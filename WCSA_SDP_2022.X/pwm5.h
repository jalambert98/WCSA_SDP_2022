/* 
 * File:    pwm5.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on February 8, 2022, 2:15 PM
 */
//------------------------------------------------------------------------------
#ifndef PWM5_H
#define PWM5_H

#include <xc.h>
#include <stdint.h>


#define PWM5_INITIALIZE_DUTY_VALUE    0

//------------------------------------------------------------------------------
/**
  @Summary
    Initializes the PWM5
  @Description
    This routine initializes the EPWM5_Initialize
    This routine must be called before any other PWM5 routine is called.
    This routine should only be called once during system initialization.
  @Preconditions
    None
  @Param
    None
  @Returns
    None
 */
void PWM5_Initialize(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Loads 10-bit duty cycle.
  @Description
    This routine loads the 10 bit duty cycle value.
  @Preconditions
    PWM5_Initialize() function should have been called 
        before calling this function.
  @Param
    Pass 10bit duty cycle value.
  @Returns
    None
 */
void PWM5_LoadDutyValue(uint16_t dutyValue);

//------------------------------------------------------------------------------

#endif	//PWM5_H
/**
 End of File
 */