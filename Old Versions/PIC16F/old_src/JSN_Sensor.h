/* 
 * File:    JSN_Sensor.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 24, 2022, 10:24 PM
 */
//------------------------------------------------------------------------------

#include "PIC16Xpress_DevBoard.h"

#ifndef JSN_SENSOR_H
#define	JSN_SENSOR_H

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define US_WAVE_SPEED       343     // speed of ultrasonic wave [m/s]
#define TRIG_PULSE_WIDTH    11      // > 10us minimum pulse width
#define MICROS_PER_MILLI    1000

#define SINGLE_SENS_CONFIG  0
#define TRI_SENS_CONFIG     1

//==============================================================================
//-------------------------------- TYPEDEFS ------------------------------------
//==============================================================================

typedef struct {
    unsigned int echoHighTime;
    unsigned int distance;
    PinName_t trigPin;
    PinName_t echoPin;
} JSN_t;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================
/**
 * @funct    JSN_Sensor_Init(*Sensor, trigPin, echoPin)
 * 
 * @param    uint8_t sensConfig: SINGLE_SENS_CONFIG or TRI_SENS_CONFIG
 * 
 * @return   None
 * 
 * @brief    Initializes all JSN_t structs by:
 *           clearing the echoHighTime & distance variables, setting the
 *           trigPin & echoPin variables, and properly initializing the pins
 *           as inputs/outputs.
 * NOTE:     echoPin MUST BE one of the following: [RA2, RA4, RC3, RC5] & 
 *           trigPin MAY NOT BE any of the following: [RA2, RA4, RC3, RC5, RA3]
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
void JSN_Sensor_Init(uint8_t sensConfig);

//------------------------------------------------------------------------------
/**
 * @funct    JSN_Sensor_Trig(*Sensor)
 * 
 * @param    uint8_t sensNum
 * 
 * @return   None
 * 
 * @brief    Sends the appropriate trigger signal (HIGH for >10us) to the pin
 *           associated with [Sensor->trigPin]
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
void JSN_Sensor_Trig(uint8_t sensNum);

//------------------------------------------------------------------------------
/**
 * @funct    GetDistance(*Sensor)
 * 
 * @param    uint8_t sensNum
 * 
 * @return   unsigned int dist  :  distance reading (in mm) last measured by the 
 *                                 instance of the JSN sensor
 * 
 * @brief    Returns the last distance reading (in mm) measured by the sensor
 *           associated with the JSN_t struct pointer argument
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
unsigned int JSN_Sensor_GetDistance(uint8_t sensNum);

//------------------------------------------------------------------------------

JSN_t* JSN_GetLastTrig(void);

//------------------------------------------------------------------------------

#endif	/* JSN_SENSOR_H */

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
