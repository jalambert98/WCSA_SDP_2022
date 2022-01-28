
#include "interrupt_manager.h"
#include "mcc.h"

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1)
    {
        TMR0_ISR();
    }
    else if(INTCONbits.PEIE == 1)
    {
        if(PIE4bits.CCP1IE == 1 && PIR4bits.CCP1IF == 1)
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
        else if(PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1)
        {
            TMR1_ISR();
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
/**
 End of File
*/
