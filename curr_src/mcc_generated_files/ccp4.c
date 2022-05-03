/**
  CCP4 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp4.c

  @Summary
    This is the generated driver implementation file for the CCP4 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for CCP4.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18345
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
         MPLAB 	          :  MPLAB X 5.45
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "ccp4.h"

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

void CCP4_SetCompareCount(uint16_t compareCount)
{
    CCP4_PERIOD_REG_T module;
    
    // Write the 16-bit compare value
    module.ccpr4_16Bit = compareCount;
    
    CCPR4L = module.ccpr4l;
    CCPR4H = module.ccpr4h;
}

bool CCP4_OutputStatusGet(void)
{
    // Returns the output status
    return(CCP4CONbits.CCP4OUT);
}

void CCP4_CompareISR(void)
{
    // Clear the CCP4 interrupt flag
    PIR4bits.CCP4IF = 0;
    
    // Add user code here
}
/**
 End of File
*/