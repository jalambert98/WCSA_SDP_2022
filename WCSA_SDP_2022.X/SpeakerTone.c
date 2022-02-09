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
        currFreq = newFrequency;
        ocCount = (uint16_t)((uint32_t)2000000 / newFrequency);
        CCP4_SetCompareCount(ocCount);
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

int main(void) {
    PIC16_Init();
    SpeakerTone_Init();
    SpeakerTone_On();
    
    SetPin(C0, OUTPUT);
    WritePin(C0, LOW);
    
    while(1);
    return 0;
}

#endif

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
