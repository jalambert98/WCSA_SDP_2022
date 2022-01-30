/* 
 * File:    interrupt_manager.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 26, 2022, 12:35 PM
 */
//------------------------------------------------------------------------------

#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

//------------------------------------------------------------------------------
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will enable global interrupts.
 */
#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)

//------------------------------------------------------------------------------
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will disable global interrupts.
 */
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

//------------------------------------------------------------------------------
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will enable peripheral interrupts.
 */
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)

//------------------------------------------------------------------------------
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will disable peripheral interrupts.
 */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

//------------------------------------------------------------------------------

#endif  // INTERRUPT_MANAGER_H

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
