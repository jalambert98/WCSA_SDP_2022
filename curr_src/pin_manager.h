/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18345
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

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

// get/set PM_STAT1 aliases
#define PM_STAT1_TRIS                 TRISBbits.TRISB4
#define PM_STAT1_LAT                  LATBbits.LATB4
#define PM_STAT1_PORT                 PORTBbits.RB4
#define PM_STAT1_WPU                  WPUBbits.WPUB4
#define PM_STAT1_OD                   ODCONBbits.ODCB4
#define PM_STAT1_ANS                  ANSELBbits.ANSB4
#define PM_STAT1_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define PM_STAT1_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define PM_STAT1_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define PM_STAT1_GetValue()           PORTBbits.RB4
#define PM_STAT1_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define PM_STAT1_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define PM_STAT1_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define PM_STAT1_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define PM_STAT1_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define PM_STAT1_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define PM_STAT1_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define PM_STAT1_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

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

// get/set NA_1 aliases
#define NA_1_TRIS                 TRISBbits.TRISB6
#define NA_1_LAT                  LATBbits.LATB6
#define NA_1_PORT                 PORTBbits.RB6
#define NA_1_WPU                  WPUBbits.WPUB6
#define NA_1_OD                   ODCONBbits.ODCB6
#define NA_1_ANS                  ANSELBbits.ANSB6
#define NA_1_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define NA_1_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define NA_1_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define NA_1_GetValue()           PORTBbits.RB6
#define NA_1_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define NA_1_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define NA_1_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define NA_1_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define NA_1_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define NA_1_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define NA_1_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define NA_1_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

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

// get/set NA_2 aliases
#define NA_2_TRIS                 TRISCbits.TRISC0
#define NA_2_LAT                  LATCbits.LATC0
#define NA_2_PORT                 PORTCbits.RC0
#define NA_2_WPU                  WPUCbits.WPUC0
#define NA_2_OD                   ODCONCbits.ODCC0
#define NA_2_ANS                  ANSELCbits.ANSC0
#define NA_2_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define NA_2_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define NA_2_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define NA_2_GetValue()           PORTCbits.RC0
#define NA_2_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define NA_2_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define NA_2_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define NA_2_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define NA_2_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define NA_2_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define NA_2_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define NA_2_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

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

// get/set PM_STAT2 aliases
#define PM_STAT2_TRIS                 TRISCbits.TRISC2
#define PM_STAT2_LAT                  LATCbits.LATC2
#define PM_STAT2_PORT                 PORTCbits.RC2
#define PM_STAT2_WPU                  WPUCbits.WPUC2
#define PM_STAT2_OD                   ODCONCbits.ODCC2
#define PM_STAT2_ANS                  ANSELCbits.ANSC2
#define PM_STAT2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define PM_STAT2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define PM_STAT2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define PM_STAT2_GetValue()           PORTCbits.RC2
#define PM_STAT2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define PM_STAT2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define PM_STAT2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define PM_STAT2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define PM_STAT2_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define PM_STAT2_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define PM_STAT2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define PM_STAT2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set NA_3 aliases
#define NA_3_TRIS                 TRISCbits.TRISC3
#define NA_3_LAT                  LATCbits.LATC3
#define NA_3_PORT                 PORTCbits.RC3
#define NA_3_WPU                  WPUCbits.WPUC3
#define NA_3_OD                   ODCONCbits.ODCC3
#define NA_3_ANS                  ANSELCbits.ANSC3
#define NA_3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define NA_3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define NA_3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define NA_3_GetValue()           PORTCbits.RC3
#define NA_3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define NA_3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define NA_3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define NA_3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define NA_3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define NA_3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define NA_3_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define NA_3_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

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

// get/set NA_4 aliases
#define NA_4_TRIS                 TRISCbits.TRISC5
#define NA_4_LAT                  LATCbits.LATC5
#define NA_4_PORT                 PORTCbits.RC5
#define NA_4_WPU                  WPUCbits.WPUC5
#define NA_4_OD                   ODCONCbits.ODCC5
#define NA_4_ANS                  ANSELCbits.ANSC5
#define NA_4_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define NA_4_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define NA_4_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define NA_4_GetValue()           PORTCbits.RC5
#define NA_4_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define NA_4_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define NA_4_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define NA_4_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define NA_4_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define NA_4_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define NA_4_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define NA_4_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

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

// get/set NA_5 aliases
#define NA_5_TRIS                 TRISCbits.TRISC7
#define NA_5_LAT                  LATCbits.LATC7
#define NA_5_PORT                 PORTCbits.RC7
#define NA_5_WPU                  WPUCbits.WPUC7
#define NA_5_OD                   ODCONCbits.ODCC7
#define NA_5_ANS                  ANSELCbits.ANSC7
#define NA_5_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define NA_5_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define NA_5_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define NA_5_GetValue()           PORTCbits.RC7
#define NA_5_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define NA_5_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define NA_5_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define NA_5_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define NA_5_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define NA_5_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define NA_5_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define NA_5_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/