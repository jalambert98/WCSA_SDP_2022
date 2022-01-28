/**
  CCP2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp2.c

  @Summary
    This is the generated driver implementation file for the CCP2 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for CCP2.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18345
        Driver Version    :  2.1.3
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
#include "ccp2.h"

static void (*CCP2_CallBack)(uint16_t);

/**
  Section: Capture Module APIs:
*/

static void CCP2_DefaultCallBack(uint16_t capturedValue)
{
    // Add your code here
}

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

void CCP2_SetCallBack(void (*customCallBack)(uint16_t)){
    CCP2_CallBack = customCallBack;
}
/**
 End of File
*/