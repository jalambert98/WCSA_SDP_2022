/* 
 * File:    ccp2.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 26, 2022, 12:20 PM
 */
//------------------------------------------------------------------------------

// [CCP2 = pinRC3 (echo)], [TMR1 ticks @2MHz, rolls over every 32ms]

#include <xc.h>
#include "ccp2.h"
#include "PIC16Xpress_DevBoard.h"
#include "JSN_Sensor.h"


//==============================================================================
//---------------------------- STATICS VARIABLES -------------------------------
//==============================================================================

static void (*CCP2_CallBack)(uint16_t);
static uint16_t ticksUp, ticksDown;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

static void CCP2_DefaultCallBack(uint16_t capturedValue)
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

void CCP2_Initialize(void)
{
    // Set the CCP2 to the options selected in the User Interface
	
	// CCP2MODE Every edge; CCP2EN enabled; CCP2FMT right_aligned; 
	CCP2CON = 0x83;    
	
	// CCP2CTS0 CCP2 pin; 
	CCP2CAP = 0x00;    
	
	// CCPR2H 0; 
	CCPR2H = 0x00;    
	
	// CCPR2L 0; 
	CCPR2L = 0x00;    
    
    // Set the default call back function for CCP2
    CCP2_SetCallBack(CCP2_DefaultCallBack);

	// Selecting Timer 1
	CCPTMRSbits.C2TSEL = 0x1;
    
    // Clear the CCP2 interrupt flag
    PIR4bits.CCP2IF = 0;

    // Enable the CCP2 interrupt
    PIE4bits.CCP2IE = 1;
}

//------------------------------------------------------------------------------

void CCP2_CaptureISR(void)
{
    CCP2_PERIOD_REG_T module;

    // Clear the CCP2 interrupt flag
    PIR4bits.CCP2IF = 0;
    
    // Copy captured value.
    module.ccpr2l = CCPR2L;
    module.ccpr2h = CCPR2H;
    
    // Return 16bit captured value
    CCP2_CallBack(module.ccpr2_16Bit);
}

//------------------------------------------------------------------------------

void CCP2_SetCallBack(void (*customCallBack)(uint16_t)){
    CCP2_CallBack = customCallBack;
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
