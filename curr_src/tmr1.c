
/**
  Section: Included Files
 */

#include <xc.h>
#include "tmr1.h"

//------------------------------------------------------------------------------
/**
  Section: Global Variables Definitions
 */
volatile uint16_t timer1ReloadVal;
void (*TMR1_InterruptHandler)(void);

//------------------------------------------------------------------------------

/**
  Section: TMR1 APIs
 */

void TMR1_Initialize(void) {
    //Set the Timer to the options selected in the GUI

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

    // Set Default Interrupt Handler
    TMR1_SetInterruptHandler(TMR1_DefaultInterruptHandler);

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

void TMR1_StartSinglePulseAcquisition(void) {
    T1GCONbits.T1GGO_nDONE = 1;
}

//------------------------------------------------------------------------------

uint8_t TMR1_CheckGateValueStatus(void) {
    return (T1GCONbits.T1GVAL);
}

//------------------------------------------------------------------------------

void TMR1_ISR(void) {

    // Clear the TMR1 interrupt flag
    PIR1bits.TMR1IF = 0;
    TMR1_WriteTimer(timer1ReloadVal);

    if (TMR1_InterruptHandler) {
        TMR1_InterruptHandler();
    }
}

//------------------------------------------------------------------------------

void TMR1_SetInterruptHandler(void (* InterruptHandler)(void)) {
    TMR1_InterruptHandler = InterruptHandler;
}

//------------------------------------------------------------------------------

void TMR1_DefaultInterruptHandler(void) {
    // add your TMR1 interrupt custom code
    // or set custom function using TMR1_SetInterruptHandler()
}

//------------------------------------------------------------------------------
/**
  End of File
 */
