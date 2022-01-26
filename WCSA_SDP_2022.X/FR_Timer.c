/* 
 * File:    FR_Timer.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 25, 2022, 7:16 PM
 */

#include "FR_Timer.h"

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define TMR0_PERIOD_US          250

//#define FR_TIMER_TEST


//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

static unsigned int millis4x;
static unsigned int micros1x;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

uint8_t FR_Timer_Init(void) {
    INTCONbits.GIE = LOW;       // Temporarily disable global interrupts
    millis4x = 0;                 
    micros1x = 0;               // Reset module level variables
    
    // --- Configure TMR0 for ticks @1MHz & rollover every 250us --- //
    T0CON0 = 0x00;              
    T0CON1 = 0x00;              // Clear TMR0 control registers
    TMR0L = 0x00;               // Clear TMR0 counter register
    
    T0CON0bits.T016BIT = LOW;   // TMR0 is set to 8-bit timer mode
    T0CON1bits.T0CS = 0b010;    // [F_osc/4] = [2MHz] clk source for TMR0
    T0CON1bits.T0CKPS = 0x1;    // Set 2:1 prescalar [TMR0 ticks @1MHz]
    T0CON1bits.T0ASYNC = LOW;   // Sync TMR0 counter with [F_osc/4]
    T0CON0bits.T0OUTPS = 0x0;   // Set 1:1 postscalar [input = output = 1MHz]
    TMR0H = TMR0_PERIOD_US;     // Period match = 250 --> interrupt every 250us
    
    PIE0bits.TMR0IE = HIGH;     // Enable TMR0 interrupts
    INTCONbits.GIE = HIGH;      // Enable global interrupts
    T0CON0bits.T0EN = HIGH;     // Enable TMR0
    
    return SUCCESS;
}

//------------------------------------------------------------------------------

unsigned int FR_Timer_GetMillis() {
    // millis4x increments every 250us, so /4 = 1ms
    return (millis4x >> 2);
}

//------------------------------------------------------------------------------

unsigned int FR_Timer_GetMicros() {
    // millis4x increments every 250us, so *250 = 1us
    return ((millis4x * TMR0_PERIOD_US) + micros1x);
}

//------------------------------------------------------------------------------

void FR_Timer_IncMillis(void) {
    millis4x++;
}

//------------------------------------------------------------------------------

void FR_Timer_IncMicros(void) {
    micros1x += TMR0_PERIOD_US;
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

#ifdef FR_TIMER_TEST

int main(void) {
    
}

#endif

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================