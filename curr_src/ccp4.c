
/**
  Section: Included Files
*/

#include <xc.h>
#include "ccp4.h"

//------------------------------------------------------------------------------
/**
  Section: Compare Module APIs:
*/

void CCP4_Initialize(void)
{
    // Set the CCP4 to the options selected in the User Interface
	
	// CCP4MODE Toggle_cleartmr; CCP4OUT 0; CCP4EN enabled; CCP4FMT right_aligned; 
	CCP4CON = 0x81;    
	
	// CCPR4H 0; 
	CCPR4H = 0x00;    
	
	// CCPR4L 0; 
	CCPR4L = 0x00;    

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
    CCP4_PERIOD_REG_T module;
    
    // Write the 16-bit compare value
    module.ccpr4_16Bit = compareCount;
    
    CCPR4L = module.ccpr4l;
    CCPR4H = module.ccpr4h;
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
    
    // Add user code here
}

//------------------------------------------------------------------------------
/**
 End of File
*/
