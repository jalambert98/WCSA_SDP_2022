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

#define MAX_DC_PERMILLI     1000    // 100.0% duty cycle --> ALWAYS ON
#define MAX_DC_10BIT        1023    // (1023/1023) ticks high --> ALWAYS ON

#define HALF_DC_PERMILLI    500     // 50.0% = half duty cycle
#define HALF_DC_10BIT       512     // (512/1023) = half duty cycle

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
