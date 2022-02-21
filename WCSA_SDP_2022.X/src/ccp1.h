/* 
 * File:    ccp1.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 26, 2022, 12:20 PM
 */
//------------------------------------------------------------------------------

#ifndef CCP1_H
#define CCP1_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

//==============================================================================
//-------------------------------- TYPEDEFS ------------------------------------
//==============================================================================
/**
 @Summary
   Defines the values to convert from 16bit to two 8 bit and vice versa

 @Description
   This routine used to get two 8 bit values from 16bit also
   two 8 bit value are combine to get 16bit.
 */

typedef union CCPR1Reg_tag
{
   struct
   {
      uint8_t ccpr1l;
      uint8_t ccpr1h;
   };
   struct
   {
      uint16_t ccpr1_16Bit;
   };
} CCP1_PERIOD_REG_T ;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================
/**
  @Summary
    Initializes the CCP1

  @Description
    This routine initializes the CCP1_Initialize.
    This routine must be called before any other CCP1 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
 */
void CCP1_Initialize(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Implements ISR

  @Description
    This routine is used to implement the ISR for the interrupt-driven
    implementations.

  @Returns
    None

  @Param
    None
*/
void CCP1_CaptureISR(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Setter for CCP1 CallBack function

  @Description
    Calling this function will set a new custom call back function that will be 
    called from the Capture ISR.

  @Preconditions
    Initialize the CCP1 module with interrupt before calling this function.

  @Param
    A pointer to the new function

  @Returns
    None
*/
 void CCP1_SetCallBack(void (*customCallBack)(uint16_t));
 
//------------------------------------------------------------------------------

#endif  //CCP1_H
 
//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
