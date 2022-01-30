/* 
 * File:    eusart.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 27, 2022, 6:09 PM
 */
//------------------------------------------------------------------------------

#ifndef EUSART_H
#define EUSART_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define EUSART_DataReady  (EUSART_is_rx_ready())

//------------------------------------------------------------------------------

typedef union {
    struct {
        unsigned perr : 1;
        unsigned ferr : 1;
        unsigned oerr : 1;
        unsigned reserved : 5;
    };
    uint8_t status;
}eusart_status_t;


//------------------------------------------------------------------------------

extern volatile uint8_t eusartTxBufferRemaining;
extern volatile uint8_t eusartRxCount;

//------------------------------------------------------------------------------

extern void (*EUSART_TxDefaultInterruptHandler)(void);
extern void (*EUSART_RxDefaultInterruptHandler)(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Initialization routine that takes inputs from the EUSART GUI.

  @Description
    This routine initializes the EUSART driver.
    This routine must be called before any other EUSART routine is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None    
*/
void EUSART_Initialize(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Checks if the EUSART transmitter is ready to transmit data

  @Description
    This routine checks if EUSART transmitter is ready 
    to accept and transmit data byte

  @Preconditions
    EUSART_Initialize() function should have been called
    before calling this function.
    EUSART transmitter should be enabled before calling 
    this function

  @Param
    None

  @Returns
    Status of EUSART transmitter
    TRUE: EUSART transmitter is ready
    FALSE: EUSART transmitter is not ready
*/
bool EUSART_is_tx_ready(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Checks if the EUSART receiver ready for reading

  @Description
    This routine checks if EUSART receiver has received data 
    and ready to be read

  @Preconditions
    EUSART_Initialize() function should be called
    before calling this function
    EUSART receiver should be enabled before calling this 
    function

  @Param
    None

  @Returns
    Status of EUSART receiver
    TRUE: EUSART receiver is ready for reading
    FALSE: EUSART receiver is not ready for reading
*/
bool EUSART_is_rx_ready(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Checks if EUSART data is transmitted

  @Description
    This function return the status of transmit shift register

  @Preconditions
    EUSART_Initialize() function should be called
    before calling this function
    EUSART transmitter should be enabled and EUSART_Write
    should be called before calling this function

  @Param
    None

  @Returns
    Status of EUSART receiver
    TRUE: Data completely shifted out if the USART shift register
    FALSE: Data is not completely shifted out of the shift register
*/
bool EUSART_is_tx_done(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Gets the error status of the last read byte.

  @Description
    This routine gets the error status of the last read byte.

  @Preconditions
    EUSART_Initialize() function should have been called
    before calling this function. The returned value is only
    updated after a read is called.

  @Param
    None

  @Returns
    the status of the last read byte
 */
eusart_status_t EUSART_get_last_status(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Read a byte of data from the EUSART.

  @Description
    This routine reads a byte of data from the EUSART.

  @Preconditions
    EUSART_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if the receiver is not empty before calling this function.

  @Param
    None

  @Returns
    A data byte received by the driver.
*/
uint8_t EUSART_Read(void);

//------------------------------------------------------------------------------
 /**
  @Summary
    Writes a byte of data to the EUSART.

  @Description
    This routine writes a byte of data to the EUSART.

  @Preconditions
    EUSART_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if transmitter is not busy before calling this function.

  @Param
    txData  - Data byte to write to the EUSART

  @Returns
    None
*/
void EUSART_Write(uint8_t txData);

//------------------------------------------------------------------------------
/**
  @Summary
    Maintains the driver's transmitter state machine and implements its ISR.

  @Description
    This routine is used to maintain the driver's internal transmitter state
    machine.This interrupt service routine is called when the state of the
    transmitter needs to be maintained in a non polled manner.

  @Preconditions
    EUSART_Initialize() function should have been called
    for the ISR to execute correctly.

  @Param
    None

  @Returns
    None
*/
void EUSART_Transmit_ISR(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Maintains the driver's receiver state machine and implements its ISR

  @Description
    This routine is used to maintain the driver's internal receiver state
    machine.This interrupt service routine is called when the state of the
    receiver needs to be maintained in a non polled manner.

  @Preconditions
    EUSART_Initialize() function should have been called
    for the ISR to execute correctly.

  @Param
    None

  @Returns
    None
*/
void EUSART_Receive_ISR(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Maintains the driver's receiver state machine

  @Description
    This routine is called by the receive state routine and is used to maintain 
    the driver's internal receiver state machine. It should be called by a custom
    ISR to maintain normal behavior

  @Preconditions
    EUSART_Initialize() function should have been called
    for the ISR to execute correctly.

  @Param
    None

  @Returns
    None
*/
void EUSART_RxDataHandler(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Set EUSART Framing Error Handler

  @Description
    This API sets the function to be called upon EUSART framing error

  @Preconditions
    Initialize  the EUSART before calling this API

  @Param
    Address of function to be set as framing error handler

  @Returns
    None
*/
void EUSART_SetFramingErrorHandler(void (* interruptHandler)(void));

//------------------------------------------------------------------------------
/**
  @Summary
    Set EUSART Overrun Error Handler

  @Description
    This API sets the function to be called upon EUSART overrun error

  @Preconditions
    Initialize  the EUSART module before calling this API

  @Param
    Address of function to be set as overrun error handler

  @Returns
    None
*/
void EUSART_SetOverrunErrorHandler(void (* interruptHandler)(void));

//------------------------------------------------------------------------------
/**
  @Summary
    Set EUSART Error Handler

  @Description
    This API sets the function to be called upon EUSART error

  @Preconditions
    Initialize  the EUSART module before calling this API

  @Param
    Address of function to be set as error handler

  @Returns
    None
*/
void EUSART_SetErrorHandler(void (* interruptHandler)(void));

//------------------------------------------------------------------------------
/**
  @Summary
    Sets the transmit handler function to be called by the interrupt service

  @Description
    Calling this function will set a new custom function that will be 
    called when the transmit interrupt needs servicing.

  @Preconditions
    EUSART_Initialize() function should have been called
    for the ISR to execute correctly.

  @Param
    A pointer to the new function

  @Returns
    None
*/
void EUSART_SetTxInterruptHandler(void (* interruptHandler)(void));

//------------------------------------------------------------------------------
/**
  @Summary
    Sets the receive handler function to be called by the interrupt service

  @Description
    Calling this function will set a new custom function that will be 
    called when the receive interrupt needs servicing.

  @Preconditions
    EUSART_Initialize() function should have been called
    for the ISR to execute correctly.

  @Param
    A pointer to the new function

  @Returns
    None
*/
void EUSART_SetRxInterruptHandler(void (* interruptHandler)(void));

//------------------------------------------------------------------------------

#endif  // EUSART_H

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
