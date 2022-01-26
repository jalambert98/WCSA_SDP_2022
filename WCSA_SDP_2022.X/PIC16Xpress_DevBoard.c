/* 
 * File:    PIC16Xpress_DevBoard.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 25, 2022, 8:50 PM
 */

#include "PIC16Xpress_DevBoard.h"

//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

uint8_t PIC16_Init(void) {
    INTCONbits.GIE = 0b0;   // Temporarily disable global interrupts
    
    // All peripherals enabled by default - (setting to 1 disables)
    // Disable unnecessary timers, etc to reduce power consumption
    PMD0 = 0x00;            // enables CPUclk, FVR, NVM, & IOC
    PMD1 = 0b01010100;      // disables TMR[6,4,2]
    PMD2 = 0b00100000;      // disables ADC unit
    PMD3 = 0b11001000;      // disables CWG[2,1] & CCP4
    PMD4 = 0x00;            // enables UART & MSSP
    PMD5 = 0b00011111;      // disables CLC[4,3,2,1] & DSM
    
    // Manually disable all peripheral interrupts
    PIE0 = 0x00;
    PIE1 = 0x00;
    PIE2 = 0x00;
    PIE3 = 0x00;
    PIE4 = 0x00;
    
    // Manually clear any existing interrupt flags
    PIR0 = 0x00;
    PIR1 = 0x00;
    PIR2 = 0x00;
    PIR3 = 0x00;
    PIR4 = 0x00;
    
    // --- Configure system clock for [F_osc = 8MHz] --- //
    OSCCON1 = 0b01100000;       // Selects HFINTOSC (no PLL) with 1:1 scaling
    while(!OSCCON3bits.ORDY);   // Wait until oscillator is ready
    OSCCON3bits.SOSCBE = 0b1;   // Disables secondary oscillator
    OSCEN = 0b01000000;         // Explicitly enables HFINTOSC
    OSCFRQ = 0b00000100;        // Configures HFINTOSC to [F_osc = 8MHz]
    
    INTCONbits.GIE = 0b1;   // Enable global interrupts
    return SUCCESS;
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
