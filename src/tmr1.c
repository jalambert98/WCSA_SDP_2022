/* 
 * File:    tmr1.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 26, 2022, 12:20 PM
 */
//------------------------------------------------------------------------------

#include <xc.h>
#include "tmr1.h"

volatile uint16_t timer1ReloadVal;

//------------------------------------------------------------------------------
/*
 * TMR1 ticks @1MHz & rolls over after 16-bit range [0x0000 --> 0xFFFF]
 */
void TMR1_Initialize(void)
{
    //Set the Timer to the options selected in the GUI

    //T1GSS T1G_pin; TMR1GE disabled; T1GTM disabled; T1GPOL low; T1GGO_nDONE done; T1GSPM disabled; 
    T1GCON = 0x00;

    //TMR1H 0; 
    TMR1H = 0x00;

    //TMR1L 0; 
    TMR1L = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR1IF = 0;

    // Load the TMR value to reload variable
    timer1ReloadVal=(uint16_t)((TMR1H << 8) | TMR1L);

    // Enabling TMR1 interrupt.
    PIE1bits.TMR1IE = 1;

    // T1CKPS 1:4; T1SOSC T1CKI_enabled; T1SYNC synchronize; TMR1CS FOSC/4; TMR1ON enabled; 
    T1CON = 0b00100001;
}

//------------------------------------------------------------------------------

void TMR1_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 1;
}

//------------------------------------------------------------------------------

void TMR1_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 0;
}

//------------------------------------------------------------------------------

uint16_t TMR1_ReadTimer(void)
{
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    
	
    readValLow = TMR1L;
    readValHigh = TMR1H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;

    return readVal;
}

//------------------------------------------------------------------------------

void TMR1_WriteTimer(uint16_t timerVal)
{
    if (T1CONbits.T1SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit
        T1CONbits.TMR1ON = 0;

        // Write to the Timer1 register
        TMR1H = (uint8_t)(timerVal >> 8);
        TMR1L = (uint8_t)timerVal;

        // Start the Timer after writing to the register
        T1CONbits.TMR1ON =1;
    }
    else
    {
        // Write to the Timer1 register
        TMR1H = (uint8_t)(timerVal >> 8);
        TMR1L = (uint8_t)timerVal;
    }
}

//------------------------------------------------------------------------------

void TMR1_Reload(void)
{
    TMR1_WriteTimer(timer1ReloadVal);
}

//------------------------------------------------------------------------------

void TMR1_ISR(void)
{
    // Clear the TMR1 interrupt flag
    PIR1bits.TMR1IF = 0;
    TMR1_WriteTimer(timer1ReloadVal);
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
