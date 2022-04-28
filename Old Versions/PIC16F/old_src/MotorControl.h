/* 
 * File:   MotorControl.h
 * Author: Jack
 *
 * Created on February 7, 2022, 9:42 PM
 */
//------------------------------------------------------------------------------

#include "PIC16Xpress_DevBoard.h"

#ifndef MOTORCONTROL_H
#define	MOTORCONTROL_H

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================
/**
 * @funct   MotorControl_Init(motorPin)
 * @param   None
 * @return  None
 * @brief   Initializes the motor PWM5 system (Pin RB6)
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

#endif	/* MOTORCONTROL_H */

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
