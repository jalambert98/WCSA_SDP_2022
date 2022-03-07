/* 
 * File:    eusart.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: Generated originally by Microchip Code Configurator (MCC) and then
 *       further modified by Jack Lambert
 * 
 * Created on January 27, 2022, 6:09 PM
 */
//------------------------------------------------------------------------------

#include "eusart.h"

#define EUSART_TX_BUFFER_SIZE 8
#define EUSART_RX_BUFFER_SIZE 8


//------------------------------------------------------------------------------

volatile uint8_t eusartTxHead = 0;
volatile uint8_t eusartTxTail = 0;
volatile uint8_t eusartTxBuffer[EUSART_TX_BUFFER_SIZE];
volatile uint8_t eusartTxBufferRemaining;

volatile uint8_t eusartRxHead = 0;
volatile uint8_t eusartRxTail = 0;
volatile uint8_t eusartRxBuffer[EUSART_RX_BUFFER_SIZE];
volatile eusart_status_t eusartRxStatusBuffer[EUSART_RX_BUFFER_SIZE];
volatile uint8_t eusartRxCount;
volatile eusart_status_t eusartRxLastError;

//------------------------------------------------------------------------------

void (*EUSART_TxDefaultInterruptHandler)(void);
void (*EUSART_RxDefaultInterruptHandler)(void);

void (*EUSART_FramingErrorHandler)(void);
void (*EUSART_OverrunErrorHandler)(void);
void (*EUSART_ErrorHandler)(void);

void EUSART_DefaultFramingErrorHandler(void);
void EUSART_DefaultOverrunErrorHandler(void);
void EUSART_DefaultErrorHandler(void);

//------------------------------------------------------------------------------

void EUSART_Initialize(void)
{
    // disable interrupts before changing states
    PIE1bits.RCIE = 0;
    EUSART_SetRxInterruptHandler(EUSART_Receive_ISR);
    PIE1bits.TXIE = 0;
    EUSART_SetTxInterruptHandler(EUSART_Transmit_ISR);
    // Set the EUSART module to the options selected in the user interface.

    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUD1CON = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RC1STA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TX1STA = 0x24;

    // SP1BRGL 160; 
    SP1BRGL = 0xA0;

    // SP1BRGH 1; 
    SP1BRGH = 0x01;


    EUSART_SetFramingErrorHandler(EUSART_DefaultFramingErrorHandler);
    EUSART_SetOverrunErrorHandler(EUSART_DefaultOverrunErrorHandler);
    EUSART_SetErrorHandler(EUSART_DefaultErrorHandler);

    eusartRxLastError.status = 0;

    // initializing the driver state
    eusartTxHead = 0;
    eusartTxTail = 0;
    eusartTxBufferRemaining = sizeof(eusartTxBuffer);

    eusartRxHead = 0;
    eusartRxTail = 0;
    eusartRxCount = 0;

    // enable receive interrupt
    PIE1bits.RCIE = 1;
}

//------------------------------------------------------------------------------

bool EUSART_is_tx_ready(void)
{
    return (eusartTxBufferRemaining ? true : false);
}

//------------------------------------------------------------------------------

bool EUSART_is_rx_ready(void)
{
    return (eusartRxCount ? true : false);
}

//------------------------------------------------------------------------------

bool EUSART_is_tx_done(void)
{
    return TX1STAbits.TRMT;
}

//------------------------------------------------------------------------------

eusart_status_t EUSART_get_last_status(void){
    return eusartRxLastError;
}

//------------------------------------------------------------------------------

uint8_t EUSART_Read(void)
{
    uint8_t readValue  = 0;
    
    while(0 == eusartRxCount)
    {
    }

    eusartRxLastError = eusartRxStatusBuffer[eusartRxTail];

    readValue = eusartRxBuffer[eusartRxTail++];
    if(sizeof(eusartRxBuffer) <= eusartRxTail)
    {
        eusartRxTail = 0;
    }
    PIE1bits.RCIE = 0;
    eusartRxCount--;
    PIE1bits.RCIE = 1;

    return readValue;
}

//------------------------------------------------------------------------------

void EUSART_Write(uint8_t txData)
{
    while(0 == eusartTxBufferRemaining)
    {
    }

    if(0 == PIE1bits.TXIE)
    {
        TX1REG = txData;
    }
    else
    {
        PIE1bits.TXIE = 0;
        eusartTxBuffer[eusartTxHead++] = txData;
        if(sizeof(eusartTxBuffer) <= eusartTxHead)
        {
            eusartTxHead = 0;
        }
        eusartTxBufferRemaining--;
    }
    PIE1bits.TXIE = 1;
}

//------------------------------------------------------------------------------

char getch(void)
{
    return EUSART_Read();
}

//------------------------------------------------------------------------------

void putch(char txData)
{
    EUSART_Write(txData);
}

//------------------------------------------------------------------------------

void EUSART_Transmit_ISR(void)
{

    // add your EUSART interrupt custom code
    if(sizeof(eusartTxBuffer) > eusartTxBufferRemaining)
    {
        TX1REG = eusartTxBuffer[eusartTxTail++];
        if(sizeof(eusartTxBuffer) <= eusartTxTail)
        {
            eusartTxTail = 0;
        }
        eusartTxBufferRemaining++;
    }
    else
    {
        PIE1bits.TXIE = 0;
    }
}

//------------------------------------------------------------------------------

void EUSART_Receive_ISR(void)
{
    
    eusartRxStatusBuffer[eusartRxHead].status = 0;

    if(RC1STAbits.FERR){
        eusartRxStatusBuffer[eusartRxHead].ferr = 1;
        EUSART_FramingErrorHandler();
    }

    if(RC1STAbits.OERR){
        eusartRxStatusBuffer[eusartRxHead].oerr = 1;
        EUSART_OverrunErrorHandler();
    }
    
    if(eusartRxStatusBuffer[eusartRxHead].status){
        EUSART_ErrorHandler();
    } else {
        EUSART_RxDataHandler();
    }
    
    // or set custom function using EUSART_SetRxInterruptHandler()
}

//------------------------------------------------------------------------------

void EUSART_RxDataHandler(void){
    // use this default receive interrupt handler code
    eusartRxBuffer[eusartRxHead++] = RC1REG;
    if(sizeof(eusartRxBuffer) <= eusartRxHead)
    {
        eusartRxHead = 0;
    }
    eusartRxCount++;
}

//------------------------------------------------------------------------------

void EUSART_DefaultFramingErrorHandler(void){}

//------------------------------------------------------------------------------

void EUSART_DefaultOverrunErrorHandler(void){
    // EUSART error - restart

    RC1STAbits.CREN = 0;
    RC1STAbits.CREN = 1;

}

//------------------------------------------------------------------------------

void EUSART_DefaultErrorHandler(void){
    EUSART_RxDataHandler();
}

//------------------------------------------------------------------------------

void EUSART_SetFramingErrorHandler(void (* interruptHandler)(void)){
    EUSART_FramingErrorHandler = interruptHandler;
}

//------------------------------------------------------------------------------

void EUSART_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    EUSART_OverrunErrorHandler = interruptHandler;
}

//------------------------------------------------------------------------------

void EUSART_SetErrorHandler(void (* interruptHandler)(void)){
    EUSART_ErrorHandler = interruptHandler;
}

//------------------------------------------------------------------------------

void EUSART_SetTxInterruptHandler(void (* interruptHandler)(void)){
    EUSART_TxDefaultInterruptHandler = interruptHandler;
}

//------------------------------------------------------------------------------

void EUSART_SetRxInterruptHandler(void (* interruptHandler)(void)){
    EUSART_RxDefaultInterruptHandler = interruptHandler;
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
