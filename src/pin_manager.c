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
    LATx registers
    */
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0x27;
    TRISB = 0xB0;
    TRISC = 0xEF;

    /**
    ANSELx registers
    */
    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELA = 0x00;

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
    
    //------------------------------------------------------//
	//--- Peripheral Pin Select [PPS] Module (IO Config) ---//
    //------------------------------------------------------//
    // I2C for VCSEL:  
    // (SCL = RC0), (SDA = RC1)
    RC0PPS = 0x18;          //RC0->MSSP1:SCL1;  
    SSP1CLKPPS = 0x10;      //RC0->MSSP1:SCL1; 
    RC1PPS = 0x19;          //RC1->MSSP1:SDA1; 
    SSP1DATPPS = 0x11;      //RC1->MSSP1:SDA1;  
    
    // EUSART for Lidar:  
    // (TX = RC4), (RX = RB5)
    RXPPS = 0x0D;           //RB5->EUSART:RX; 
    RC4PPS = 0x14;          //RC4->EUSART:TX;
       
    // Input Capture for JSN: 
    // (ECHO1 = RC5), (ECHO2 = RC3), (ECHO3 = RA2)
    CCP1PPS = 0x15;         //RC5->CCP1:CCP1; 
    CCP2PPS = 0x13;         //RC3->CCP2:CCP2; 
    CCP3PPS = 0x02;         //RA2->CCP3:CCP3; 
    
    // Output Compare for Speaker:
    // (SpeakerTone = RA4)
    RA4PPS = 0x0F;          //RA4->CCP4:CCP4;    
    
    // PWM for Motor:
    // (MotorControl = RB6)
    RB6PPS = 0x02;          //RB6->PWM5:PWM5;    
         
}

//------------------------------------------------------------------------------

void PIN_MANAGER_IOC(void)
{   
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
