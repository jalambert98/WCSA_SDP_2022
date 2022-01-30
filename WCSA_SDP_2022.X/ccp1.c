/* 
 * File:    ccp1.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 26, 2022, 12:20 PM
 */
//------------------------------------------------------------------------------

// [CCP1 = pinRC5 (echo)], [TMR1 ticks @2MHz, rolls over every 32ms]

#include "ccp1.h"
#include "PIC16Xpress_DevBoard.h"
#include "JSN_Sensor.h"

//==============================================================================
//---------------------------- STATICS VARIABLES -------------------------------
//==============================================================================

static void (*CCP1_CallBack)(uint16_t);
static uint16_t ticksUp, ticksDown;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

static void CCP1_DefaultCallBack(uint16_t capturedValue)
{
    switch(ReadPin(JSN_GetLastTrig()->echoPin)) {
        // If pin RC5 is high on this ISR, store ticks
        case HIGH:
            ticksUp = capturedValue;
            break;
        // If pin RC5 is low on this ISR, store ticks & calculate highTime
        case LOW:
            ticksDown = capturedValue;
            JSN_GetLastTrig()->echoHighTime = ((ticksDown - ticksUp)>>1);
            break;
    }
}

//------------------------------------------------------------------------------

void CCP1_Initialize(void)
{
    // Set the CCP1 to the options selected in the User Interface
	
	// CCP1MODE Every edge; CCP1EN enabled; CCP1FMT right_aligned; 
	CCP1CON = 0x83;    
	
	// CCP1CTS0 CCP1 pin; 
	CCP1CAP = 0x00;    
	
	// CCPR1H 0; 
	CCPR1H = 0x00;    
	
	// CCPR1L 0; 
	CCPR1L = 0x00;    
    
    // Set the default call back function for CCP1
    CCP1_SetCallBack(CCP1_DefaultCallBack);

	// Selecting Timer 1
	CCPTMRSbits.C1TSEL = 0x1;
    
    // Clear the CCP1 interrupt flag
    PIR4bits.CCP1IF = 0;

    // Enable the CCP1 interrupt
    PIE4bits.CCP1IE = 1;
}

//------------------------------------------------------------------------------

void CCP1_CaptureISR(void)
{
    CCP1_PERIOD_REG_T module;

    // Clear the CCP1 interrupt flag
    PIR4bits.CCP1IF = 0;
    
    // Copy captured value.
    module.ccpr1l = CCPR1L;
    module.ccpr1h = CCPR1H;
    
    // Return 16bit captured value
    CCP1_CallBack(module.ccpr1_16Bit);
}

//------------------------------------------------------------------------------

void CCP1_SetCallBack(void (*customCallBack)(uint16_t)){
    CCP1_CallBack = customCallBack;
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
