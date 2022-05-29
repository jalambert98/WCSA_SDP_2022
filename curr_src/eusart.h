
#ifndef EUSART_H
#define EUSART_H

//------------------------------------------------------------------------------
/**
  Section: Included Files
 */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


//------------------------------------------------------------------------------
/**
  Section: Macro Declarations
 */
//------------------------------------------------------------------------------

#define EUSART_DataReady  (EUSART_is_rx_ready())


//------------------------------------------------------------------------------
/**
  Section: Data Type Definitions
 */
//------------------------------------------------------------------------------

typedef union {

    struct {
        unsigned perr : 1;
        unsigned ferr : 1;
        unsigned oerr : 1;
        unsigned reserved : 5;
    };
    uint8_t status;
} eusart_status_t;


//------------------------------------------------------------------------------
/**
 Section: Global variables
 */
//------------------------------------------------------------------------------

extern volatile uint8_t eusartTxBufferRemaining;
extern volatile uint8_t eusartRxCount;


//------------------------------------------------------------------------------
/**
  Section: EUSART APIs
 */
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

//------------------------------------------------------------------------------
/**
 End of File
 */
