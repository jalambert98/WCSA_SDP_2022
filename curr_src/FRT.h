/* 
 * File:    FRT.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 25, 2022, 6:52 PM
 */
//------------------------------------------------------------------------------

#include "pin_manager.h"

#ifndef FRT_H
#define	FRT_H

//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================
/**
 * @funct    FRT_GetMillis()
 * 
 * @param    None
 * 
 * @return   unsigned long millis - current FR timer value (in milliseconds)
 * 
 * @brief    Returns the number of MILLISECONDS that have elapsed since
 *           FRT_Init() was last called
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
unsigned long FRT_GetMillis(void);

//------------------------------------------------------------------------------
/**
 * @funct    FRT_GetMicros()
 * 
 * @param    None
 * 
 * @return   unsigned long micros - current FR timer value (in microseconds)
 * 
 * @brief    Returns the number of MICROSECONDS that have elapsed since
 *           FRT_Init() was last called
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
unsigned long FRT_GetMicros(void);

//------------------------------------------------------------------------------
/**
 * @funct    FRT_IncMillis()
 * 
 * @param    None
 * 
 * @return   None
 * 
 * @brief    This function should NOT be called within a main() function!
 *           The general purpose ISR (defined within "PIC16Xpress_DevBoard.c")
 *           will automatically call this function every 250us to increment
 *           millis4x. FRT_GetMillis() accounts for this & returns the
 *           actual millisecond value.
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
void FRT_IncMillis(void);

//------------------------------------------------------------------------------
/**
 * @funct    FRT_IncMillis()
 * 
 * @param    None
 * 
 * @return   None
 * 
 * @brief    This function should NOT be called within a main() function!
 *           The general purpose ISR (defined within "PIC16Xpress_DevBoard.c")
 *           will automatically call this function every 250us to increment
 *           micros1x by 250. FRT_GetMicros() accounts for this & returns 
 *           the sum of micros1x & the current value stored in the TMR0L reg -
 *           which is the actual current FR timer value in microseconds.
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
void FRT_IncMicros(void);


#endif	/* FRT_H */

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
