
#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

//------------------------------------------------------------------------------
/**
  Section: Included Files
 */

#include <xc.h>

//------------------------------------------------------------------------------

#define HIGH                1
#define LOW                 0

#define INPUT               1
#define OUTPUT              0

#define SUCCESS             0x00
#define ERROR               0xFF

#define TRUE                1
#define FALSE               0

// General pin manipulation
#define SET_A0()            TRISAbits.TRISA0
#define SET_A1()            TRISAbits.TRISA1
#define SET_A2()            TRISAbits.TRISA2
#define SET_A4()            TRISAbits.TRISA4
#define SET_A5()            TRISAbits.TRISA5
#define SET_B4()            TRISBbits.TRISB4
#define SET_B5()            TRISBbits.TRISB5
#define SET_B6()            TRISBbits.TRISB6
#define SET_B7()            TRISBbits.TRISB7
#define SET_C0()            TRISCbits.TRISC0
#define SET_C1()            TRISCbits.TRISC1
#define SET_C2()            TRISCbits.TRISC2
#define SET_C3()            TRISCbits.TRISC3
#define SET_C4()            TRISCbits.TRISC4
#define SET_C5()            TRISCbits.TRISC5
#define SET_C6()            TRISCbits.TRISC6
#define SET_C7()            TRISCbits.TRISC7

#define READ_A0()           PORTAbits.RA0
#define READ_A1()           PORTAbits.RA1
#define READ_A2()           PORTAbits.RA2
#define READ_A4()           PORTAbits.RA4
#define READ_A5()           PORTAbits.RA5
#define READ_B4()           PORTBbits.RB4
#define READ_B5()           PORTBbits.RB5
#define READ_B6()           PORTBbits.RB6
#define READ_B7()           PORTBbits.RB7
#define READ_C0()           PORTCbits.RC0
#define READ_C1()           PORTCbits.RC1
#define READ_C2()           PORTCbits.RC2
#define READ_C3()           PORTCbits.RC3
#define READ_C4()           PORTCbits.RC4
#define READ_C5()           PORTCbits.RC5
#define READ_C6()           PORTCbits.RC6
#define READ_C7()           PORTCbits.RC7

#define WRITE_A0()          LATAbits.LATA0
#define WRITE_A1()          LATAbits.LATA1
#define WRITE_A2()          LATAbits.LATA2
#define WRITE_A4()          LATAbits.LATA4
#define WRITE_A5()          LATAbits.LATA5
#define WRITE_B4()          LATBbits.LATB4
#define WRITE_B5()          LATBbits.LATB5
#define WRITE_B6()          LATBbits.LATB6
#define WRITE_B7()          LATBbits.LATB7
#define WRITE_C0()          LATCbits.LATC0
#define WRITE_C1()          LATCbits.LATC1
#define WRITE_C2()          LATCbits.LATC2
#define WRITE_C3()          LATCbits.LATC3
#define WRITE_C4()          LATCbits.LATC4
#define WRITE_C5()          LATCbits.LATC5
#define WRITE_C6()          LATCbits.LATC6
#define WRITE_C7()          LATCbits.LATC7

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA2 procedures
#define RA2_SetPullup()             do { WPUAbits.WPUA2 = 1; } while(0)
#define RA2_ResetPullup()           do { WPUAbits.WPUA2 = 0; } while(0)
#define RA2_SetAnalogMode()         do { ANSELAbits.ANSA2 = 1; } while(0)
#define RA2_SetDigitalMode()        do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetPullup()             do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()           do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()         do { ANSELAbits.ANSA4 = 1; } while(0)
#define RA4_SetDigitalMode()        do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set vBat aliases
#define vBat_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define vBat_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define vBat_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define vBat_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define vBat_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define vBat_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set IO_RB4 aliases
#define IO_RB4_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_RB4_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_RB4_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IO_RB4_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IO_RB4_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define IO_RB4_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set IO_RB6 aliases
#define IO_RB6_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define IO_RB6_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define IO_RB6_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define IO_RB6_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define IO_RB6_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define IO_RB6_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set spkrSdwn aliases
#define spkrSdwn_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define spkrSdwn_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define spkrSdwn_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define spkrSdwn_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define spkrSdwn_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define spkrSdwn_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set IO_RC0 aliases
#define IO_RC0_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define IO_RC0_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define IO_RC0_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define IO_RC0_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define IO_RC0_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define IO_RC0_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set RC1 procedures
#define RC1_SetPullup()             do { WPUCbits.WPUC1 = 1; } while(0)
#define RC1_ResetPullup()           do { WPUCbits.WPUC1 = 0; } while(0)
#define RC1_SetAnalogMode()         do { ANSELCbits.ANSC1 = 1; } while(0)
#define RC1_SetDigitalMode()        do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set IO_RC2 aliases
#define IO_RC2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define IO_RC2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define IO_RC2_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define IO_RC2_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define IO_RC2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define IO_RC2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set IO_RC3 aliases
#define IO_RC3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_RC3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define IO_RC3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define IO_RC3_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set IO_RC5 aliases
#define IO_RC5_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define IO_RC5_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define IO_RC5_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define IO_RC5_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define IO_RC5_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define IO_RC5_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set spkrGainSel aliases
#define spkrGainSel_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define spkrGainSel_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define spkrGainSel_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define spkrGainSel_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define spkrGainSel_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define spkrGainSel_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set IO_RC7 aliases
#define IO_RC7_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define IO_RC7_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define IO_RC7_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define IO_RC7_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define IO_RC7_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define IO_RC7_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)


//==============================================================================
//-------------------------------- TYPEDEFS ------------------------------------
//==============================================================================

typedef enum {
    A5, A4, A3,
    C5, C4, C3,
    C6, C7, B7,
    A0, A1, A2,
    C0, C1, C2,
    B4, B5, B6
} PinName_t;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

uint8_t PIC16_SetPin(PinName_t pin, uint8_t io);

//------------------------------------------------------------------------------

uint8_t PIC16_ReadPin(PinName_t pin);

//------------------------------------------------------------------------------

uint8_t PIC16_WritePin(PinName_t pin, uint8_t val);

//------------------------------------------------------------------------------
/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
 */
void PIN_MANAGER_Initialize(void);

//------------------------------------------------------------------------------
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 */
void PIN_MANAGER_IOC(void);

//------------------------------------------------------------------------------

#endif // PIN_MANAGER_H

//------------------------------------------------------------------------------
/**
 End of File
 */
