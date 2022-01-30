
#include "pin_manager.h"

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
    TRISA = 0x37;
    TRISB = 0xF0;
    TRISC = 0xFF;

    /**
    ANSELx registers
    */
    ANSELC = 0xD7;
    ANSELB = 0xF0;
    ANSELA = 0x33;

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

    RXPPS = 0x0D;   //RB5->EUSART:RX;    
    CCP2PPS = 0x13;   //RC3->CCP2:CCP2;    
    CCP3PPS = 0x02;   //RA2->CCP3:CCP3;    
    RC4PPS = 0x14;   //RC4->EUSART:TX;    
    CCP1PPS = 0x15;   //RC5->CCP1:CCP1;   
}
  
void PIN_MANAGER_IOC(void)
{   
}

/**
 End of File
*/