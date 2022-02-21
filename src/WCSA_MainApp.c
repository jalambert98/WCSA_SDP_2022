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
// #define TRI_SENS_CONFIG


//--- SINGLE-SENSOR TESTING MAIN APPLICATION ---//

#ifdef SINGLE_SENS_CONFIG

int main(void) {
    // Initialize required libraries
    PIC16_Init();
    JSN_Sensor_Init();
    SpeakerTone_Init();    

    printf("==== WCSA_MainApp.c ====\n");
    printf("// SINGLE_SENS_CONFIG //\n");
    
    // Initialize function variables
    unsigned long currMilli = 0;
    unsigned long prevMilli = 0;
    unsigned int distance = 0;

    // Send initial TRIG signal so that reading is ready
    JSN_Sensor_Trig(1);
    currMilli = FRT_GetMillis(); // initial timer reading
    prevMilli = currMilli;

    while (1) {
        // Continuously update free running timer (milliseconds)
        currMilli = FRT_GetMillis();

        // Trigger a sensor reading every SAMPLE_PERIOD milliseconds
        if ((currMilli - prevMilli) >= SAMPLE_PERIOD) {
            distance = JSN_Sensor_GetDistance(1);
            JSN_Sensor_Trig(1);
            printf("%u", distance);

            // Turn on LED if any sensor sees object within MIN_DIST_LED [mm]
            if (distance < WARNING_DISTANCE) {
                SpeakerTone_On();
            }
            else {
                SpeakerTone_Off();
            }

            // Update prevMilli to ensure SAMPLE_PERIOD remains constant
            prevMilli = currMilli;
        }
    }

    return 0;
}
#endif

//--- TRI-SENSOR TESTING MAIN APPLICATION ---//

#ifdef TRI_SENS_CONFIG
int main(void) {
    // Initialize required libraries
    PIC16_Init();
    JSN_Sensor_Init(JSN_SensorGetPtr(1), TRIG1, ECHO1);
    SpeakerTone_Init();
    MotorControl_Init();
    
    printf("==== WCSA_MainApp.c ====\n");
    printf("//   TRI_SENS_CONFIG   //\n");
    
    uint8_t numSens = 3;
    uint8_t S3_Dist = 0;
    uint8_t S2_Dist = 0;
    uint8_t S1_Dist = 0;
    uint8_t x_pos = 0;
    uint8_t y_pos = 0;
    uint8_t z_pos = 0;
    
    switch (numSens) {
        case 3:
            if (JSN_Sensor_Init(JSN_SensorGetPtr(3), TRIG3, ECHO3) == ERROR)
                while (1);
        case 2:
            if (JSN_Sensor_Init(JSN_SensorGetPtr(2), TRIG2, ECHO2) == ERROR)
                while (1);
        case 1:
            if (JSN_Sensor_Init(JSN_SensorGetPtr(1), TRIG1, ECHO1) == ERROR)
                while (1);
    }
    
    // Initialize function variables
    unsigned long currMilli = 0;
    unsigned long prevMilli = 0;
    uint8_t nextSens = 1;

    JSN_Sensor_Trig(JSN_SensorGetPtr(3));
    currMilli = FRT_GetMillis(); // initial timer reading
    prevMilli = currMilli;
    
    while (1) {
        // Continuously update free running timer (milliseconds)
        currMilli = FRT_GetMillis();

        // Trigger a sensor reading every SAMPLE_PERIOD milliseconds
        if ((currMilli - prevMilli) >= SAMPLE_PERIOD) {
            /*
             * Alternate sensor to trig each cycle 
             * NOTE: Each sensor is triggered every (numSens * SAMPLE_PERIOD)ms
             */
            switch (nextSens) {
                case 1:
                    // Trigger a reading from Sens1
                    JSN_Sensor_Trig(JSN_SensorGetPtr(1));
                    // print Sens3 distance on TXpin
                    S3_Dist = JSN_Sensor_GetDistance(JSN_SensorGetPtr(3));
                    printf("S3 %u", S3_Dist);

                    // Update nextSens based on numSens
                    if (numSens > 1)
                        nextSens = 2;
                    else
                        nextSens = 1;

                    break;

                case 2:
                    // Trigger a reading from Sens2
                    JSN_Sensor_Trig(JSN_SensorGetPtr(2));
                    // print Sens1 distance on TXpin
                    S1_Dist = JSN_Sensor_GetDistance(JSN_SensorGetPtr(1));
                    printf("S1 %u", JSN_Sensor_GetDistance(S1_Dist));

                    // Update nextSens based on numSens
                    if (numSens > 2)
                        nextSens = 3;
                    else
                        nextSens = 1;

                    break;

                case 3:
                    // Trigger a reading from Sens3
                    JSN_Sensor_Trig(JSN_SensorGetPtr(3));
                    // print Sens2 distance on TXpin
                    S2_Dist = JSN_Sensor_GetDistance(JSN_SensorGetPtr(2));
                    printf("S2 %u", JSN_Sensor_GetDistance(S2_Dist));

                    // Always trigger Sens1 next, after Sens3
                    nextSens = 1;

                    break;
            }

            // Return 3D map of object using trilateration
            
            
            // Update prevMilli to ensure SAMPLE_PERIOD remains constant
            prevMilli = currMilli;
        }
    }
    
    
    return 0;
}


#endif