/* 
 * File:    interrupt_manager.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: Generated originally by Microchip Code Configurator (MCC) and then
 *       further modified by Jack Lambert
 * 
 * Created on January 26, 2022, 12:35 PM
 */
//------------------------------------------------------------------------------

#include "PIC16Xpress_DevBoard.h"
#include "interrupt_manager.h"
#include "tmr0.h"
#include "eusart.h"
#include "i2c1_master.h"
#include "ccp1.h"
#include "ccp2.h"
#include "ccp3.h"
#include "ccp4.h"

//------------------------------------------------------------------------------

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1)
    {
        TMR0_ISR();
    }
    else if(INTCONbits.PEIE == 1)
    {
        if(PIE1bits.RCIE == 1 && PIR1bits.RCIF == 1)
        {
            EUSART_RxDefaultInterruptHandler();
        } 
        else if(PIE1bits.TXIE == 1 && PIR1bits.TXIF == 1)
        {
            EUSART_TxDefaultInterruptHandler();
        } 
        else if(PIE1bits.SSP1IE == 1 && PIR1bits.SSP1IF == 1)
        {
            MSSP1_InterruptHandler();
        } 
        else if(PIE4bits.CCP1IE == 1 && PIR4bits.CCP1IF == 1)
        {
            CCP1_CaptureISR();
        } 
        else if(PIE4bits.CCP2IE == 1 && PIR4bits.CCP2IF == 1)
        {
            CCP2_CaptureISR();
        } 
        else if(PIE4bits.CCP3IE == 1 && PIR4bits.CCP3IF == 1)
        {
            CCP3_CaptureISR();
        } 
        else if(PIE4bits.CCP4IE == 1 && PIR4bits.CCP4IF == 1)
        {
            CCP4_CompareISR();
        } 
        else
        {
            //Unhandled Interrupt
        }
    }      
    else
    {
        //Unhandled Interrupt
    }
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
