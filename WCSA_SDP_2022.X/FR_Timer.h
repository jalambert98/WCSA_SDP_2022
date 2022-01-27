/* 
 * File:    FR_Timer.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 25, 2022, 6:52 PM
 */

#include "PIC16Xpress_DevBoard.h"

#ifndef FR_TIMER_H
#define	FR_TIMER_H

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================
/**
 * @funct    FR_Timer_Init()
 * 
 * @param    None
 * 
 * @return   None
 * 
 * @brief    ASSUMES PIC16_Init() has already been called to set [F_osc = 8MHz]!
 *           This function initializes TMR0 to tick @1MHz [1us period] & roll
 *           over (& set the TMR0 interrupt flag) every 250us
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
void FR_Timer_Init(void);

//------------------------------------------------------------------------------
/**
 * @funct    FR_Timer_GetMillis()
 * 
 * @param    None
 * 
 * @return   unsigned long millis - current FR timer value (in milliseconds)
 * 
 * @brief    Returns the number of MILLISECONDS that have elapsed since
 *           FR_Timer_Init() was last called
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
unsigned long FR_Timer_GetMillis(void);

//------------------------------------------------------------------------------
/**
 * @funct    FR_Timer_GetMicros()
 * 
 * @param    None
 * 
 * @return   unsigned long micros - current FR timer value (in microseconds)
 * 
 * @brief    Returns the number of MICROSECONDS that have elapsed since
 *           FR_Timer_Init() was last called
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
unsigned long FR_Timer_GetMicros(void);

//------------------------------------------------------------------------------
/**
 * @funct    FR_Timer_IncMillis()
 * 
 * @param    None
 * 
 * @return   None
 * 
 * @brief    This function should NOT be called within a main() function!
 *           The general purpose ISR (defined within "PIC16Xpress_DevBoard.c")
 *           will automatically call this function every 250us to increment
 *           millis4x. FR_Timer_GetMillis() accounts for this & returns the
 *           actual millisecond value.
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
void FR_Timer_IncMillis(void);

//------------------------------------------------------------------------------
/**
 * @funct    FR_Timer_IncMillis()
 * 
 * @param    None
 * 
 * @return   None
 * 
 * @brief    This function should NOT be called within a main() function!
 *           The general purpose ISR (defined within "PIC16Xpress_DevBoard.c")
 *           will automatically call this function every 250us to increment
 *           micros1x by 250. FR_Timer_GetMicros() accounts for this & returns 
 *           the sum of micros1x & the current value stored in the TMR0L reg -
 *           which is the actual current FR timer value in microseconds.
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
void FR_Timer_IncMicros(void);


#endif	/* FR_TIMER_H */

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
