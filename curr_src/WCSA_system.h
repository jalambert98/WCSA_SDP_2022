/* 
 * File:    WCSA_system.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: Generated originally by Microchip Code Configurator (as "mcc.h") and 
 *       then further modified by Jack Lambert
 * 
 * Created on January 26, 2022, 8:45 PM
 */
//------------------------------------------------------------------------------

#ifndef WCSA_SYSTEM_H
#define	WCSA_SYSTEM_H

#include <xc.h>
#include "device_config.h"
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "interrupt_manager.h"
#include "FRT.h"
#include "MotorControl.h"
#include "SpeakerTone.h"
#include "PowerButton.h"
#include "BatteryMonitor.h"
#include "eusart.h"


#define RESET_WDT()     do {asm("CLRWDT");} while(0)


//------------------------------------------------------------------------------
/**
 * @Param
    none
 * @Returns
    none
 */
void PIC16_Init(void);

//------------------------------------------------------------------------------
/**
 * @Param
    none
 * @Returns
    none
 */
void OSCILLATOR_Initialize(void);

//------------------------------------------------------------------------------
/**
 * @Param
    none
 * @Returns
    none
 */
void WDT_Initialize(void);

//------------------------------------------------------------------------------
/**
 * @Param
    none
 * @Returns
    none
 */
void PMD_Initialize(void);

//------------------------------------------------------------------------------

#endif	/* WCSA_SYSTEM_H */

//------------------------------------------------------------------------------
/**
 End of File
*/
