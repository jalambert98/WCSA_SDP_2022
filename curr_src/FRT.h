/* 
 * File:    FRT.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 25, 2022, 6:52 PM
 */
//------------------------------------------------------------------------------

#include "pin_manager.h"

#ifndef FRT_H
#define	FRT_H

//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================
/**
 * @funct    FRT_Init()
 * @param    None
 * @return   None
 * @brief    Initializes TMR1 as FRT source and sets time-counters to 0.
 * @author   Jack Lambert, 2022.01.25
 **/
void FRT_Init(void);

//------------------------------------------------------------------------------
/**
 * @funct    FRT_GetMillis()
 * 
 * @param    None
 * 
 * @return   unsigned long millis - current FR timer value (in milliseconds)
 * 
 * @brief    Returns the number of MILLISECONDS that have elapsed since
 *           FRT_Init() was last called
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
unsigned long FRT_GetMillis(void);

//------------------------------------------------------------------------------
/**
 * @funct    FRT_GetMicros()
 * 
 * @param    None
 * 
 * @return   unsigned long micros - current FR timer value (in microseconds)
 * 
 * @brief    Returns the number of MICROSECONDS that have elapsed since
 *           FRT_Init() was last called
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
unsigned long FRT_GetMicros(void);

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


#endif	/* FRT_H */

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
