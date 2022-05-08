
#ifndef CCP4_H
#define CCP4_H

//------------------------------------------------------------------------------
/**
  Section: Included Files
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

//------------------------------------------------------------------------------
/** 
  Section: Data type definitions
 */
//------------------------------------------------------------------------------

/**
 @Summary
   Defines the values to convert from 16bit to two 8 bit and vice versa

 @Description
   This routine used to get two 8 bit values from 16bit also
   two 8 bit value are combine to get 16bit.
 */
typedef union CCPR4Reg_tag {

    struct {
        uint8_t ccpr4l;
        uint8_t ccpr4h;
    };

    struct {
        uint16_t ccpr4_16Bit;
    };
} CCP4_PERIOD_REG_T;

//------------------------------------------------------------------------------
/**
  Section: COMPARE Module APIs
 */
//------------------------------------------------------------------------------
/**
  @Summary
    Initializes the CCP4

  @Description
    This routine initializes the CCP4_Initialize.
    This routine must be called before any other CCP4 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
 */
void CCP4_Initialize(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Loads 16-bit compare value.

  @Description
    This routine loads the 16 bit compare value.

  @Preconditions
    CCP4_Initialize() function should have been
    called before calling this function.

  @Param
    compareCount: 16-bit unsigned value

  @Returns
    None
 */
void CCP4_SetCompareCount(uint16_t compareCount);

//------------------------------------------------------------------------------
/**
  @Summary
    Read compare output status.

  @Description
    This routine returns the compare output status.

  @Preconditions
    CCP4_Initialize() function should have been
    called before calling this function.

  @Param
    None

  @Returns
    true : output high
    false: output low
 */
bool CCP4_OutputStatusGet(void);

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
void CCP4_CompareISR(void);

//------------------------------------------------------------------------------

#endif 

//------------------------------------------------------------------------------
/**
 End of File
 */
