/* 
 * File:    tmr1.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 26, 2022, 12:20 PM
 */
//------------------------------------------------------------------------------

#ifndef TMR1_H
#define TMR1_H

#include <stdbool.h>
#include <stdint.h>

#define TMR1_INTERRUPT_TICKER_FACTOR    1

//------------------------------------------------------------------------------
/**
  @Summary
    Initializes the TMR1

  @Description
    This routine initializes the TMR1.
    This routine must be called before any other TMR1 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
*/
void TMR1_Initialize(void);

//------------------------------------------------------------------------------
/**
  @Summary
    This function starts the TMR1.

  @Description
    This function starts the TMR1 operation.
    This function must be called after the initialization of TMR1.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR1_StartTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    This function stops the TMR1.

  @Description
    This function stops the TMR1 operation.
    This function must be called after the start of TMR1.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR1_StopTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Reads the TMR1 register.

  @Description
    This function reads the TMR1 register value and return it.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    This function returns the current value of TMR1 register.
*/
uint16_t TMR1_ReadTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Writes the TMR1 register.

  @Description
    This function writes the TMR1 register.
    This function must be called after the initialization of TMR1.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    timerVal - Value to write into TMR1 register.

  @Returns
    None
*/
void TMR1_WriteTimer(uint16_t timerVal);

//------------------------------------------------------------------------------
/**
  @Summary
    Reload the TMR1 register.

  @Description
    This function reloads the TMR1 register.
    This function must be called to write initial value into TMR1 register.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR1_Reload(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Timer Interrupt Service Routine

  @Description
    Timer Interrupt Service Routine is called by the Interrupt Manager.

  @Preconditions
    Initialize  the TMR1 module with interrupt before calling this ISR.

  @Param
    None

  @Returns
    None
*/
void TMR1_ISR(void);

//------------------------------------------------------------------------------

#endif // TMR1_H

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
