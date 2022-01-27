/* 
 * File:    FR_Timer.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 25, 2022, 7:16 PM
 */
//------------------------------------------------------------------------------

#include "FR_Timer.h"
#include "tmr0.h"
#include "PIC16Xpress_DevBoard.h"

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define TMR0_PERIOD_US          250

#define FR_TIMER_TEST


//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

static unsigned long millis;
static unsigned long micros;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void FR_Timer_Init(void) {
    TMR0_Initialize();
    return;
}

//------------------------------------------------------------------------------

unsigned long FR_Timer_GetMillis() {
    return millis;
}

//------------------------------------------------------------------------------

unsigned long FR_Timer_GetMicros() {
    return (unsigned long)((millis * 1000) + TMR0_ReadTimer());
}

//------------------------------------------------------------------------------

void FR_Timer_IncMillis(void) {
    millis += 1;
}

//------------------------------------------------------------------------------

void FR_Timer_IncMicros(void) {
    micros += 1000;
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

#ifdef FR_TIMER_TEST

int main(void) {
    /*
     * THIS TEST HARNESS FLICKERS pin RC0 @1Hz (flicker LED against stopwatch)
     */
    unsigned long currMilli = 0;
    unsigned long prevMilli = 0;
    
    // Initialize required libraries
    PIC16_Init();
    FR_Timer_Init();
    
    SET_C0() = OUTPUT;
    WRITE_C0() = LOW;
    
    while(1) {
        currMilli = FR_Timer_GetMillis();
        
        // Toggle output pin every 500ms (full cycle every 1s)
        if((unsigned long)(currMilli - prevMilli) >= 500) {
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