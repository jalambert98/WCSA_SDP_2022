/* 
 * File:    FRT.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 25, 2022, 7:16 PM
 */
//------------------------------------------------------------------------------

#include "FRT.h"

// #define FRT_TEST          // toggle comment to enable/disable test harness

//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

static volatile unsigned long millis;
static volatile unsigned long micros;

volatile uint16_t timer1ReloadVal;

//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void FRT_Init(void) {
    // init FRT time counters to 0
    millis = 0;
    micros = 0;
    
    /* TMR1 ticks @1MHz (ticks every 1us) and generates
     * an interrupt every 1000 ticks (every 1ms --> @1kHz) */
    TMR1_Initialize();
}

//------------------------------------------------------------------------------

void TMR1_Initialize(void) {
    //T1GSS T1G_pin; TMR1GE disabled; T1GTM disabled; T1GPOL low; T1GGO_nDONE done; T1GSPM disabled; 
    T1GCON = 0x00;

    //TMR1H 252; 
    TMR1H = 0xFC;

    //TMR1L 24; 
    TMR1L = 0x18;

    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR1IF = 0;

    // Load the TMR value to reload variable
    timer1ReloadVal = (uint16_t) ((TMR1H << 8) | TMR1L);

    // Enabling TMR1 interrupt.
    PIE1bits.TMR1IE = 1;

    // T1CKPS 1:8; T1SOSC T1CKI_enabled; T1SYNC do_not_synchronize; TMR1CS FOSC/4; TMR1ON enabled; 
    T1CON = 0x35;
}

//------------------------------------------------------------------------------

void TMR1_StartTimer(void) {
    // Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 1;
}

//------------------------------------------------------------------------------

void TMR1_StopTimer(void) {
    // Stop the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 0;
}

//------------------------------------------------------------------------------

uint16_t TMR1_ReadTimer(void) {
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;


    readValLow = TMR1L;
    readValHigh = TMR1H;

    readVal = ((uint16_t) readValHigh << 8) | readValLow;

    return readVal;
}

//------------------------------------------------------------------------------

void TMR1_WriteTimer(uint16_t timerVal) {
    if (T1CONbits.T1SYNC == 1) {
        // Stop the Timer by writing to TMRxON bit
        T1CONbits.TMR1ON = 0;

        // Write to the Timer1 register
        TMR1H = (uint8_t) (timerVal >> 8);
        TMR1L = (uint8_t) timerVal;

        // Start the Timer after writing to the register
        T1CONbits.TMR1ON = 1;
    } else {
        // Write to the Timer1 register
        TMR1H = (uint8_t) (timerVal >> 8);
        TMR1L = (uint8_t) timerVal;
    }
}

//------------------------------------------------------------------------------

void TMR1_Reload(void) {
    TMR1_WriteTimer(timer1ReloadVal);
}

//------------------------------------------------------------------------------

void TMR1_ISR(void) {
    TMR1_WriteTimer(timer1ReloadVal);

    millis++;
    micros += 1000;
    
    // Clear the TMR1 interrupt flag
    PIR1bits.TMR1IF = 0;
}

//------------------------------------------------------------------------------

unsigned long FRT_GetMillis() {
    return millis;
}

//------------------------------------------------------------------------------

unsigned long FRT_GetMicros() {
    return ((TMR1_ReadTimer() - timer1ReloadVal) + micros);
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

#ifdef FRT_TEST

#include "WCSA_system.h"

int main(void) {
    /*
     * THIS TEST HARNESS FLICKERS pin RC0 @1Hz (flicker LED against stopwatch)
     */
    unsigned long currMilli = 0;
    unsigned long prevMilli = 0;
    
    // Initialize required libraries
    PIC16_Init();
    FRT_Init();
    
    SET_C0() = OUTPUT;
    WRITE_C0() = LOW;
    
    while(1) {
        /*
         * NOTE:    WDT will force a reset if not cleared 
         *          within every 2 sec or less
         */
        asm("CLRWDT");  // clear watchdog timer at start of each loop
        
        currMilli = FRT_GetMillis();    // update free-running timer
        
        // Toggle output pin every 500ms (full cycle every 1s)
        if((currMilli - prevMilli) >= 500) {
            WRITE_C0() ^= 1;
            prevMilli = currMilli;
        }
    }
    while(1);
    return 0;
}

#endif

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
