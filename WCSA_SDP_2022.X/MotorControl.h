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
 * @param   PinName_t motorPin
 * @return  [uint8_t] SUCCESS or ERROR
 * @brief   Initializes the motor PWM (CCP) system
 * @author  Jack Lambert, 2022.02.07 */
uint8_t MotorControl_Init(PinName_t motorPin);

//------------------------------------------------------------------------------
/**
 * @funct   MotorControl_SetIntensity(dutyCycle)
 * @param   uint8_t dutyCycle - [0, 100] % duty cycle
 * @return  None
 * @brief   Sets the motor intensity in terms of a [0, 100]% duty cycle
 * @author  Jack Lambert, 2022.02.07 */
void MotorControl_SetIntensity(uint8_t dutyCycle);

//------------------------------------------------------------------------------
/**
 * @funct   MotorControl_SetNextPulseDuration(duration)
 * @param   unsigned short duration
 * @return  None
 * @brief   Sets the duration (in ms) of the next vibration pulse to occur
 * @author  Jack Lambert, 2022.02.07 */
void MotorControl_SetNextPulseDuration(unsigned short duration);

//------------------------------------------------------------------------------
/**
 * @funct   MotorControl_StartPulse()
 * @param   None
 * @return  None
 * @brief   Begins the motor PWM pulse according to the intensity & duration
 *          previously specified by the user configuration
 * @author  Jack Lambert, 2022.02.07 */
void MotorControl_StartPulse();

//------------------------------------------------------------------------------

#endif	/* MOTORCONTROL_H */

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
