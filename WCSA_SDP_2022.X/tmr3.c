/* 
 * File:    tmr3.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on February 8, 2022, 2:15 PM
 */
//------------------------------------------------------------------------------

#include <xc.h>
#include "tmr3.h"

//------------------------------------------------------------------------------

volatile uint16_t timer3ReloadVal;
void (*TMR3_InterruptHandler)(void);

//------------------------------------------------------------------------------
/* TMR3 ticks@4MHz, rollover after 16-bit range (always cleared before rollover)
 */
void TMR3_Initialize(void)
{
    //T3GSS T3G_pin; TMR3GE disabled; T3GTM disabled; T3GPOL low; T3GGO_nDONE done; T3GSPM disabled; 
    T3GCON = 0x00;

    //TMR3H 6; 
    TMR3H = 0x00;

    //TMR3L 0; 
    TMR3L = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR3bits.TMR3IF = 0;

    // Load the TMR value to reload variable
    timer3ReloadVal=(uint16_t)((TMR3H << 8) | TMR3L);

    // Enabling TMR3 interrupt.
    PIE3bits.TMR3IE = 1;

    // Set Default Interrupt Handler
    TMR3_SetInterruptHandler(TMR3_DefaultInterruptHandler);

    // T3CKPS 1:1; T3SOSC T3CKI_enabled; T3SYNC synchronize; TMR3CS FOSC/4; TMR3ON disabled; 
    T3CON = 0x00;
}

//------------------------------------------------------------------------------

void TMR3_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T3CONbits.TMR3ON = 1;
}

//------------------------------------------------------------------------------

void TMR3_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T3CONbits.TMR3ON = 0;
}

//------------------------------------------------------------------------------

uint16_t TMR3_ReadTimer(void)
{
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    
	
    readValLow = TMR3L;
    readValHigh = TMR3H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;

    return readVal;
}

//------------------------------------------------------------------------------

void TMR3_WriteTimer(uint16_t timerVal)
{
    if (T3CONbits.T3SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit
        T3CONbits.TMR3ON = 0;

        // Write to the Timer3 register
        TMR3H = (uint8_t)(timerVal >> 8);
        TMR3L = (uint8_t)timerVal;

        // Start the Timer after writing to the register
        T3CONbits.TMR3ON =1;
    }
    else
    {
        // Write to the Timer3 register
        TMR3H = (uint8_t)(timerVal >> 8);
        TMR3L = (uint8_t)timerVal;
    }
}

//------------------------------------------------------------------------------

void TMR3_Reload(void)
{
    TMR3_WriteTimer(timer3ReloadVal);
}

//------------------------------------------------------------------------------

void TMR3_StartSinglePulseAcquisition(void)
{
    T3GCONbits.T3GGO_nDONE = 1;
}

//------------------------------------------------------------------------------

uint8_t TMR3_CheckGateValueStatus(void)
{
    return (T3GCONbits.T3GVAL);
}

//------------------------------------------------------------------------------

void TMR3_ISR(void)
{
    // Clear the TMR3 interrupt flag
    PIR3bits.TMR3IF = 0;
    TMR3_Reload();
    LATCbits.LATC0 = 1;
    /*if(TMR3_InterruptHandler)
    {
        TMR3_InterruptHandler();
    }*/
}

//------------------------------------------------------------------------------

void TMR3_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR3_InterruptHandler = InterruptHandler;
}

//------------------------------------------------------------------------------

void TMR3_DefaultInterruptHandler(void){
    // add your TMR3 interrupt custom code
    // or set custom function using TMR3_SetInterruptHandler()
}

//------------------------------------------------------------------------------
/**
  End of File
*/
