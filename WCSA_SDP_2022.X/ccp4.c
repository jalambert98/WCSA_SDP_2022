/* 
 * File:    ccp4.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on February 8, 2022, 2:15 PM
 */
//------------------------------------------------------------------------------

// [CCP4 = pinRC1 (SpeakerTone output)], [TMR3 ticks @4MHz & rolls over after 16-bit range]

#include <xc.h>
#include "ccp4.h"
#include "PIC16Xpress_DevBoard.h"

//------------------------------------------------------------------------------

void CCP4_Initialize(void)
{
	// CCP4MODE Toggle_cleartmr; CCP4OUT 0; CCP4EN enabled; CCP4FMT right_aligned; 
	CCP4CON = 0x81;    
	
    // Initialize OC value to Default 440Hz speakerTone
	CCPR4H = 0x11;     
	CCPR4L = 0xC1;    

	// Selecting Timer 3
	CCPTMRSbits.C4TSEL = 0x2;
    
    // Clear the CCP4 interrupt flag
    PIR4bits.CCP4IF = 0;

    // Enable the CCP4 interrupt
    PIE4bits.CCP4IE = 1;
}

//------------------------------------------------------------------------------

void CCP4_SetCompareCount(uint16_t compareCount)
{
    /*
    CCP4_PERIOD_REG_T module;
    
    // Write the 16-bit compare value
    module.ccpr4_16Bit = compareCount;
    
    CCPR4L = module.ccpr4l;
    CCPR4H = module.ccpr4h;
     */
    CCPR4L = compareCount & 0x00FF;
    CCPR4H = ((compareCount & 0xFF00)>>8);
}

//------------------------------------------------------------------------------

bool CCP4_OutputStatusGet(void)
{
    // Returns the output status
    return(CCP4CONbits.CCP4OUT);
}

//------------------------------------------------------------------------------

void CCP4_CompareISR(void)
{
    // Clear the CCP4 interrupt flag
    PIR4bits.CCP4IF = 0;
    WritePin(C0, HIGH);
    // Add user code here
}

//------------------------------------------------------------------------------
