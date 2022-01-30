#ifndef TMR1_H
#define TMR1_H

#include <stdbool.h>
#include <stdint.h>

#define TMR1_INTERRUPT_TICKER_FACTOR    1

/**
  @Summary
    Initializes the TMR1

  @Description
    This routine initializes the TMR1.
    This routine must be called before any other TMR1 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
*/
void TMR1_Initialize(void);

//------------------------------------------------------------------------------
/**
  @Summary
    This function starts the TMR1.

  @Description
    This function starts the TMR1 operation.
    This function must be called after the initialization of TMR1.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR1_StartTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    This function stops the TMR1.

  @Description
    This function stops the TMR1 operation.
    This function must be called after the start of TMR1.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR1_StopTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Reads the TMR1 register.

  @Description
    This function reads the TMR1 register value and return it.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    This function returns the current value of TMR1 register.
*/
uint16_t TMR1_ReadTimer(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Writes the TMR1 register.

  @Description
    This function writes the TMR1 register.
    This function must be called after the initialization of TMR1.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    timerVal - Value to write into TMR1 register.

  @Returns
    None
*/
void TMR1_WriteTimer(uint16_t timerVal);

//------------------------------------------------------------------------------
/**
  @Summary
    Reload the TMR1 register.

  @Description
    This function reloads the TMR1 register.
    This function must be called to write initial value into TMR1 register.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR1_Reload(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Starts the single pulse acquisition in TMR1 gate operation.

  @Description
    This function starts the single pulse acquisition in TMR1 gate operation.
    This function must be used when the TMR1 gate is enabled.

  @Preconditions
    Initialize  the TMR1 with gate enable before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR1_StartSinglePulseAcquisition(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Check the current state of Timer1 gate.

  @Description
    This function reads the TMR1 gate value and return it.
    This function must be used when the TMR1 gate is enabled.

  @Preconditions
    Initialize  the TMR1 with gate enable before calling this function.

  @Param
    None

  @Returns
    None
*/
uint8_t TMR1_CheckGateValueStatus(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Timer Interrupt Service Routine

  @Description
    Timer Interrupt Service Routine is called by the Interrupt Manager.

  @Preconditions
    Initialize  the TMR1 module with interrupt before calling this ISR.

  @Param
    None

  @Returns
    None
*/
void TMR1_ISR(void);

//------------------------------------------------------------------------------
/**
  @Summary
    CallBack function.

  @Description
    This routine is called by the Interrupt Manager.

  @Preconditions
    Initialize  the TMR1 module with interrupt before calling this function.

  @Param
    None

  @Returns
    None
*/
void TMR1_CallBack(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Set Timer Interrupt Handler

  @Description
    This sets the function to be called during the ISR

  @Preconditions
    Initialize  the TMR1 module with interrupt before calling this.

  @Param
    Address of function to be set

  @Returns
    None
*/
 void TMR1_SetInterruptHandler(void (* InterruptHandler)(void));

 //------------------------------------------------------------------------------
/**
  @Summary
    Timer Interrupt Handler

  @Description
    This is a function pointer to the function that will be called during the ISR

  @Preconditions
    Initialize  the TMR1 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
*/
extern void (*TMR1_InterruptHandler)(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Default Timer Interrupt Handler

  @Description
    This is the default Interrupt Handler function

  @Preconditions
    Initialize  the TMR1 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
*/
void TMR1_DefaultInterruptHandler(void);

//------------------------------------------------------------------------------

#endif // TMR1_H

//------------------------------------------------------------------------------
/**
 End of File
*/
