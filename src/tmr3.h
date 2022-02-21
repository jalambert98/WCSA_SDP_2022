/* 
 * File:    tmr3.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on February 8, 2022, 2:15 PM
 */
//------------------------------------------------------------------------------

#ifndef TMR3_H
#define TMR3_H

#include <stdbool.h>
#include <stdint.h>

//------------------------------------------------------------------------------
/**
  @Summary
    Initializes the TMR3
  @Description
    This routine initializes the TMR3.
    This routine must be called before any other TMR3 routine is called.
    This routine should only be called once during system initialization.
  @Preconditions
    None
  @Param
    None
  @Returns
    None
 */
void TMR3_Initialize(void);

//------------------------------------------------------------------------------
/**
  @Summary
    This function starts the TMR3.
  @Description
    This function starts the TMR3 operation.
    This function must be called after the initialization of TMR3.
  @Preconditions
    Initialize  the TMR3 before calling this function.
  @Param
    None
  @Returns
    None
 */
void TMR3_StartTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    This function stops the TMR3.
  @Description
    This function stops the TMR3 operation.
    This function must be called after the start of TMR3.
  @Preconditions
    Initialize  the TMR3 before calling this function.
  @Param
    None
  @Returns
    None
 */
void TMR3_StopTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Reads the TMR3 register.
  @Description
    This function reads the TMR3 register value and return it.
  @Preconditions
    Initialize  the TMR3 before calling this function.
  @Param
    None
  @Returns
    This function returns the current value of TMR3 register.
 */
uint16_t TMR3_ReadTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Writes the TMR3 register.
  @Description
    This function writes the TMR3 register.
    This function must be called after the initialization of TMR3.
  @Preconditions
    Initialize  the TMR3 before calling this function.
  @Param
    timerVal - Value to write into TMR3 register.
  @Returns
    None
 */
void TMR3_WriteTimer(uint16_t timerVal);

//------------------------------------------------------------------------------
/**
  @Summary
    Reload the TMR3 register.
  @Description
    This function reloads the TMR3 register.
    This function must be called to write initial value into TMR3 register.
  @Preconditions
    Initialize  the TMR3 before calling this function.
  @Param
    None
  @Returns
    None
 */
void TMR3_Reload(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Starts the single pulse acquisition in TMR3 gate operation.
  @Description
    This function starts the single pulse acquisition in TMR3 gate operation.
    This function must be used when the TMR3 gate is enabled.
  @Preconditions
    Initialize  the TMR3 with gate enable before calling this function.
  @Param
    None
  @Returns
    None
 */
void TMR3_StartSinglePulseAcquisition(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Check the current state of Timer1 gate.
  @Description
    This function reads the TMR3 gate value and return it.
    This function must be used when the TMR3 gate is enabled.
  @Preconditions
    Initialize  the TMR3 with gate enable before calling this function.
  @Param
    None
  @Returns
    None
 */
uint8_t TMR3_CheckGateValueStatus(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Timer Interrupt Service Routine
  @Description
    Timer Interrupt Service Routine is called by the Interrupt Manager.
  @Preconditions
    Initialize  the TMR3 module with interrupt before calling this ISR.
  @Param
    None
  @Returns
    None
 */
void TMR3_ISR(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Set Timer Interrupt Handler
  @Description
    This sets the function to be called during the ISR
  @Preconditions
    Initialize  the TMR3 module with interrupt before calling this.
  @Param
    Address of function to be set
  @Returns
    None
 */
void TMR3_SetInterruptHandler(void (* InterruptHandler)(void));

//------------------------------------------------------------------------------
/**
  @Summary
    Timer Interrupt Handler
  @Description
    This is a function pointer to the function that will be called during the ISR
  @Preconditions
    Initialize  the TMR3 module with interrupt before calling this isr.
  @Param
    None
  @Returns
    None
 */
extern void (*TMR3_InterruptHandler)(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Default Timer Interrupt Handler
  @Description
    This is the default Interrupt Handler function
  @Preconditions
    Initialize  the TMR3 module with interrupt before calling this isr.
  @Param
    None
  @Returns
    None
 */
void TMR3_DefaultInterruptHandler(void);

//------------------------------------------------------------------------------

#endif // TMR3_H

//------------------------------------------------------------------------------
/**
 End of File
 */
