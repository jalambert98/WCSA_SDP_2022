
/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr2.h"

//------------------------------------------------------------------------------
/**
  Section: TMR2 APIs
*/

void TMR2_Initialize(void)
{
    // Set TMR2 to the options selected in the User Interface

    // PR2 249; 
    PR2 = 0xF9;

    // TMR2 0; 
    TMR2 = 0x00;

    // Clearing IF flag.
    PIR1bits.TMR2IF = 0;

    // T2CKPS 1:4; T2OUTPS 1:8; TMR2ON on; 
    T2CON = 0x3D;
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