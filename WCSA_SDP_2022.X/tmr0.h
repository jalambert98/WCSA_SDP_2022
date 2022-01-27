/* 
 * File:    tmr0.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 26, 2022, 10:52 PM
 */

#ifndef TMR0_H
#define TMR0_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif


#define TMR0_INTERRUPT_TICKER_FACTOR    4

//------------------------------------------------------------------------------
/**
  @Summary
    Initializes the TMR0.

  @Description
    This function initializes the TMR0 Registers.
    This function must be called before any other TMR0 function is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
*/
void TMR0_Initialize(void);

//------------------------------------------------------------------------------
/**
  @Summary
    This function starts the TMR0.

  @Description
    This function starts the TMR0 operation.
    This function must be called after the initialization of TMR0.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR0_StartTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    This function stops the TMR0.

  @Description
    This function stops the TMR0 operation.
    This function must be called after the start of TMR0.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR0_StopTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Reads the 8 bits TMR0 register value.

  @Description
    This function reads the 8 bits TMR0 register value and return it.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Param
    None

  @Returns
    This function returns the 8 bits value of TMR0 register.
*/
uint8_t TMR0_ReadTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Writes the 8 bits value to TMR0 register.

  @Description
    This function writes the 8 bits value to TMR0 register.
    This function must be called after the initialization of TMR0.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Param
    timerVal - Value to write into TMR0 register.

  @Returns
    None
*/
void TMR0_WriteTimer(uint8_t timerVal);

//------------------------------------------------------------------------------
/**
  @Summary
    Load value to Period Register.

  @Description
    This function writes the value to TMR0H register.
    This function must be called after the initialization of TMR0.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Param
    periodVal - Value to load into TMR0 register.

  @Returns
    None
*/
void TMR0_Reload(uint8_t periodVal);

//------------------------------------------------------------------------------
/**
  @Summary
    Timer Interrupt Service Routine

  @Description
    Timer Interrupt Service Routine is called by the Interrupt Manager.

  @Preconditions
    Initialize  the TMR0 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
 */
void TMR0_ISR(void);

//------------------------------------------------------------------------------
/**
  @Summary
    CallBack function

  @Description
    This function is called from the timer ISR. User can write your code in this function.

  @Preconditions
    Initialize  the TMR0 module with interrupt before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR0_CallBack(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Set Timer Interrupt Handler

  @Description
    This sets the function to be called during the ISR

  @Preconditions
    Initialize  the TMR0 module with interrupt before calling this.

  @Param
    Address of function to be set

  @Returns
    None
*/
 void TMR0_SetInterruptHandler(void (* InterruptHandler)(void));

//------------------------------------------------------------------------------
/**
  @Summary
    Timer Interrupt Handler

  @Description
    This is a function pointer to the function that will be called during the ISR

  @Preconditions
    Initialize  the TMR0 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
*/
extern void (*TMR0_InterruptHandler)(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Default Timer Interrupt Handler

  @Description
    This is the default Interrupt Handler function

  @Preconditions
    Initialize  the TMR0 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
*/
void TMR0_DefaultInterruptHandler(void);

//------------------------------------------------------------------------------

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // TMR0_H
/**
 End of File
*/