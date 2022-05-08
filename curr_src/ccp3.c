
/**
  Section: Included Files
*/

#include <xc.h>
#include "ccp3.h"

//------------------------------------------------------------------------------

static void (*CCP3_CallBack)(uint16_t);

//------------------------------------------------------------------------------
/**
  Section: Capture Module APIs:
*/

static void CCP3_DefaultCallBack(uint16_t capturedValue)
{
    // Add your code here
}

//------------------------------------------------------------------------------

void CCP3_Initialize(void)
{
    // Set the CCP3 to the options selected in the User Interface
	
	// CCP3MODE Falling edge; CCP3EN enabled; CCP3FMT right_aligned; 
	CCP3CON = 0x84;    
	
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

//------------------------------------------------------------------------------
/**
 End of File
*/
