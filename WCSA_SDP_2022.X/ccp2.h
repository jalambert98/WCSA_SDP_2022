/* 
 * File:    ccp2.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 26, 2022, 12:20 PM
 */
//------------------------------------------------------------------------------

#ifndef CCP2_H
#define CCP2_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

//------------------------------------------------------------------------------
/**
 @Summary
   Defines the values to convert from 16bit to two 8 bit and vice versa

 @Description
   This routine used to get two 8 bit values from 16bit also
   two 8 bit value are combine to get 16bit.
 */
typedef union CCPR2Reg_tag
{
   struct
   {
      uint8_t ccpr2l;
      uint8_t ccpr2h;
   };
   struct
   {
      uint16_t ccpr2_16Bit;
   };
} CCP2_PERIOD_REG_T ;


//------------------------------------------------------------------------------
/**
  @Summary
    Initializes the CCP2

  @Description
    This routine initializes the CCP2_Initialize.
    This routine must be called before any other CCP2 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
 */
void CCP2_Initialize(void);

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
void CCP2_CaptureISR(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Setter for CCP2 CallBack function

  @Description
    Calling this function will set a new custom call back function that will be 
    called from the Capture ISR.

  @Preconditions
    Initialize the CCP2 module with interrupt before calling this function.

  @Param
    A pointer to the new function

  @Returns
    None
*/
 void CCP2_SetCallBack(void (*customCallBack)(uint16_t));
 
 //------------------------------------------------------------------------------

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  //CCP2_H
    
/**
 End of File
*/

