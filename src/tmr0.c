/* 
 * File:    tmr0.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: Generated originally by Microchip Code Configurator (MCC) and then
 *       further modified by Jack Lambert
 * 
 * Created on January 26, 2022, 10:52 PM
 */
//------------------------------------------------------------------------------

#include <xc.h>
#include "tmr0.h"
#include "FRT.h"

void (*TMR0_InterruptHandler)(void);
static volatile uint8_t CountCallBack;

//------------------------------------------------------------------------------

void TMR0_Initialize(void)
{
    // T0CS FOSC/4; T0CKPS 1:4; T0ASYNC synchronised; 
    T0CON1 = 0x42;

    // TMR0H 249; 
    TMR0H = 0xF9;

    // TMR0L 0; 
    TMR0L = 0x00;

    // Clear Interrupt flag before enabling the interrupt
    PIR0bits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    PIE0bits.TMR0IE = 1;

    // Set Default Interrupt Handler
    TMR0_SetInterruptHandler(TMR0_DefaultInterruptHandler);

    // T0OUTPS 1:1; T0EN enabled; T016BIT 8-bit; 
    T0CON0 = 0x80;
    
    CountCallBack = 0;
}

//------------------------------------------------------------------------------

void TMR0_StartTimer(void)
{
    // Start the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 1;
}

//------------------------------------------------------------------------------

void TMR0_StopTimer(void)
{
    // Stop the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 0;
}

//------------------------------------------------------------------------------

uint8_t TMR0_ReadTimer(void)
{
    uint8_t readVal;

    // read Timer0, low register only
    readVal = TMR0L;

    return readVal;
}

//------------------------------------------------------------------------------

void TMR0_WriteTimer(uint8_t timerVal)
{
    // Write to Timer0 registers, low register only
    TMR0L = timerVal;
 }

//------------------------------------------------------------------------------

void TMR0_Reload(uint8_t periodVal)
{
   // Write to Timer0 registers, high register only
   TMR0H = periodVal;
}

//------------------------------------------------------------------------------

void TMR0_ISR(void)
{
    // callback function - called every 4th pass
    if (CountCallBack >= TMR0_INTERRUPT_TICKER_FACTOR)
    {
        // ticker function call
        FRT_IncMicros();
        FRT_IncMillis();

        // reset ticker counter
        CountCallBack = 0;
    }
    
    CountCallBack++;
    
    // clear the TMR0 interrupt flag
    PIR0bits.TMR0IF = 0;
}

//------------------------------------------------------------------------------

void TMR0_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR0_InterruptHandler = InterruptHandler;
}

//------------------------------------------------------------------------------

void TMR0_DefaultInterruptHandler(void){
    // add your TMR0 interrupt custom code
    // or set custom function using TMR0_SetInterruptHandler()
}

//------------------------------------------------------------------------------

uint8_t TMR0_GetCallBackNum(void) {
    return CountCallBack;
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
