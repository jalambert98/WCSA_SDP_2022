/* 
 * File:    FRT.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 25, 2022, 7:16 PM
 */
//------------------------------------------------------------------------------

#include "FRT.h"
#include "tmr1.h"

// #define FRT_TEST          // toggle comment to enable/disable test harness

//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

static volatile unsigned long millis;
static volatile unsigned long micros;

//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

unsigned long FRT_GetMillis() {
    return millis;
}

//------------------------------------------------------------------------------

unsigned long FRT_GetMicros() {
    return (micros + TMR1_ReadTimer());
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

#define DEBUG_FRT_TEST

#ifdef DEBUG_FRT_TEST

#include "eusart.h"
#include "mcc.h"

#define PRINT_RATE  50  // 50ms

int main(void) {
    PIC16_Init();
    EUSART_Initialize();
    
    printf("\n\n// ======================== //\n");
    printf("TESTING libs on %s at %s\n", __DATE__, __TIME__);
    printf("// ======================== //\n\n");
    
    SET_C0() = OUTPUT;
    WRITE_C0() = LOW;
    
    unsigned long currMilli, currMicro, prevMilli;
    currMicro = FRT_GetMicros();
    currMilli = FRT_GetMillis();
    prevMilli = currMilli;
    
    uint8_t callback = 0;
    
    while(1) {
        currMicro = FRT_GetMicros();
        currMilli = FRT_GetMillis();
        
        if((currMilli - prevMilli) >= PRINT_RATE) {
            callback++;
            printf("[ms  =  %lu]        [us  =  %lu]\n", currMilli, currMicro);
            prevMilli = currMilli;
            
            if(callback >= 10) {
                WRITE_C0() ^= 1;
                callback = 0;
            }
        }
    }
    while(1);
    return 0;
}

#endif