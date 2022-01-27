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
 * @funct    JSN_Library_Init()
 * 
 * @param    None
 * 
 * @return   uint8_t [SUCCESS or ERROR]
 * 
 * @brief    Initializes the hardware peripherals required to operate the JSN
 *           ultrasonic sensors. This includes: [TMRx], [ICx]
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
uint8_t JSN_Library_Init(void);

//------------------------------------------------------------------------------
/**
 * @funct    JSN_Sensor_Init(*Sensor, trigPin, echoPin)
 * 
 * @param    JSN_t *Sensor      - A pointer to the JSN_t instance to initialize
 *           PinName_t trigPin  - Pin name to assign to TRIG pin
 *           PinName_t echoPin  - Pin name to assign to ECHO pin
 * 
 * @return   uint8_t [SUCCESS or ERROR]
 * 
 * @brief    Initializes a JSN_t struct by accepting a pointer to the sensor,
 *           clearing its echoHighTime & distance variables, setting its
 *           trigPin & echoPin variables, and properly initializing the pins
 *           as inputs/outputs.
 * NOTE:     echoPin MUST BE one of the following: [RA2, RA4, RC3, RC5] & 
 *           trigPin MAY NOT BE any of the following: [RA2, RA4, RC3, RC5, RA3]
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
uint8_t JSN_Sensor_Init(JSN_t *Sensor, PinName_t trigPin, PinName_t echoPin);

//------------------------------------------------------------------------------
/**
 * @funct    JSN_Sensor_Trig(*Sensor)
 * 
 * @param    JSN_t *Sensor  - Pointer to JSN sensor
 * 
 * @return   None
 * 
 * @brief    Sends the appropriate trigger signal (HIGH for >10us) to the pin
 *           associated with [Sensor->trigPin]
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
void JSN_Sensor_Trig(JSN_t *Sensor);

//------------------------------------------------------------------------------
/**
 * @funct    GetDistance(*Sensor)
 * 
 * @param    JSN_t *Sensor  - Pointer to JSN sensor
 * 
 * @return   unsigned int dist  :  distance reading (in mm) last measured by the 
 *                                 instance of the JSN sensor
 * 
 * @brief    Returns the last distance reading (in mm) measured by the sensor
 *           associated with the JSN_t struct pointer argument
 * 
 * @author   Jack Lambert, 2022.01.25
 **/
unsigned int JSN_Sensor_GetDistance(JSN_t *Sensor);

//------------------------------------------------------------------------------


#endif	/* JSN_SENSOR_H */

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
