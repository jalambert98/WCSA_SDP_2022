/* 
 * File:    SpeakerTone.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on February 7, 2022, 9:30 PM
 */
//------------------------------------------------------------------------------

#include "SpeakerTone.h"

// Speaker Output Pin = [RA4]
//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define HALF_TIMER_PERIOD       ((uint32_t)4000000)

#define NOTE_MED_DURATION       200     // 200ms --> [1/8th notes (~150bpm)]
#define NOTE_SHORT_DURATION     100     // 100ms --> [1/16th notes]
#define NOTE_SUPERFAST          50      // 50ms  --> [1/32nd notes]

// #define SPEAKERTONE_TEST


//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

static volatile uint16_t currFreq, ocCount;
volatile uint16_t timer3ReloadVal;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void SpeakerTone_Init(void) {
    // Initialize required libraries
    TMR3_Initialize();
    CCP4_Initialize();

    // speakerTone pin is OUTPUT (init LOW)
    SET_A4() = OUTPUT;
    WRITE_A4() = LOW;

    // spkrSdwn pin low disables amp. high enables amp.
    SET_B7() = OUTPUT;
    WRITE_B7() = LOW;

    // Default tone/ocCount pair corresponds to 440Hz
    currFreq = DEFAULT_TONE;
    SpeakerTone_SetFrequency(currFreq);

    // Default to speaker off. Must be enabled in software.
    SpeakerTone_Off();
}

//------------------------------------------------------------------------------

uint8_t SpeakerTone_SetFrequency(uint16_t newFrequency) {
    if ((newFrequency < MIN_FREQ) || (newFrequency > MAX_FREQ)) {
        return ERROR;
    } else {
        // Store user-assigned frequency & calculate required ocCount
        currFreq = newFrequency;
        ocCount = (uint16_t) (HALF_TIMER_PERIOD / newFrequency);

        // Update output compare match value
        CCP4_SetCompareCount(ocCount);
        //TMR3_Reload();
        return SUCCESS;
    }
}

//------------------------------------------------------------------------------

void CCP4_Initialize(void) {
    TRISAbits.TRISA4 = OUTPUT;
    LATAbits.LATA4 = LOW;

    // Peripheral pin select [PPS] module config
    RA4PPS = 0x0F; //RA4->CCP4:CCP4; 

    // CCP4MODE Toggle_cleartmr; CCP4OUT 0; CCP4EN enabled; CCP4FMT right_aligned; 
    CCP4CON = 0x81;

    // CCPR4H 0; 
    CCPR4H = 0x00;

    // CCPR4L 0; 
    CCPR4L = 0x00;

    // Selecting Timer 3
    CCPTMRSbits.C4TSEL = 0x2;

    // Clear the CCP4 interrupt flag
    PIR4bits.CCP4IF = 0;

    // Enable the CCP4 interrupt
    PIE4bits.CCP4IE = 1;
}

//------------------------------------------------------------------------------

void CCP4_SetCompareCount(uint16_t compareCount) {
    CCP4_PERIOD_REG_T module;

    // Write the 16-bit compare value
    module.ccpr4_16Bit = compareCount;

    CCPR4L = module.ccpr4l;
    CCPR4H = module.ccpr4h;
}

//------------------------------------------------------------------------------

void CCP4_CompareISR(void) {
    // Clear the CCP4 interrupt flag
    PIR4bits.CCP4IF = 0;
}

//------------------------------------------------------------------------------

void TMR3_Initialize(void) {
    //T3GSS T3G_pin; TMR3GE disabled; T3GTM disabled; T3GPOL low; T3GGO_nDONE done; T3GSPM disabled; 
    T3GCON = 0x00;

    //TMR3H 0; 
    TMR3H = 0x00;

    //TMR3L 0; 
    TMR3L = 0x00;

    // Clearing IF flag.
    PIR3bits.TMR3IF = 0;

    // Load the TMR value to reload variable
    timer3ReloadVal = (uint16_t) ((TMR3H << 8) | TMR3L);

    // T3CKPS 1:1; T3SOSC T3CKI_enabled; T3SYNC synchronize; TMR3CS FOSC/4; TMR3ON disabled; 
    T3CON = 0x00;
}

//------------------------------------------------------------------------------

void TMR3_StartTimer(void) {
    // Start the Timer by writing to TMRxON bit
    T3CONbits.TMR3ON = 1;
}

//------------------------------------------------------------------------------

void TMR3_StopTimer(void) {
    // Stop the Timer by writing to TMRxON bit
    T3CONbits.TMR3ON = 0;
}

//------------------------------------------------------------------------------

void TMR3_WriteTimer(uint16_t timerVal) {
    if (T3CONbits.T3SYNC == 1) {
        // Stop the Timer by writing to TMRxON bit
        T3CONbits.TMR3ON = 0;

        // Write to the Timer3 register
        TMR3H = (uint8_t) (timerVal >> 8);
        TMR3L = (uint8_t) timerVal;

        // Start the Timer after writing to the register
        T3CONbits.TMR3ON = 1;
    } else {
        // Write to the Timer3 register
        TMR3H = (uint8_t) (timerVal >> 8);
        TMR3L = (uint8_t) timerVal;
    }
}

//------------------------------------------------------------------------------

void TMR3_Reload(void) {
    TMR3_WriteTimer(timer3ReloadVal);
}

//------------------------------------------------------------------------------

void SpeakerTone_Off(void) {
    WRITE_B7() = LOW; // shut down amplifier
    TMR3_StopTimer(); // pause TMR3 ticks
    TMR3_Reload(); // clear TMR3 register
    return;
}

//------------------------------------------------------------------------------

void SpeakerTone_On(void) {
    WRITE_B7() = HIGH; // start up amplifier
    TMR3_StartTimer(); // resume TMR3 ticks
    return;
}

//------------------------------------------------------------------------------

void SpeakerTone_StartupChirp(void) {
    // Ascending Cmaj triad (1/8th notes)
    RESET_WDT();
    SpeakerTone_SetFrequency(TONE_C4);  // C
    SpeakerTone_On();
    __delay_ms(NOTE_MED_DURATION);
    SpeakerTone_SetFrequency(TONE_E4);  // E
    __delay_ms(NOTE_MED_DURATION);
    SpeakerTone_SetFrequency(TONE_G4);  // G
    __delay_ms(NOTE_MED_DURATION);

    RESET_WDT();
    SpeakerTone_Off();  // Turn off amplifier
}

//------------------------------------------------------------------------------

void SpeakerTone_ShutdownChirp(void) {
    // Descending Cmaj triad (1/8th notes)
    RESET_WDT();
    SpeakerTone_SetFrequency(TONE_G4);  // G
    SpeakerTone_On();
    __delay_ms(NOTE_MED_DURATION);
    SpeakerTone_SetFrequency(TONE_E4);  // E      
    __delay_ms(NOTE_MED_DURATION);
    SpeakerTone_SetFrequency(TONE_C4);  // C
    __delay_ms(NOTE_MED_DURATION);

    RESET_WDT();
    SpeakerTone_Off();  // Turn off amplifier
}

//------------------------------------------------------------------------------

void SpeakerTone_LowBatteryChirp(void) {
    // Alternating G4-->C5 (played 2x) --> quick 4x (1/16th) notes
    RESET_WDT();
    SpeakerTone_SetFrequency(TONE_G4);  // G
    SpeakerTone_On();
    __delay_ms(NOTE_SHORT_DURATION);
    SpeakerTone_SetFrequency(TONE_C5);  // C
    __delay_ms(NOTE_SHORT_DURATION);
    SpeakerTone_SetFrequency(TONE_G4);  // G
    __delay_ms(NOTE_SHORT_DURATION);
    SpeakerTone_SetFrequency(TONE_C5);  // C
    __delay_ms(NOTE_SHORT_DURATION);

    RESET_WDT();
    SpeakerTone_Off();  // Turn off amplifier
}

//------------------------------------------------------------------------------

void SpeakerTone_BatLvlChirp(batLvl_t batChg) {
    RESET_WDT();

    // Play C4 for 200ms
    SpeakerTone_SetFrequency(TONE_C4);  // same first note for all batLvl chirps
    SpeakerTone_On();   // turn on speaker
    __delay_ms(NOTE_MED_DURATION);

    switch (batChg) {
        case BAT_EMPTY:     // 1 note only (probably will never happen)
            break;          // automatic shutdown gets priority
            
        case BAT_25:        // 2 notes (C,G) if vBat enters BAT_25
            // Add 2nd note if vBat > 25%
            SpeakerTone_SetFrequency(TONE_G4);
            __delay_ms(NOTE_MED_DURATION);
            break;   
            
        case BAT_50:        // 3 notes (C,G,A) if vBat enters BAT_50
            // Add 2nd-3rd notes if vBat > 50%
            SpeakerTone_SetFrequency(TONE_G4);
            __delay_ms(NOTE_MED_DURATION);
            SpeakerTone_SetFrequency(TONE_A4);
            __delay_ms(NOTE_MED_DURATION);
            break;  
            
        case BAT_75:        // 4 notes (C,G,A,B) if vBat enters BAT_75
            // Add 2nd-4th notes if vBat > 75%
            SpeakerTone_SetFrequency(TONE_G4);
            __delay_ms(NOTE_MED_DURATION);
            SpeakerTone_SetFrequency(TONE_A4);
            __delay_ms(NOTE_MED_DURATION);
            SpeakerTone_SetFrequency(TONE_B4);
            __delay_ms(NOTE_MED_DURATION);   
            break;

        case BAT_FULL:      // 5 notes (C,G,A,B,C) if vBat enters BAT_FULL
            // Add 2nd-5th notes if vBat is basically full ( > ~90%)
            SpeakerTone_SetFrequency(TONE_G4);
            __delay_ms(NOTE_MED_DURATION);
            SpeakerTone_SetFrequency(TONE_A4);
            __delay_ms(NOTE_MED_DURATION);
            SpeakerTone_SetFrequency(TONE_B4);
            __delay_ms(NOTE_MED_DURATION);
            SpeakerTone_SetFrequency(TONE_C5);
            __delay_ms(NOTE_MED_DURATION);
            SpeakerTone_Off();      
            break;
    }
    
    RESET_WDT();
    SpeakerTone_Off();      // turn off speaker
}

//------------------------------------------------------------------------------

void SpeakerTone_NowChargingChirp(uint8_t chgEn) {
    // Super fast ascending arpeggio 2x (5x note runs)
    RESET_WDT();

    if (chgEn == TRUE) {
        // First run
        SpeakerTone_SetFrequency(TONE_C4);
        SpeakerTone_On();
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_E4);
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_G4);
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_B4);
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_C5);
        __delay_ms(NOTE_SUPERFAST);

        // (1/16th) note rest between (1/32nd) note runs
        SpeakerTone_Off();
        __delay_ms(NOTE_SHORT_DURATION);

        // Second run
        SpeakerTone_SetFrequency(TONE_C4);
        SpeakerTone_On();
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_E4);
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_G4);
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_B4);
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_C5);
        __delay_ms(NOTE_SUPERFAST);
    }
    else {
        // First run
        SpeakerTone_SetFrequency(TONE_C5);
        SpeakerTone_On();
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_B4);
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_G4);
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_E4);
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_C4);
        __delay_ms(NOTE_SUPERFAST);

        // (1/16th) note rest between (1/32nd) note runs
        SpeakerTone_Off();
        __delay_ms(NOTE_SHORT_DURATION);

        // Second run
        SpeakerTone_SetFrequency(TONE_C5);
        SpeakerTone_On();
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_B4);
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_G4);
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_E4);
        __delay_ms(NOTE_SUPERFAST);
        SpeakerTone_SetFrequency(TONE_C4);
        __delay_ms(NOTE_SUPERFAST);
    }
    
    RESET_WDT();
    SpeakerTone_Off();
}

//------------------------------------------------------------------------------

void SpeakerTone_ChargeCompleteChirp(void) {
    SpeakerTone_BatLvlChirp(BAT_FULL);
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

/* ---------- TEST HARNESS FOR SPEAKER TONE SUBSYSTEM ---------- */
#ifdef SPEAKERTONE_TEST

// ======= DEFINES ======= //
#define CHIRP_RATE    3000 // play chirp sequence every 5s


// ======= MAIN() ======= //

int main(void) {
    // Init required libraries
    PIC16_Init();
    FRT_Init();
    SpeakerTone_Init(); // speakerTone pinRA4

    RESET_WDT();

    printf("//=== SpeakerTone.c ===//\n");
    printf("SPEAKERTONE_TEST - Last compiled on %s at %s\n", __DATE__, __TIME__);
    uint32_t currMilli = FRT_GetMillis();
    uint32_t prevMilli = currMilli;
    uint8_t i = 0;

    while (1) {
        /*
         * NOTE:    WDT will force a reset if not cleared 
         *          within every 2 sec or less
         */
        RESET_WDT(); // reset watchdog timer at start of each loop

        currMilli = FRT_GetMillis(); // update free-running timer

        if ((currMilli - prevMilli) >= CHIRP_RATE) {
            switch (i) {
                case 0:
                    SpeakerTone_StartupChirp();
                    i++;
                    break;
                case 1:
                    SpeakerTone_ShutdownChirp();
                    i++;
                    break;
                case 2:
                    SpeakerTone_LowBatteryChirp();
                    i++;
                    break;     
                case 3:
                    SpeakerTone_BatLvlChirp(BAT_50);
                    i++;
                    break;     
                case 4:
                    SpeakerTone_BatLvlChirp(BAT_75);
                    i++;
                    break;  
                case 5:
                    SpeakerTone_BatLvlChirp(BAT_FULL);
                    i++;
                    break;
                case 6:
                    SpeakerTone_NowChargingChirp(TRUE);
                    i++;
                    break;
                case 7:
                    SpeakerTone_NowChargingChirp(FALSE);
                    i = 0;
                    break;
            }

            prevMilli = currMilli;
            RESET_WDT();
        }
    }
    return 0;
}

#endif

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
