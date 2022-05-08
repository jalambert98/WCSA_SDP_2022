
#include "interrupt_manager.h"
#include "mcc.h"

//------------------------------------------------------------------------------

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(INTCONbits.PEIE == 1)
    {
        if(PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1)
        {
            TMR1_ISR();
        } 
        else if(PIE1bits.RCIE == 1 && PIR1bits.RCIF == 1)
        {
            EUSART_RxDefaultInterruptHandler();
        } 
        else if(PIE1bits.TXIE == 1 && PIR1bits.TXIF == 1)
        {
            EUSART_TxDefaultInterruptHandler();
        } 
        else if(PIE4bits.CCP3IE == 1 && PIR4bits.CCP3IF == 1)
        {
            CCP3_CaptureISR();
        } 
        else if(PIE4bits.CCP4IE == 1 && PIR4bits.CCP4IF == 1)
        {
            CCP4_CompareISR();
        } 
        else if(PIE1bits.ADIE == 1 && PIR1bits.ADIF == 1)
        {
            ADC_ISR();
        }
    }      
}

//------------------------------------------------------------------------------
/**
 End of File
*/
