/* 
 * File:    BatteryMonitor.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: ADC code originally generated by Microchip Code Configurator (MCC) 
 *       and then further modified by Jack Lambert.
 *       BatteryMonitor implementations were written from scratch.
 * 
 * Created on May 2, 2022, 3:10 PM
 */
//------------------------------------------------------------------------------

#ifndef BATTERYMONITOR_H
#define	BATTERYMONITOR_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "device_config.h"


//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================
// ADC readings corresponding to various battery states
#define BAT_CRITICALLY_LOW      750     // ADC 750 --> ~1.5V --> (vBat ~ 3.0V)
#define BAT_EMPTY_THRESHOLD     800     // ADC 800 --> ~1.6V --> (vBat ~ 3.2V)
#define BAT_25_THRESHOLD        850     // ADC 850 --> ~1.7V --> (vBat ~ 3.4V)
#define BAT_50_THRESHOLD        900     // ADC 900 --> ~1.8V --> (vBat ~ 3.6V)
#define BAT_75_THRESHOLD        950     // ADC 950 --> ~1.9V --> (vBat ~ 3.8V)
#define BAT_FULL_THRESHOLD      1000    // ADC 1k  --> ~2.0V --> (vBat ~ 4.0V)

// PMIC status pins with values ranging [0, 3] <-- STAT1 / STAT2
#define PMIC_STATUS_MASK()      (uint8_t)(0x00 | (PORTBbits.RB4 << 1) | (PORTCbits.RC2))


// ADC(vBat) == pin[RA5]
//==============================================================================
//--------------------------------- TYPEDEFS -----------------------------------
//==============================================================================

typedef enum {
    BAT_EMPTY,
    BAT_25,
    BAT_50,
    BAT_75,
    BAT_FULL
} batLvl_t;

//------------------------------------------------------------------------------

typedef enum {
    SYSTEST = 0,
    NOW_CHARGING = 1,
    CHARGE_COMPLETE = 2,
    NOT_CHARGING = 3
} pmicState_t;

//------------------------------------------------------------------------------

// resulting size of an A/D conversion
typedef uint16_t adc_result_t;

//------------------------------------------------------------------------------

// resulting datatype of a Double ADC conversion
typedef struct {
    adc_result_t adcResult1;
    adc_result_t adcResult2;
} adc_sync_double_result_t;

//------------------------------------------------------------------------------
/** ADC Channel Definitions

 @Summary
   Defines the channels available for conversion.

 @Description
   This datatype defines the channels that are available for the module to use.
 */
typedef enum {
    vBat = 0x5,
    channel_AVSS = 0x3C,
    channel_Temp = 0x3D,
    channel_DAC1 = 0x3E,
    channel_FVR = 0x3F
} adc_channel_t;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================
/**
 * @funct   BatteryMonitor_Init()
 * 
 * @param   None
 * @return  None
 * 
 * @brief   Initializes the vBat ADC pin [RA5] and sets up the BatteryMonitor
 * @author  Jack Lambert, 2022.02.07 
 */
void BatteryMonitor_Init(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Initializes the ADC

  @Description
    This routine initializes the Initializes the ADC.
    This routine must be called before any other ADC routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
 */
void ADC_Initialize(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Allows selection of a channel for conversion

  @Description
    This routine is used to select desired channel for conversion.
    available

  @Preconditions
    ADC_Initialize() function should have been called before calling this function.

  @Returns
    None

  @Param
    Pass in required channel number
    "For available channel refer to enum under adc.h file"
 */
void ADC_SelectChannel(adc_channel_t channel);

//------------------------------------------------------------------------------
/**
  @Summary
    Starts conversion

  @Description
    This routine is used to start conversion of desired channel.
    
  @Preconditions
    ADC_Initialize() function should have been called before calling this function.

  @Returns
    None

  @Param
    None
 */
void ADC_StartConversion(void);

//------------------------------------------------------------------------------
/**
  @Summary
    Returns the ADC conversion value.

  @Description
    This routine is used to get the analog to digital converted value. This
    routine gets converted values from the channel specified.

  @Preconditions
    This routine returns the conversion value only after the conversion is complete.
    Completion status can be checked using
    ADC_IsConversionDone() routine.

  @Returns
    Returns the converted value.

  @Param
    None
 */
adc_result_t ADC_GetConversionResult(void);

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
void ADC_ISR(void);

//------------------------------------------------------------------------------
/**
  @Description
    Returns value of most recently completed ADC reading/conversion

  @Returns
    adc_result_t (uint16_t) adcReading

  @Param
    None
 */
adc_result_t ADC_GetCurrReading(void);

//------------------------------------------------------------------------------
/*
 * @funct:  unsigned int ADCBuffer_GetFilteredReading()
 * 
 * @param:  None
 * @return: uint16_t    -   Output of LPF (running avg) of vals
 * 
 * @brief:  Returns the current filtered reading of the ADC
 * @author: Jack Lambert <joalambe@ucsc.edu>
 *          April 15, 2021
 */
uint16_t ADCBuffer_GetFilteredReading(void);

//------------------------------------------------------------------------------
/*
 * @funct:  batLvl_t GetBatState(batLvl)
 * 
 * @param:  uint16_t :  batLvl   : (vBat / 2) reading from ADC
 * @return: batLvl_t :  batState : enum value [BAT_EMPTY, BAT_25, ..., BAT_FULL]
 * 
 * @brief:  Interprets the ADC reading for BatteryMonitor & characterizes the
 *          battery level into 1 of 6 possible enum states [def: batLvl_t]
 * @author: Jack Lambert <joalambe@ucsc.edu>
 *          May 15, 2021
 */
batLvl_t GetBatState(uint16_t batLvl);

//------------------------------------------------------------------------------


#endif	/* BATTERYMONITOR_H */


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================