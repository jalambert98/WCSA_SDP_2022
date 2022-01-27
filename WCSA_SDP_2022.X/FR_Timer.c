/* 
 * File:    FR_Timer.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 25, 2022, 7:16 PM
 */

#include "FR_Timer.h"
#include <stdio.h>

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define TMR0_PERIOD_US          250

#define FR_TIMER_TEST


//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

static unsigned int millis4x;
static unsigned int micros1x;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void FR_Timer_Init(void) {
    INTCONbits.GIE = LOW;       // Temporarily disable global interrupts
    millis4x = 0;                 
    micros1x = 0;               // Reset module level variables
    
    // --- Configure TMR0 for ticks @1MHz & rollover every 250us --- //
    T0CON0 = 0x00;              
    T0CON1 = 0x00;              // Clear TMR0 control registers
    TMR0L = 0x00;               // Clear TMR0 counter register
    
    T0CON0bits.T016BIT = LOW;   // TMR0 is set to 8-bit timer mode
    T0CON1bits.T0CS = 0b010;    // [16MHz/4 = 4MHz] clk for TMR0
    T0CON1bits.T0CKPS = 0x2;    // Set 4:1 prescalar [TMR0 ticks @1MHz]
    T0CON1bits.T0ASYNC = LOW;   // Syncd with [F_osc/4]
    T0CON0bits.T0OUTPS = 0x0;   // Set 1:1 postscalar [input = output = 1MHz]
    TMR0H = TMR0_PERIOD_US;     // Period match = 250 --> interrupt every 250us
    
    PIE0bits.TMR0IE = HIGH;     // Enable TMR0 interrupts
    INTCONbits.GIE = HIGH;      // Enable global interrupts
    T0CON0bits.T0EN = HIGH;     // Enable TMR0
    
    return;
}

//------------------------------------------------------------------------------

unsigned int FR_Timer_GetMillis() {
    // millis4x increments every 250us, so /4 = 1ms
    return (millis4x >> 2);
}

//------------------------------------------------------------------------------

unsigned int FR_Timer_GetMicros() {
    // millis4x increments every 250us, so *250 = 1us
    return ((millis4x * TMR0_PERIOD_US) + TMR0L);
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
    unsigned int currMilli = 0;
    unsigned int prevMilli = 0;
    
    // Initialize required libraries
    PIC16_Init();
    FR_Timer_Init();
    
    SET_C0() = OUTPUT;
    WRITE_C0() = LOW;
    
    while(1) {
        currMilli = FR_Timer_GetMillis();
        
        if((currMilli - prevMilli) > 500) {
            WRITE_C0() = ~WRITE_C0();
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