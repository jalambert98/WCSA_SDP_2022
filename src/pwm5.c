/* 
 * File:    pwm5.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: Generated originally by Microchip Code Configurator (MCC) and then
 *       further modified by Jack Lambert
 * 
 * Created on February 8, 2022, 2:15 PM
 */
//------------------------------------------------------------------------------

#include <xc.h>
#include "pwm5.h"
#include "PIC16Xpress_DevBoard.h"

// PWM5 output --> pinRC1
//------------------------------------------------------------------------------

void PWM5_Initialize(void) {
    TRISCbits.TRISC1 = OUTPUT;
    LATCbits.LATC1 = LOW;
    
    // Peripheral pin select [PPS] module config
    RC1PPS = 0x02;          //RC1->PWM5:PWM5; 
    
    // PWM5POL active_hi; PWM5EN enabled; 
    PWM5CON = 0x80;   

    // PWM5DCH 0; 
    PWM5DCH = 0x00;   

    // PWM5DCL 0; 
    PWM5DCL = 0x00;   

    // Select timer
    PWMTMRSbits.P5TSEL = 1;
}

//------------------------------------------------------------------------------

void PWM5_LoadDutyValue(uint16_t dutyValue) {
    // Writing to 8 MSBs of PWM duty cycle in PWMDCH register
    PWM5DCH = (dutyValue & 0x03FC) >> 2;

    // Writing to 2 LSBs of PWM duty cycle in PWMDCL register
    PWM5DCL = (dutyValue & 0x0003) << 6;
}

//------------------------------------------------------------------------------
/**
 End of File
 */
