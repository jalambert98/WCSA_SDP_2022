/* 
 * File:    SpeakerTone.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on February 7, 2022, 9:30 PM
 */
//------------------------------------------------------------------------------

#include "SpeakerTone.h"
#include "WCSA_system.h"
#include "FRT.h"

// Speaker Output Pin = [RA4]
//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define HALF_TIMER_FREQ     ((uint32_t)2000000)

#define SPEAKERTONE_TEST


//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

static uint16_t currFreq, ocCount;
volatile uint16_t timer3ReloadVal;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void SpeakerTone_Init(void) {
    // Initialize required libraries
    CCP4_Initialize();
    TMR3_Initialize();

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
        ocCount = (uint16_t) (HALF_TIMER_FREQ / newFrequency);

        TMR3_Reload();
        
        // Update output compare match value
        CCP4_SetCompareCount(ocCount);
        return SUCCESS;
    }
}

//------------------------------------------------------------------------------

uint16_t SpeakerTone_GetFrequency(void) {
    return currFreq; // return frequency last assigned by user (440Hz if N/A)
}

//------------------------------------------------------------------------------

void CCP4_Initialize(void) {
    TRISAbits.TRISA4 = OUTPUT;
    LATAbits.LATA4 = LOW;
    
    // Peripheral pin select [PPS] module config
    RA4PPS = 0x0F;          //RA4->CCP4:CCP4; 

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

bool CCP4_OutputStatusGet(void) {
    // Returns the output status
    return (CCP4CONbits.CCP4OUT);
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

    // T3CKPS 1:2; T3SOSC T3CKI_enabled; T3SYNC synchronized; TMR3CS FOSC/4; TMR3ON disabled; 
    T3CON = 0x10;
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

uint16_t TMR3_ReadTimer(void) {
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;

    readValLow = TMR3L;
    readValHigh = TMR3H;

    readVal = ((uint16_t) readValHigh << 8) | readValLow;

    return readVal;
}

//------------------------------------------------------------------------------

void TMR3_WriteTimer(uint16_t timerVal) {
    // Write to the Timer3 register
    TMR3H = (uint8_t) (timerVal >> 8);
    TMR3L = (uint8_t) timerVal;
}

//------------------------------------------------------------------------------

void TMR3_Reload(void) {
    TMR3_WriteTimer(timer3ReloadVal);
}

//------------------------------------------------------------------------------

bool TMR3_HasOverflowOccured(void) {
    // check if  overflow has occurred by checking the TMRIF bit
    return (PIR3bits.TMR3IF);
}

//------------------------------------------------------------------------------

void SpeakerTone_Off(void) {
    PIC16_WritePin(B7, LOW); // shut down amplifier
    TMR3_StopTimer(); // pause TMR3 ticks
    TMR3_Reload(); // clear TMR3 register
    return;
}

//------------------------------------------------------------------------------

void SpeakerTone_On(void) {
    PIC16_WritePin(B7, HIGH); // start up amplifier
    TMR3_StartTimer(); // resume TMR3 ticks
    return;
}

//------------------------------------------------------------------------------

void SpeakerTone_StartupChirp(void) {
    uint32_t curr, prev;
    RESET_WDT();

    // Play C4 for 200ms
    SpeakerTone_SetFrequency(TONE_C4);
    SpeakerTone_On();
    prev = FRT_GetMillis();
    do {
        curr = FRT_GetMillis();
    } while ((curr - prev) < 200);

    // Play E4 for 200ms
    SpeakerTone_SetFrequency(TONE_E4);
    prev = FRT_GetMillis();
    do {
        curr = FRT_GetMillis();
    } while ((curr - prev) < 200);

    // Play G4 for 200ms
    SpeakerTone_SetFrequency(TONE_G4);
    prev = FRT_GetMillis();
    do {
        curr = FRT_GetMillis();
    } while ((curr - prev) < 200);

    RESET_WDT();
    
    // Turn off amplifier
    SpeakerTone_Off();
}

//------------------------------------------------------------------------------

void SpeakerTone_ShutdownChirp(void) {
    uint32_t curr, prev;
    RESET_WDT();

    // Play C4 for 200ms
    SpeakerTone_SetFrequency(TONE_G4);
    SpeakerTone_On();
    prev = FRT_GetMillis();
    do {
        curr = FRT_GetMillis();
    } while ((curr - prev) < 200);

    // Play E4 for 200ms
    SpeakerTone_SetFrequency(TONE_E4);
    prev = FRT_GetMillis();
    do {
        curr = FRT_GetMillis();
    } while ((curr - prev) < 200);

    // Play G4 for 200ms
    SpeakerTone_SetFrequency(TONE_C4);
    prev = FRT_GetMillis();
    do {
        curr = FRT_GetMillis();
    } while ((curr - prev) < 200);

    RESET_WDT();
    
    // Turn off amplifier
    SpeakerTone_Off();
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

/* ---------- TEST HARNESS FOR SPEAKER TONE SUBSYSTEM ---------- */
#ifdef SPEAKERTONE_TEST

// ======= DEFINES ======= //
#define CHIRP_RATE    5000 // play chirp sequence every 5s


// ======= MAIN() ======= //

int main(void) {
    // Init required libraries
    PIC16_Init();
    FRT_Init();
    SpeakerTone_Init(); // speakerTone pinRA4
    CCPTMRS = 0b10010000;

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
            if (i == 0) {
                SpeakerTone_StartupChirp();
                i = 1;
            } else if (i == 1) {
                SpeakerTone_ShutdownChirp();
                i = 0;
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
