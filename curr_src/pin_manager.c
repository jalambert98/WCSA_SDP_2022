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
    ANSELA = 0x20;

    /**
    WPUx registers
     */
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;
    
    /* 
     * PMIC status pins
     */
    STAT1_SetInput();
    STAT2_SetInput();
    STAT1_SetPullup();
    STAT2_SetPullup();

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


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
