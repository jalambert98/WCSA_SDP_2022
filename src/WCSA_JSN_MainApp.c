/* 
 * File:    WCSA_JSN_MainApp.c
 * Author:  Jack Lambert <joalambe@ucsc.edu> & Evan Mayhew <emayhew@ucsc.edu>
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
#define WARNING_DISTANCE    1500
#define MIN_FEEDBACK_TIME   500

// Modularize number of sensors currently in use
// #define SINGLE_SENS_TEST
// #define TRI_SENS_TEST

//------------------------------------------------------------------------------

//----------- SINGLE-SENSOR TESTING MAIN APPLICATION -----------//

#ifdef SINGLE_SENS_TEST

int main(void) {
    // Initialize required libraries
    PIC16_Init();
    JSN_Sensor_Init(SINGLE_SENS_CONFIG);
    SpeakerTone_Init();    

    printf("==== WCSA_MainApp.c ====\n");
    printf("SINGLE_SENS_CONFIG - Last compiled on %s at %s\n", __DATE__, __TIME__);
    
    // Initialize function variables
    unsigned long currMilli = 0;
    unsigned long prevMilli = 0;
    unsigned int distance = 0;
    unsigned long speakerOnTime = 0;

    // Send initial TRIG signal so that reading is ready
    JSN_Sensor_Trig(1);
    currMilli = FRT_GetMillis(); // initial timer reading
    prevMilli = currMilli;

    
    //==========================================//
    //-------------- PRIMARY LOOP --------------//
    //==========================================//
    while (1) {
        // Continuously update free running timer (milliseconds)
        currMilli = FRT_GetMillis();

        // Trigger a sensor reading every SAMPLE_PERIOD milliseconds
        if ((currMilli - prevMilli) >= SAMPLE_PERIOD) {
            distance = JSN_Sensor_GetDistance(1);
            JSN_Sensor_Trig(1);
            printf("S1 = %umm\n", distance);

            // Turn on LED if any sensor sees object within MIN_DIST_LED [mm]
            if (distance < WARNING_DISTANCE) {
                SpeakerTone_On();
                speakerOnTime = currMilli;
            }
            /*
             * This part isn't working yet!! (Speaker should always remain on
             * for at least MIN_FEEDBACK_TIME, but for some reason it doesn't??)
             */
            else if ((currMilli - speakerOnTime) > MIN_FEEDBACK_TIME) {
                SpeakerTone_Off();
            }

            // Update prevMilli to ensure SAMPLE_PERIOD remains constant
            prevMilli = currMilli;
        }
    }

    return 0;
}
#endif


//----------- TRI-SENSOR TESTING MAIN APPLICATION -----------//

#ifdef TRI_SENS_TEST

int main(void) {
    // Initialize required libraries
    PIC16_Init();
    JSN_Sensor_Init(TRI_SENS_CONFIG);
    // SpeakerTone_Init();
    // MotorControl_Init();
    
    printf("==== WCSA_MainApp.c ====\n");
    printf("TRI_SENS_CONFIG - Last compiled on %s at %s\n", __DATE__, __TIME__);

    unsigned int s1Dist = 0;
    unsigned int s2Dist = 0;    
    unsigned int s3Dist = 0;
    
    /*
     * uint8_t xPos = 0;
     * uint8_t yPos = 0;
     * uint8_t zPos = 0;
     */

    // Initialize timer variables
    unsigned long currMilli = 0;
    unsigned long prevMilli = 0;
    
    // TRIG Sens3 first, then continue as: [1,2,3,1,2,3,...]
    uint8_t nextSens = 1;
    JSN_Sensor_Trig(3);
    
    // Current timer reading (fresh)
    currMilli = FRT_GetMillis(); // initial timer reading
    prevMilli = currMilli;
    
    
    //==========================================//
    //-------------- PRIMARY LOOP --------------//
    //==========================================//
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
                    JSN_Sensor_Trig(1);
                    // print Sens3 distance on TXpin
                    s3Dist = JSN_Sensor_GetDistance(3);
                    printf("S3=%u\n", s3Dist);

                    nextSens = 2;
                    break;

                case 2:
                    // Trigger a reading from Sens2
                    JSN_Sensor_Trig(2);
                    // print Sens1 distance on TXpin
                    s1Dist = JSN_Sensor_GetDistance(1);
                    printf("S1=%u\n", s1Dist);

                    nextSens = 3;
                    break;

                case 3:
                    // Trigger a reading from Sens3
                    JSN_Sensor_Trig(3);
                    
                    // print Sens2 distance on TXpin
                    s2Dist = JSN_Sensor_GetDistance(2);
                    printf("S2=%u\n", s2Dist);

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

//------------------------------------------------------------------------------

#endif

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
