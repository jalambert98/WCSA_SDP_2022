/* 
 * File:    pin_manager.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: Generated originally by Microchip Code Configurator (MCC) and then
 *       further modified by Jack Lambert
 * 
 * Created on February 8, 2022, 2:15 PM
 */
//------------------------------------------------------------------------------

#include "pin_manager.h"


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

uint8_t PIC16_SetPin(PinName_t pin, uint8_t io) {
    // 
    switch (io) {
        case INPUT:
        case OUTPUT:
            break;
        default:
            return ERROR;
    }

    switch (pin) {
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

uint8_t PIC16_ReadPin(PinName_t pin) {
    switch (pin) {
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

uint8_t PIC16_WritePin(PinName_t pin, uint8_t val) {
    switch (val) {
        case HIGH:
        case LOW:
            break;
        default:
            return ERROR;
    }

    switch (pin) {
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
//------------------------------------------------------------------------------

void PIN_MANAGER_Initialize(void) {
    /**
    LATx registers
     */
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
     */
    TRISA = 0x27;
    TRISB = 0x70;
    TRISC = 0xAD;

    /**
    ANSELx registers
     */
    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELA = 0x22;

    /**
    WPUx registers
     */
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    ODx registers
     */
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;

    /**
    SLRCONx registers
     */
    SLRCONA = 0x37;
    SLRCONB = 0xF0;
    SLRCONC = 0xFF;

    /**
    INLVLx registers
     */
    INLVLA = 0x3F;
    INLVLB = 0xF0;
    INLVLC = 0xFF;    
}

//------------------------------------------------------------------------------

void PIN_MANAGER_IOC(void) {
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
