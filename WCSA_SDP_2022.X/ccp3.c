/* 
 * File:    ccp3.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 26, 2022, 12:20 PM
 */
//------------------------------------------------------------------------------

// [CCP3 = pinRA2 (echo)], [TMR1 ticks @2MHz, rolls over every 32ms]

#include <xc.h>
#include "ccp3.h"
#include "PIC16Xpress_DevBoard.h"
#include "JSN_Sensor.h"


//==============================================================================
//---------------------------- STATICS VARIABLES -------------------------------
//==============================================================================

static void (*CCP3_CallBack)(uint16_t);
static uint16_t ticksUp, ticksDown;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

static void CCP3_DefaultCallBack(uint16_t capturedValue)
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

void CCP3_Initialize(void)
{
    // Set the CCP3 to the options selected in the User Interface
	
	// CCP3MODE Every edge; CCP3EN enabled; CCP3FMT right_aligned; 
	CCP3CON = 0x83;    
	
	// CCP3CTS0 CCP3 pin; 
	CCP3CAP = 0x00;    
	
	// CCPR3H 0; 
	CCPR3H = 0x00;    
	
	// CCPR3L 0; 
	CCPR3L = 0x00;    
    
    // Set the default call back function for CCP3
    CCP3_SetCallBack(CCP3_DefaultCallBack);

	// Selecting Timer 1
	CCPTMRSbits.C3TSEL = 0x1;
    
    // Clear the CCP3 interrupt flag
    PIR4bits.CCP3IF = 0;

    // Enable the CCP3 interrupt
    PIE4bits.CCP3IE = 1;
}

//------------------------------------------------------------------------------

void CCP3_CaptureISR(void)
{
    CCP3_PERIOD_REG_T module;

    // Clear the CCP3 interrupt flag
    PIR4bits.CCP3IF = 0;
    
    // Copy captured value.
    module.ccpr3l = CCPR3L;
    module.ccpr3h = CCPR3H;
    
    // Return 16bit captured value
    CCP3_CallBack(module.ccpr3_16Bit);
}

//------------------------------------------------------------------------------

void CCP3_SetCallBack(void (*customCallBack)(uint16_t)){
    CCP3_CallBack = customCallBack;
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
