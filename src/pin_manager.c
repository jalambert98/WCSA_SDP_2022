/* 
 * File:    pin_manager.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: Generated originally by Microchip Code Configurator (MCC) and then
 *       further modified by Jack Lambert
 * 
 * Created on January 26, 2022, 12:35 PM
 */
//------------------------------------------------------------------------------

#include "pin_manager.h"

//------------------------------------------------------------------------------

void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers (all LOW)
    */
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers (all OUTPUT)
    */
    TRISA = 0x37;
    TRISB = 0xF0;
    TRISC = 0xFF;

    /**
    ANSELx registers (all DIGITAL)
    */
    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELA = 0x00;

    /**
    WPUx registers (all DISABLED)
    */
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    ODx registers (all DISABLED)
    */
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;

    /**
    SLRCONx registers (all LIMITED SR)
    */
    SLRCONA = 0x37;
    SLRCONB = 0xF0;
    SLRCONC = 0xFF;

    /**
    INLVLx registers (all SCHMIDT TRIGGERED)
    */
    INLVLA = 0x3F;
    INLVLB = 0xF0;
    INLVLC = 0xFF;
    
    //------------------------------------------------------//
	//--- Peripheral Pin Select [PPS] Module (IO Config) ---//
    //------------------------------------------------------//
    // I2C for VCSEL:  
    // (SCL = RB6), (SDA = RB4)
    
    // EUSART for Lidar:  
    // (TX = RC4), (RX = RB5)
       
    // Input Capture for JSN: 
    // (ECHO1 = RC5), (ECHO2 = RC3), (ECHO3 = RA2)
    
    // Output Compare for Speaker:
    // (SpeakerTone = RA4)   
    
    // PWM for Motor:
    // (MotorControl = RB6)
}

//------------------------------------------------------------------------------

void PIN_MANAGER_IOC(void)
{   
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
