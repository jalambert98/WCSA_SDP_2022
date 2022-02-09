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

#define SPEAKERTONE_TEST


//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

uint16_t currFreq, ocCount;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void SpeakerTone_Init(void) {
    SetPin(C1, OUTPUT);
    WritePin(C1, LOW);
    currFreq = DEFAULT_TONE;
    ocCount = DEFAULT_OCCOUNT;
    SpeakerTone_Off();
}

//------------------------------------------------------------------------------

uint8_t SpeakerTone_SetFrequency(uint16_t newFrequency) {
    if((newFrequency < 100)||(newFrequency > 10000))
        return ERROR;
    else {
        SpeakerTone_Off();
        currFreq = newFrequency;
        ocCount = (uint16_t)(0x001E8480 / newFrequency);
        CCP4_SetCompareCount(ocCount);
        SpeakerTone_On();
        return SUCCESS;
    }
}

//------------------------------------------------------------------------------

uint16_t SpeakerTone_GetFrequency(void) {
    return currFreq;
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
#define FREQ_CHANGE_RATE    500     // change speakerTone freq every 500ms

int main(void) {
    PIC16_Init();
    SpeakerTone_Init(); // speakerTone pinRC1
    
    unsigned long currMilli = FRT_GetMillis();
    unsigned long prevMilli = currMilli;
    SpeakerTone_SetFrequency(TONE_C4);
    uint8_t i = 0;
    SpeakerTone_On();

    // arpeggio (C->G->C) triplets (changes pitch every 500ms)
    while(1) {
        currMilli = FRT_GetMillis();
        if((currMilli - prevMilli) > FREQ_CHANGE_RATE) {
            switch(i) {
                case 0:
                    SpeakerTone_SetFrequency(TONE_C4);
                    i++;
                    break;
                case 1:
                    SpeakerTone_SetFrequency(TONE_G4);
                    i++;
                    break;
                case 2:
                    SpeakerTone_SetFrequency(TONE_C5);
                    i -=2;
                    break;
            }
            prevMilli = currMilli;
        }
    }
    return 0;
}

#endif

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
