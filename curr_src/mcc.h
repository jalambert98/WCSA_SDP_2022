
#ifndef MCC_H
#define	MCC_H

#include <xc.h>
#include "device_config.h"
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>
#include "interrupt_manager.h"
#include "tmr3.h"
#include "FRT.h"
#include "MotorControl.h"
#include "SpeakerTone.h"
#include "ccp3.h"
#include "adc.h"
#include "eusart.h"

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

#endif	/* MCC_H */

//------------------------------------------------------------------------------
/**
 End of File
*/
