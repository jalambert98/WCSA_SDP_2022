/* 
 * File:    SpeakerTone.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on February 7, 2022, 8:20 PM
 */
//------------------------------------------------------------------------------

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
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================
/**
 * @funct   SpeakerTone_Init(speakerPin)
 * @param   None
 * @return  None
 * @brief   Initializes the SpeakerTone pin (C1) to 440Hz (tone disabled)
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

#endif	/* SPEAKERTONE_H */


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
