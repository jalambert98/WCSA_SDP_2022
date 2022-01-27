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

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

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
    Starts the single pulse acquisition in TMR1 gate operation.

  @Description
    This function starts the single pulse acquisition in TMR1 gate operation.
    This function must be used when the TMR1 gate is enabled.

  @Preconditions
    Initialize  the TMR1 with gate enable before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR1_StartSinglePulseAcquisition(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Check the current state of Timer1 gate.

  @Description
    This function reads the TMR1 gate value and return it.
    This function must be used when the TMR1 gate is enabled.

  @Preconditions
    Initialize  the TMR1 with gate enable before calling this function.

  @Param
    None

  @Returns
    None
*/
uint8_t TMR1_CheckGateValueStatus(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Boolean routine to poll or to check for the overflow flag on the fly.

  @Description
    This function is called to check for the timer overflow flag.
    This function is usd in timer polling method.

  @Preconditions
    Initialize  the TMR1 module before calling this routine.

  @Param
    None

  @Returns
    true - timer overflow has occured.
    false - timer overflow has not occured.
*/
bool TMR1_HasOverflowOccured(void);

//------------------------------------------------------------------------------

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // TMR1_H
    
/**
 End of File
*/
