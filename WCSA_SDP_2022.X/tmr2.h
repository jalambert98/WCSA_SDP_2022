/* 
 * File:    tmr2.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on February 8, 2022, 2:15 PM
 */
//------------------------------------------------------------------------------

#ifndef TMR2_H
#define TMR2_H

#include <stdint.h>
#include <stdbool.h>

//------------------------------------------------------------------------------
/**
  @Summary
    Initializes the TMR2 module.
  @Description
    This function initializes the TMR2 Registers.
    This function must be called before any other TMR2 function is called.
  @Preconditions
    None
  @Param
    None
  @Returns
    None
*/
void TMR2_Initialize(void);

//------------------------------------------------------------------------------
/**
  @Summary
    This function starts the TMR2.
  @Description
    This function starts the TMR2 operation.
    This function must be called after the initialization of TMR2.
  @Preconditions
    Initialize  the TMR2 before calling this function.
  @Param
    None
  @Returns
    None
*/
void TMR2_StartTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    This function stops the TMR2.
  @Description
    This function stops the TMR2 operation.
    This function must be called after the start of TMR2.
  @Preconditions
    Initialize  the TMR2 before calling this function.
  @Param
    None
  @Returns
    None
*/
void TMR2_StopTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Reads the TMR2 register.
  @Description
    This function reads the TMR2 register value and return it.
  @Preconditions
    Initialize  the TMR2 before calling this function.
  @Param
    None
  @Returns
    This function returns the current value of TMR2 register.
*/
uint8_t TMR2_ReadTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Writes the TMR2 register.
  @Description
    This function writes the TMR2 register.
    This function must be called after the initialization of TMR2.
  @Preconditions
    Initialize  the TMR2 before calling this function.
  @Param
    timerVal - Value to write into TMR2 register.
  @Returns
    None
*/
void TMR2_WriteTimer(uint8_t timerVal);

//------------------------------------------------------------------------------
/**
  @Summary
    Load value to Period Register.
  @Description
    This function writes the value to PR2 register.
    This function must be called after the initialization of TMR2.
  @Preconditions
    Initialize  the TMR2 before calling this function.
  @Param
    periodVal - Value to load into TMR2 register.
  @Returns
    None
*/
void TMR2_LoadPeriodRegister(uint8_t periodVal);

//------------------------------------------------------------------------------
/**
  @Summary
    Boolean routine to poll or to check for the match flag on the fly.
  @Description
    This function is called to check for the timer match flag.
    This function is used in timer polling method.
  @Preconditions
    Initialize  the TMR2 module before calling this routine.
  @Param
    None
  @Returns
    true - timer match has occurred.
    false - timer match has not occurred.
*/
bool TMR2_HasOverflowOccured(void);

//------------------------------------------------------------------------------

#endif // TMR2_H

//------------------------------------------------------------------------------
/**
 End of File
*/
