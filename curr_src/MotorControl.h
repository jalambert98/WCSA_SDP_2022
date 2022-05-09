/* 
 * File:   MotorControl.h
 * Author: Jack
 *
 * Created on February 7, 2022, 9:42 PM
 */
//------------------------------------------------------------------------------

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "pin_manager.h"

#ifndef MOTORCONTROL_H
#define	MOTORCONTROL_H

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define PWM5_INITIALIZE_DUTY_VALUE    0


// [PWM5] output --> Pin[RC1]
//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================
/**
 * @funct   MotorControl_Init()
 * @param   None
 * @return  None
 * @brief   Initializes the motor PWM5 system (PinRC1)
 * @author  Jack Lambert, 2022.02.07 */
void MotorControl_Init(void);

//------------------------------------------------------------------------------
/**
 * @funct   MotorControl_SetIntensity(dutyCycle)
 * @param   unsigned int dutyCycle - [0, 1000] range duty cycle
 * @return  uint8_t [SUCCESS or ERROR]
 * @brief   Sets the motor intensity in terms of a [0, 100.0]% duty cycle
 * @author  Jack Lambert, 2022.02.07 */
uint8_t MotorControl_SetIntensity(uint16_t dutyCycle);

//------------------------------------------------------------------------------
/**
 * @funct   MotorControl_SetNextPulseDuration(duration)
 * @param   None
 * @return  None
 * @brief   Engages TMR2
 * @author  Jack Lambert, 2022.02.07 */
void MotorControl_On(void);

//------------------------------------------------------------------------------
/**
 * @funct   MotorControl_StartPulse()
 * @param   None
 * @return  None
 * @brief   Disables TMR2
 * @author  Jack Lambert, 2022.02.07 */
void MotorControl_Off(void);

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
/**
  @Summary
    Initializes the PWM5

  @Description
    This routine initializes the EPWM5_Initialize
    This routine must be called before any other PWM5 routine is called.
    This routine should only be called once during system initialization.

  @Param
    None

  @Returns
    None
 */
void PWM5_Initialize(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Loads 16-bit duty cycle.

  @Description
    This routine loads the 16 bit duty cycle value.

  @Preconditions
    PWM5_Initialize() function should have been called 
        before calling this function.

  @Param
    Pass 16bit duty cycle value.

  @Returns
    None
 */
void PWM5_LoadDutyValue(uint16_t dutyValue);

//------------------------------------------------------------------------------

#endif	/* MOTORCONTROL_H */

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
