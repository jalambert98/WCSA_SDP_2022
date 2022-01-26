/* 
 * File:    JSN_Sensor.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 24, 2022, 10:29 PM
 */

#include "JSN_Sensor.h"
#include <stdio.h>

#define JSN_SENSOR_TEST

//==============================================================================
//---------------------------- STATICS VARIABLES -------------------------------
//==============================================================================


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

uint8_t JSN_Library_Init(void) {
    // Configure Timers
    
    
    return SUCCESS;
}

//------------------------------------------------------------------------------

uint8_t JSN_Sensor_Init(JSN_t *Sensor, PinName_t trigPin, PinName_t echoPin) {
    
    // Set echoPin as INPUT if it is one of the following: [A2,A4,C3,C5]
    switch(echoPin) {
        case A2:
            SET_A2() = INPUT;
            break;
        case A4:
            SET_A4() = INPUT;
            break;
        case C3:
            SET_C3() = INPUT;
            break;
        case C5:
            SET_C5() = INPUT;
            break;
        default:
            printf("ERROR! echoPin must be one of the following: [RA2, RA4, RC3, RC5]\n");
            return ERROR;
    }
    
    // set trigPin as OUTPUT & initialize low
    switch(trigPin) {
        case A2:
        case A4:
        case C3:
        case C5:
        case A3:
            printf("ERROR! trigPin may not be any of the following: [RA2, RA4, RC3, RC5, RA3]\n");
            return ERROR;
        case A5:
            SET_A5() = OUTPUT;
            WRITE_A5() = LOW;
            break;
        case C4:
            SET_C4() = OUTPUT;
            WRITE_C4() = LOW;
            break;
        case C6:
            SET_C6() = OUTPUT;
            WRITE_C6() = LOW;
            break;
        case C7:
            SET_C7() = OUTPUT;
            WRITE_C7() = LOW;
            break;
        case B7:
            SET_B7() = OUTPUT;
            WRITE_B7() = LOW;
            break;
        case B6:
            SET_B6() = OUTPUT;
            WRITE_B6() = LOW;
            break;
        case B5:
            SET_B5() = OUTPUT;
            WRITE_B5() = LOW;
            break;
        case B4:
            SET_B4() = OUTPUT;
            WRITE_B4() = LOW;
            break;
        case C2:
            SET_C2() = OUTPUT;
            WRITE_C2() = LOW;
            break;
        case C1:
            SET_C1() = OUTPUT;
            WRITE_C1() = LOW;
            break;
        case C0:
            SET_C0() = OUTPUT;
            WRITE_C0() = LOW;
            break;
        case A1:
            SET_A1() = OUTPUT;
            WRITE_A1() = LOW;
            break;
        case A0:
            SET_A0() = OUTPUT;
            WRITE_A0() = LOW;
            break;
    }
    
    // Initialize JSN_t instance variables
    Sensor->distance = 0;
    Sensor->echoHighTime = 0;
    Sensor->echoPin = echoPin;
    Sensor->trigPin = trigPin;
    
    return SUCCESS;
}

//------------------------------------------------------------------------------

void JSN_Sensor_Trig(JSN_t *Sensor) {
    return;
}

//------------------------------------------------------------------------------

unsigned int JSN_Sensor_GetDistance(JSN_t *Sensor) {
    return 0;
}

//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

#ifdef JSN_SENSOR_TEST

int main(void) {
    JSN_t Sens1, Sens2, Sens3;
    while(1);
    return 0;
}

#endif

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
