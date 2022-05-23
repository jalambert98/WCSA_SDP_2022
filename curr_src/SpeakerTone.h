/* 
 * File:    SpeakerTone.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on February 7, 2022, 8:20 PM
 */
//------------------------------------------------------------------------------

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "WCSA_system.h"
#include "BatteryMonitor.h"
#include "device_config.h"

#ifndef SPEAKERTONE_H
#define	SPEAKERTONE_H

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define DEFAULT_TONE    440     // (A4 = 440Hz)
#define DEFAULT_OCCOUNT 0x11C1  // (output compare reg value for 440Hz)

#define TONE_C4         262
#define TONE_Db4        277
#define TONE_D4         294
#define TONE_Eb4        311
#define TONE_E4         330
#define TONE_F4         349
#define TONE_Gb4        370
#define TONE_G4         392
#define TONE_Ab4        415
#define TONE_A4         440
#define TONE_Bb4        466
#define TONE_B4         494
#define TONE_C5         523       

#define MIN_FREQ        125
#define MAX_FREQ        5000


//==============================================================================
//--------------------------------- TYPEDEFS -----------------------------------
//==============================================================================
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


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================
/**
 * @funct   SpeakerTone_Init()
 * @param   None
 * @return  None
 * @brief   Initializes the SpeakerTone pin [RA4] to 440Hz (tone disabled)
 * @author  Jack Lambert, 2022.02.07 */
void SpeakerTone_Init(void);

//------------------------------------------------------------------------------
/**
 * @funct   SpeakerTone_SetFrequency(unsigned int NewFrequency)
 * @param   uint16_t newFrequency - new frequency (in Hz) to set. 
 * @return  [uint8_t] SUCCESS or ERROR
 * @brief   Changes the frequency of the speakerTone playback.
 * @author  Jack Lambert, 2022.02.07 */
uint8_t SpeakerTone_SetFrequency(uint16_t newFrequency);

//------------------------------------------------------------------------------
/**
 * @funct   FrequencyGenerator_GetFrequency(void)
 * @return  Frequency of system in Hertz
 * @brief   gets the frequency of the  system.
 * @author  Jack Lambert, 2022.02.07 */
uint16_t SpeakerTone_GetFrequency(void);

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
/**
 * @funct   FrequencyGenerator_Off(void)
 * @return  Turns output Off
 * @author  Jack Lambert, 2022.02.07 */
void SpeakerTone_Off(void);

//------------------------------------------------------------------------------
/**
 * @Function FrequencyGenerator_On(void)
 * @return Turns output On
 * @author  Jack Lambert, 2022.02.07 */
void SpeakerTone_On(void);

//------------------------------------------------------------------------------

void SpeakerTone_StartupChirp(void);

//------------------------------------------------------------------------------

void SpeakerTone_ShutdownChirp(void);

//------------------------------------------------------------------------------

void SpeakerTone_LowBatteryChirp(void);

//------------------------------------------------------------------------------

void SpeakerTone_ChargingChirp(batLvl_t batChg);

//------------------------------------------------------------------------------

#endif	/* SPEAKERTONE_H */


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
