/* 
 * File:    PIC16Xpress_DevBoard.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 25, 2022, 8:50 PM
 */

#include "PIC16Xpress_DevBoard.h"
#include "FR_Timer.h"

//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void PIC16_Init(void) {
    // Initialize hardware libraries
    SYSTEM_Initialize();
    
    // Manually disable all peripheral interrupts
    PIE0 = 0x00;
    PIE1 = 0x00;
    PIE2 = 0x00;
    PIE3 = 0x00;
    PIE4 = 0x00;
    
    // Initialize GPIO pins
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    
    TRISA = 0x37;
    TRISB = 0xF0;
    TRISC = 0xFF;
    
    ANSELC = 0xFF;
    ANSELB = 0xF0;
    ANSELA = 0x37;
    
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;
    
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    
    SLRCONA = 0x37;
    SLRCONB = 0xF0;
    SLRCONC = 0xFF;
    
    INLVLA = 0x3F;
    INLVLB = 0xF0;
    INLVLC = 0xFF;
    
    // Manually clear any existing interrupt flags
    PIR0 = 0x00;
    PIR1 = 0x00;
    PIR2 = 0x00;
    PIR3 = 0x00;
    PIR4 = 0x00;
    
    INTCONbits.GIE = HIGH;      // Enable global interrupts
}

//==============================================================================
//----------------------- General Purpose ISR Manager --------------------------
//==============================================================================

void __interrupt() InterruptManager (void)
{
    if(PIE0bits.TMR0IE && PIR0bits.TMR0IF) {
        FR_Timer_IncMillis();
        FR_Timer_IncMicros();
        PIR0bits.TMR0IF = LOW;
    }
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
