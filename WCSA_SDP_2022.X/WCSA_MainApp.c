/* 
 * File:    WCSA_MainApp.c
 * Author:  
 * Project: WCSA_SDP_2022
 * 
 * Created on 02/20/2022 @2:45PM
 */
//------------------------------------------------------------------------------

#include "PIC16Xpress_DevBoard.h"
#include "FRT.h"
#include "JSN_Sensor.h"
#include "SpeakerTone.h"
#include "MotorControl.h"
#include <stdio.h>

// DevBoard pin designators for test harness execution
#define TRIG1               C6
#define ECHO1               C5

#define TRIG2               A1
#define ECHO2               C3

#define TRIG3               B7
#define ECHO3               A2

// Thresholds for timing + distance measurements
#define SAMPLE_PERIOD       50  // Sensor reading occus every [x]ms
#define WARNING_DISTANCE    400

// Modularize number of sensors currently in use (inside test harness)
#define SINGLE_SENS_CONFIG
//#define TRI_SENS_CONFIG


//--- SINGLE-SENSOR TESTING MAIN APPLICATION ---//

#ifdef SINGLE_SENS_CONFIG

int main(void) {
    // Initialize required libraries
    PIC16_Init();
    JSN_Sensor_Init(JSN_SensorGetPtr(1), TRIG1, ECHO1);
    SpeakerTone_Init();
    MotorControl_Init();
    /*
     * If invalid trig/echoPin, JSN_Sensor_Init() will print error statement
     * & this conditional statement will halt further program execution
     */
    

    // Initialize function variables
    unsigned long currMilli = 0;
    unsigned long prevMilli = 0;
    unsigned int distance = 0;

    // Send initial TRIG signal so that reading is ready
    JSN_Sensor_Trig(JSN_SensorGetPtr(1));
    currMilli = FRT_GetMillis(); // initial timer reading
    prevMilli = currMilli;

    while (1) {
        // Continuously update free running timer (milliseconds)
        currMilli = FRT_GetMillis();

        // Trigger a sensor reading every SAMPLE_PERIOD milliseconds
        if ((currMilli - prevMilli) >= SAMPLE_PERIOD) {
            distance = JSN_Sensor_GetDistance(JSN_SensorGetPtr(1));
            printf("%u", distance);

            // Turn on LED if any sensor sees object within MIN_DIST_LED [mm]
            if (distance < WARNING_DISTANCE) {
                // do something
            }
            else {
                // do nothing
            }

            // Update prevMilli to ensure SAMPLE_PERIOD remains constant
            prevMilli = currMilli;
        }
    }

    return 0;
}

#endif
