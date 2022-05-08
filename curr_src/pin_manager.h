
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
#define RA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RA2_GetValue()              PORTAbits.RA2
#define RA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RA2_SetPullup()             do { WPUAbits.WPUA2 = 1; } while(0)
#define RA2_ResetPullup()           do { WPUAbits.WPUA2 = 0; } while(0)
#define RA2_SetAnalogMode()         do { ANSELAbits.ANSA2 = 1; } while(0)
#define RA2_SetDigitalMode()        do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()              PORTAbits.RA4
#define RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()             do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()           do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()         do { ANSELAbits.ANSA4 = 1; } while(0)
#define RA4_SetDigitalMode()        do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set vBat aliases
#define vBat_TRIS                 TRISAbits.TRISA5
#define vBat_LAT                  LATAbits.LATA5
#define vBat_PORT                 PORTAbits.RA5
#define vBat_WPU                  WPUAbits.WPUA5
#define vBat_OD                   ODCONAbits.ODCA5
#define vBat_ANS                  ANSELAbits.ANSA5
#define vBat_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define vBat_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define vBat_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define vBat_GetValue()           PORTAbits.RA5
#define vBat_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define vBat_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define vBat_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define vBat_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define vBat_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define vBat_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define vBat_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define vBat_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set IO_RB4 aliases
#define IO_RB4_TRIS                 TRISBbits.TRISB4
#define IO_RB4_LAT                  LATBbits.LATB4
#define IO_RB4_PORT                 PORTBbits.RB4
#define IO_RB4_WPU                  WPUBbits.WPUB4
#define IO_RB4_OD                   ODCONBbits.ODCB4
#define IO_RB4_ANS                  ANSELBbits.ANSB4
#define IO_RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_RB4_GetValue()           PORTBbits.RB4
#define IO_RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IO_RB4_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_RB4_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_RB4_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IO_RB4_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IO_RB4_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define IO_RB4_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set IO_RB6 aliases
#define IO_RB6_TRIS                 TRISBbits.TRISB6
#define IO_RB6_LAT                  LATBbits.LATB6
#define IO_RB6_PORT                 PORTBbits.RB6
#define IO_RB6_WPU                  WPUBbits.WPUB6
#define IO_RB6_OD                   ODCONBbits.ODCB6
#define IO_RB6_ANS                  ANSELBbits.ANSB6
#define IO_RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define IO_RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define IO_RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define IO_RB6_GetValue()           PORTBbits.RB6
#define IO_RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define IO_RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define IO_RB6_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define IO_RB6_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define IO_RB6_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define IO_RB6_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define IO_RB6_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define IO_RB6_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set spkrSdwn aliases
#define spkrSdwn_TRIS                 TRISBbits.TRISB7
#define spkrSdwn_LAT                  LATBbits.LATB7
#define spkrSdwn_PORT                 PORTBbits.RB7
#define spkrSdwn_WPU                  WPUBbits.WPUB7
#define spkrSdwn_OD                   ODCONBbits.ODCB7
#define spkrSdwn_ANS                  ANSELBbits.ANSB7
#define spkrSdwn_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define spkrSdwn_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define spkrSdwn_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define spkrSdwn_GetValue()           PORTBbits.RB7
#define spkrSdwn_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define spkrSdwn_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define spkrSdwn_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define spkrSdwn_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define spkrSdwn_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define spkrSdwn_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define spkrSdwn_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define spkrSdwn_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set IO_RC0 aliases
#define IO_RC0_TRIS                 TRISCbits.TRISC0
#define IO_RC0_LAT                  LATCbits.LATC0
#define IO_RC0_PORT                 PORTCbits.RC0
#define IO_RC0_WPU                  WPUCbits.WPUC0
#define IO_RC0_OD                   ODCONCbits.ODCC0
#define IO_RC0_ANS                  ANSELCbits.ANSC0
#define IO_RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define IO_RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define IO_RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define IO_RC0_GetValue()           PORTCbits.RC0
#define IO_RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define IO_RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define IO_RC0_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define IO_RC0_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define IO_RC0_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define IO_RC0_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define IO_RC0_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define IO_RC0_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set RC1 procedures
#define RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RC1_GetValue()              PORTCbits.RC1
#define RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define RC1_SetPullup()             do { WPUCbits.WPUC1 = 1; } while(0)
#define RC1_ResetPullup()           do { WPUCbits.WPUC1 = 0; } while(0)
#define RC1_SetAnalogMode()         do { ANSELCbits.ANSC1 = 1; } while(0)
#define RC1_SetDigitalMode()        do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set IO_RC2 aliases
#define IO_RC2_TRIS                 TRISCbits.TRISC2
#define IO_RC2_LAT                  LATCbits.LATC2
#define IO_RC2_PORT                 PORTCbits.RC2
#define IO_RC2_WPU                  WPUCbits.WPUC2
#define IO_RC2_OD                   ODCONCbits.ODCC2
#define IO_RC2_ANS                  ANSELCbits.ANSC2
#define IO_RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define IO_RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define IO_RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define IO_RC2_GetValue()           PORTCbits.RC2
#define IO_RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define IO_RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define IO_RC2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define IO_RC2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define IO_RC2_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define IO_RC2_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define IO_RC2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define IO_RC2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set IO_RC3 aliases
#define IO_RC3_TRIS                 TRISCbits.TRISC3
#define IO_RC3_LAT                  LATCbits.LATC3
#define IO_RC3_PORT                 PORTCbits.RC3
#define IO_RC3_WPU                  WPUCbits.WPUC3
#define IO_RC3_OD                   ODCONCbits.ODCC3
#define IO_RC3_ANS                  ANSELCbits.ANSC3
#define IO_RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_RC3_GetValue()           PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_RC3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_RC3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define IO_RC3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define IO_RC3_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set IO_RC5 aliases
#define IO_RC5_TRIS                 TRISCbits.TRISC5
#define IO_RC5_LAT                  LATCbits.LATC5
#define IO_RC5_PORT                 PORTCbits.RC5
#define IO_RC5_WPU                  WPUCbits.WPUC5
#define IO_RC5_OD                   ODCONCbits.ODCC5
#define IO_RC5_ANS                  ANSELCbits.ANSC5
#define IO_RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define IO_RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define IO_RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define IO_RC5_GetValue()           PORTCbits.RC5
#define IO_RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define IO_RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define IO_RC5_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define IO_RC5_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define IO_RC5_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define IO_RC5_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define IO_RC5_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define IO_RC5_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set spkrGainSel aliases
#define spkrGainSel_TRIS                 TRISCbits.TRISC6
#define spkrGainSel_LAT                  LATCbits.LATC6
#define spkrGainSel_PORT                 PORTCbits.RC6
#define spkrGainSel_WPU                  WPUCbits.WPUC6
#define spkrGainSel_OD                   ODCONCbits.ODCC6
#define spkrGainSel_ANS                  ANSELCbits.ANSC6
#define spkrGainSel_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define spkrGainSel_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define spkrGainSel_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define spkrGainSel_GetValue()           PORTCbits.RC6
#define spkrGainSel_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define spkrGainSel_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define spkrGainSel_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define spkrGainSel_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define spkrGainSel_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define spkrGainSel_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define spkrGainSel_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define spkrGainSel_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set IO_RC7 aliases
#define IO_RC7_TRIS                 TRISCbits.TRISC7
#define IO_RC7_LAT                  LATCbits.LATC7
#define IO_RC7_PORT                 PORTCbits.RC7
#define IO_RC7_WPU                  WPUCbits.WPUC7
#define IO_RC7_OD                   ODCONCbits.ODCC7
#define IO_RC7_ANS                  ANSELCbits.ANSC7
#define IO_RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define IO_RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define IO_RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define IO_RC7_GetValue()           PORTCbits.RC7
#define IO_RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define IO_RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
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
