/* 
 * File:    PIC16Xpress_DevBoard.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 25, 2022, 8:50 PM
 */
//------------------------------------------------------------------------------

#include "PIC16Xpress_DevBoard.h"

//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void PIC16_Init(void) {
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
    
    SYSTEM_Initialize();
    
    INTCONbits.GIE = HIGH;      // Enable global interrupts
}

//------------------------------------------------------------------------------

uint8_t SetPin(PinName_t pin, uint8_t io) {
    switch(pin) {
        case A5:
            SET_A5() = io;
            return SUCCESS;
        case A4:
            SET_A4() = io;
            return SUCCESS;
        case A3:
            return ERROR;
        case C5:
            SET_C5() = io;
            return SUCCESS;
        case C4:
            SET_C4() = io;
            return SUCCESS;
        case C3:
            SET_C3() = io;
            return SUCCESS;
        case C6:
            SET_C6() = io;
            return SUCCESS;
        case C7:
            SET_C7() = io;
            return SUCCESS;
        case B7:
            SET_B7() = io;
            return SUCCESS;
        case A0:
            SET_A0() = io;
            return SUCCESS;
        case A1:
            SET_A1() = io;
            return SUCCESS;
        case A2:
            SET_A2() = io;
            return SUCCESS;
        case C0:
            SET_C0() = io;
            return SUCCESS;
        case C1:
            SET_C1() = io;
            return SUCCESS;
        case C2:
            SET_C2() = io;
            return SUCCESS;
        case B4:
            SET_B4() = io;
            return SUCCESS;
        case B5:
            SET_B5() = io;
            return SUCCESS;
        case B6:
            SET_B6() = io;
            return SUCCESS;
        default:
            return ERROR;
    }
}

//------------------------------------------------------------------------------

uint8_t ReadPin(PinName_t pin) {
    switch(pin) {
        case A5:
            return READ_A5();
        case A4:
            return READ_A4();
        case A3:
            return ERROR;
        case C5:
            return READ_C5();
        case C4:
            return READ_C4();
        case C3:
            return READ_C3();
        case C6:
            return READ_C6();
        case C7:
            return READ_C7();
        case B7:
            return READ_B7();
        case A0:
            return READ_A0();
        case A1:
            return READ_A1();
        case A2:
            return READ_A2();
        case C0:
            return READ_C0();
        case C1:
            return READ_C1();
        case C2:
            return READ_C2();
        case B4:
            return READ_B4();
        case B5:
            return READ_B5();
        case B6:
            return READ_B6();
        default:
            return ERROR;
    }
}

//------------------------------------------------------------------------------

uint8_t WritePin(PinName_t pin, uint8_t val) {
    switch(pin) {
        case A5:
            WRITE_A5() = val;
            return SUCCESS;
        case A4:
            WRITE_A4() = val;
            return SUCCESS;
        case A3:
            return ERROR;
        case C5:
            WRITE_C5() = val;
            return SUCCESS;
        case C4:
            WRITE_C4() = val;
            return SUCCESS;
        case C3:
            WRITE_C3() = val;
            return SUCCESS;
        case C6:
            WRITE_C6() = val;
            return SUCCESS;
        case C7:
            WRITE_C7() = val;
            return SUCCESS;
        case B7:
            WRITE_B7() = val;
            return SUCCESS;
        case A0:
            WRITE_A0() = val;
            return SUCCESS;
        case A1:
            WRITE_A1() = val;
            return SUCCESS;
        case A2:
            WRITE_A2() = val;
            return SUCCESS;
        case C0:
            WRITE_C0() = val;
            return SUCCESS;
        case C1:
            WRITE_C1() = val;
            return SUCCESS;
        case C2:
            WRITE_C2() = val;
            return SUCCESS;
        case B4:
            WRITE_B4() = val;
            return SUCCESS;
        case B5:
            WRITE_B5() = val;
            return SUCCESS;
        case B6:
            WRITE_B6() = val;
            return SUCCESS;
        default:
            return ERROR;
    }
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
