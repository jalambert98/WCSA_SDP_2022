/* 
 * File:    tmr2.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: Generated originally by Microchip Code Configurator (MCC) and then
 *       further modified by Jack Lambert
 * 
 * Created on February 8, 2022, 2:15 PM
 */
//------------------------------------------------------------------------------
/* TMR2 ticks @250kHz & rolls over every 1ms
 * This timer is used to control PWM5 (motor control output)
 * PWM frequency is fixed @1kHz, but duty cycle is variable */
#include <xc.h>
#include "tmr2.h"

//------------------------------------------------------------------------------

void TMR2_Initialize(void)
{
    // PR2 249; 
    PR2 = 0xF9;

    // TMR2 0; 
    TMR2 = 0x00;

    // Clearing IF flag.
    PIR1bits.TMR2IF = 0;

    // T2CKPS 1:16; T2OUTPS 1:1; TMR2ON off; 
    T2CON = 0x02;
}

//------------------------------------------------------------------------------

void TMR2_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 1;
}

//------------------------------------------------------------------------------

void TMR2_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 0;
}

//------------------------------------------------------------------------------

uint8_t TMR2_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TMR2;

    return readVal;
}

//------------------------------------------------------------------------------

void TMR2_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer2 register
    TMR2 = timerVal;
}

//------------------------------------------------------------------------------

void TMR2_LoadPeriodRegister(uint8_t periodVal)
{
   PR2 = periodVal;
}

//------------------------------------------------------------------------------

bool TMR2_HasOverflowOccured(void)
{
    // check if  overflow has occurred by checking the TMRIF bit
    bool status = PIR1bits.TMR2IF;
    if(status)
    {
        // Clearing IF flag.
        PIR1bits.TMR2IF = 0;
    }
    return status;
}

//------------------------------------------------------------------------------
/**
  End of File
*/
