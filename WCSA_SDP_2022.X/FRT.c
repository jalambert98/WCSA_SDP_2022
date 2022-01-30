/* 
 * File:    FRT.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 25, 2022, 7:16 PM
 */
//------------------------------------------------------------------------------

#include "FRT.h"


//#define FRT_TEST          // toggle comment to enable/disable test harness

//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

static unsigned long millis;
static unsigned long micros;

//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

unsigned long FRT_GetMillis() {
    return millis;
}

//------------------------------------------------------------------------------

unsigned long FRT_GetMicros() {
    return (micros + TMR0_ReadTimer());
}

//------------------------------------------------------------------------------

void FRT_IncMillis(void) {
    millis ++;
    return;
}

//------------------------------------------------------------------------------

void FRT_IncMicros(void) {
    micros += 1000;
    return;
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

#ifdef FRT_TEST

int main(void) {
    /*
     * THIS TEST HARNESS FLICKERS pin RC0 @1Hz (flicker LED against stopwatch)
     */
    unsigned long currMilli = 0;
    unsigned long prevMilli = 0;
    
    // Initialize required libraries
    PIC16_Init();
    
    SET_C0() = OUTPUT;
    WRITE_C0() = LOW;
    
    while(1) {
        currMilli = FRT_GetMillis();
        
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
