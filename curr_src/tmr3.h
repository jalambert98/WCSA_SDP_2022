
#ifndef TMR3_H
#define TMR3_H

//------------------------------------------------------------------------------
/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

//------------------------------------------------------------------------------
/**
  Section: TMR3 APIs
*/
//------------------------------------------------------------------------------
/**
  @Summary
    Initializes the TMR3

  @Description
    This routine initializes the TMR3.
    This routine must be called before any other TMR3 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
*/
void TMR3_Initialize(void);

//------------------------------------------------------------------------------
/**
  @Summary
    This function starts the TMR3.

  @Description
    This function starts the TMR3 operation.
    This function must be called after the initialization of TMR3.

  @Preconditions
    Initialize  the TMR3 before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR3_StartTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    This function stops the TMR3.

  @Description
    This function stops the TMR3 operation.
    This function must be called after the start of TMR3.

  @Preconditions
    Initialize  the TMR3 before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR3_StopTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Reads the TMR3 register.

  @Description
    This function reads the TMR3 register value and return it.

  @Preconditions
    Initialize  the TMR3 before calling this function.

  @Param
    None

  @Returns
    This function returns the current value of TMR3 register.
*/
uint16_t TMR3_ReadTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Writes the TMR3 register.

  @Description
    This function writes the TMR3 register.
    This function must be called after the initialization of TMR3.

  @Preconditions
    Initialize  the TMR3 before calling this function.

  @Param
    timerVal - Value to write into TMR3 register.

  @Returns
    None
*/
void TMR3_WriteTimer(uint16_t timerVal);

//------------------------------------------------------------------------------
/**
  @Summary
    Reload the TMR3 register.

  @Description
    This function reloads the TMR3 register.
    This function must be called to write initial value into TMR3 register.

  @Preconditions
    Initialize  the TMR3 before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR3_Reload(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Starts the single pulse acquisition in TMR3 gate operation.

  @Description
    This function starts the single pulse acquisition in TMR3 gate operation.
    This function must be used when the TMR3 gate is enabled.

  @Preconditions
    Initialize  the TMR3 with gate enable before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR3_StartSinglePulseAcquisition(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Check the current state of Timer1 gate.

  @Description
    This function reads the TMR3 gate value and return it.
    This function must be used when the TMR3 gate is enabled.

  @Preconditions
    Initialize  the TMR3 with gate enable before calling this function.

  @Param
    None

  @Returns
    None
*/
uint8_t TMR3_CheckGateValueStatus(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Boolean routine to poll or to check for the overflow flag on the fly.

  @Description
    This function is called to check for the timer overflow flag.
    This function is usd in timer polling method.

  @Preconditions
    Initialize  the TMR3 module before calling this routine.

  @Param
    None

  @Returns
    true - timer overflow has occured.
    false - timer overflow has not occured.
*/
bool TMR3_HasOverflowOccured(void);

//------------------------------------------------------------------------------

#endif // TMR3_H

//------------------------------------------------------------------------------
/**
 End of File
*/
