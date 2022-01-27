/* 
 * File:    ccp3.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 26, 2022, 12:20 PM
 */
//------------------------------------------------------------------------------

#ifndef CCP3_H
#define CCP3_H

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
typedef union CCPR3Reg_tag
{
   struct
   {
      uint8_t ccpr3l;
      uint8_t ccpr3h;
   };
   struct
   {
      uint16_t ccpr3_16Bit;
   };
} CCP3_PERIOD_REG_T ;


//------------------------------------------------------------------------------
/**
  @Summary
    Initializes the CCP3

  @Description
    This routine initializes the CCP3_Initialize.
    This routine must be called before any other CCP3 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
 */
void CCP3_Initialize(void);

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
void CCP3_CaptureISR(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Setter for CCP3 CallBack function

  @Description
    Calling this function will set a new custom call back function that will be 
    called from the Capture ISR.

  @Preconditions
    Initialize the CCP3 module with interrupt before calling this function.

  @Param
    A pointer to the new function

  @Returns
    None
*/
 void CCP3_SetCallBack(void (*customCallBack)(uint16_t));
 
//------------------------------------------------------------------------------
 
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  //CCP3_H
    
/**
 End of File
*/

