/* 
 * File:    mcc.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 26, 2022, 8:45 PM
 */
//------------------------------------------------------------------------------

#ifndef MCC_H
#define	MCC_H
#include <xc.h>
#include "device_config.h"
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>
#include "interrupt_manager.h"
#include "tmr0.h"
#include "eusart.h"


//------------------------------------------------------------------------------
/**
 * @Param
 *  PeripheralConfig_t config : 1 of 4 selectable peripheral configurations
 *                              (selects which hardware systems to enable)
 * @Returns
    none
 * @Description
    Initializes the device to the default states configured in the
 *                  MCC GUI
 */
void PIC16_Init(void);

//------------------------------------------------------------------------------
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the oscillator to the default states configured in the
 *                  MCC GUI
 */
void OSCILLATOR_Initialize(void);

//------------------------------------------------------------------------------
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the WDT module to the default states configured in the
 *                  MCC GUI
 */
void WDT_Initialize(void);

//------------------------------------------------------------------------------
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the PMD module to the default states configured in the
 *                  MCC GUI
 */
void PMD_Initialize(void);

//------------------------------------------------------------------------------

#endif	/* MCC_H */

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
