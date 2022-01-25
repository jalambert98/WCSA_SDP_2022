/* 
 * File:   PIC16Xpress_DevBoard.h
 * Author: Jack Lambert
 *
 * Created on January 25, 2022, 12:42 PM
 */

#ifndef PIC16XPRESS_DEVBOARD_H
#define	PIC16XPRESS_DEVBOARD_H

#include <xc.h>
#include <PIC16F18345.h>

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define HIGH                0b1
#define LOW                 0b0

#define INPUT               0b1
#define OUTPUT              0b0

#define SUCCESS             0x00
#define ERROR               0xFF

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


typedef enum {
    A5, A4, A3, 
    C5, C4, C3, 
    C6, C7, B7, 
    A0, A1, A2, 
    C0, C1, C2, 
    B4, B5, B6
} PinName_t;


#endif	/* PIC16XPRESS_DEVBOARD_H */

