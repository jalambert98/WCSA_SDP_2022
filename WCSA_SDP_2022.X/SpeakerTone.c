/* 
 * File:    SpeakerTone.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on February 7, 2022, 9:30 PM
 */
//------------------------------------------------------------------------------

#include "PIC16Xpress_DevBoard.h"
#include "SpeakerTone.h"
#include "ccp4.h"
#include "tmr3.h"

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define HALF_TIMER_PERIOD   ((uint32_t)2000000) 

#define SPEAKERTONE_TEST


//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

uint16_t currFreq, ocCount;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void SpeakerTone_Init(void) {
    // speakerTone pin is OUTPUT (init LOW)
    SetPin(C1, OUTPUT);
    WritePin(C1, LOW);
    
    // Default tone/ocCount pair corresponds to 440Hz
    currFreq = DEFAULT_TONE;
    ocCount = DEFAULT_OCCOUNT;
    
    // Default to speaker off. Must be enabled in software.
    SpeakerTone_Off();
}

//------------------------------------------------------------------------------

uint8_t SpeakerTone_SetFrequency(uint16_t newFrequency) {
    if((newFrequency < MIN_FREQ)||(newFrequency > MAX_FREQ))
        return ERROR;
    else {
        // Disable speaker before changing freq during operation
        SpeakerTone_Off();
        
        // Store user-assigned frequency & calculate required ocCount
        currFreq = newFrequency;
        ocCount = (uint16_t)(HALF_TIMER_PERIOD/newFrequency);
        
        // Update output compare match value
        CCP4_SetCompareCount(ocCount);
        
        // Enable speaker tone after freq properly updated
        SpeakerTone_On();
        return SUCCESS;
    }
}

//------------------------------------------------------------------------------

uint16_t SpeakerTone_GetFrequency(void) {
    return currFreq;  // return frequency last assigned by user (440Hz if N/A)
}

//------------------------------------------------------------------------------

void SpeakerTone_Off(void) {
    TMR3_StopTimer();   // pause TMR3 ticks
    TMR3_Reload();      // clear TMR3 register
    return;
}

//------------------------------------------------------------------------------

void SpeakerTone_On(void) {
    TMR3_StartTimer();  // resume TMR3 ticks
    return;
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

#ifdef SPEAKERTONE_TEST

#include "FRT.h"

#define FREQ_CHANGE_RATE    200000  // change speakerTone freq every 100ms

int main(void) {
    PIC16_Init();
    SpeakerTone_Init(); // speakerTone pinRC1
    
    unsigned long currMicro = FRT_GetMicros();
    unsigned long prevMicro = currMicro;
    uint8_t i = 0;

    /* Plays back Windows theme 
     * (C->C->F->G) : (changes pitch every 200ms) */
    while(1) {
        currMicro = FRT_GetMicros();
        if((currMicro - prevMicro) > (unsigned long)FREQ_CHANGE_RATE) {
            switch(i) {
                case 0:
                    SpeakerTone_SetFrequency(TONE_C4);
                    SpeakerTone_On();
                    i = 1;
                    break;
                case 1:
                    SpeakerTone_SetFrequency(TONE_C5);
                    i = 2;
                    break;
                case 2:
                    SpeakerTone_SetFrequency(TONE_F4);
                    i = 3;
                    break;
                case 3:
                    SpeakerTone_SetFrequency(TONE_G4);
                    i = 4;
                    break;
                case 4:
                    SpeakerTone_Off();
                    while((currMicro + 1000000) > FRT_GetMicros());
                    i = 0;
            }
            prevMicro = currMicro;
        }
    }
    return 0;
}

#endif

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
