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


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================
/**
 * @funct   SpeakerTone_Init(speakerPin)
 * @param   PinName_t speakerPin
 * @return  [uint8_t] SUCCESS or ERROR
 * @brief   Initializes the timer and for the tone system
 * @author  Jack Lambert, 2022.02.07 */
void SpeakerTone_Init(void);

//------------------------------------------------------------------------------
/**
 * @funct   SpeakerTone_SetFrequency(unsigned int NewFrequency)
 * @param   newFrequency - new frequency to set. 
 * @return  [uint8_t] SUCCESS or ERROR
 * @brief   Changes the frequency of the  system.
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
