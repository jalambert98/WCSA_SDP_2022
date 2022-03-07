/* 
 * File:    JSN_Sensor.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 * 
 * Created on January 24, 2022, 10:29 PM
 */
//------------------------------------------------------------------------------

#include "JSN_Sensor.h"
#include "PIC16Xpress_DevBoard.h"
#include "FRT.h"
#include "tmr1.h"
#include "ccp1.h"
#include "ccp2.h"
#include "ccp3.h"
#include <stdio.h>


//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define TRIG1               C6
#define ECHO1               C5

#define TRIG2               A1
#define ECHO2               C3

#define TRIG3               B7
#define ECHO3               A2

#define JSN_SENSOR_TEST       // toggle comment to enable/disable test harness

//==============================================================================
//---------------------------- STATICS VARIABLES -------------------------------
//==============================================================================

static JSN_t *lastTrig; // pointer to sensor which last sent TRIG signal
static JSN_t *sensPtr; // a "cursor" for the currently selected sensor
static unsigned long micros;
static JSN_t Sens1, Sens2, Sens3;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void JSN_Sensor_Init(uint8_t sensConfig) {
    switch (sensConfig) {
        case TRI_SENS_CONFIG:
            // Initialize Input Capture [2,3] 
            //(no break, so CCP1 & TMR1 init below)
            CCP3_Initialize();
            CCP2_Initialize();
            
            Sens3.distance = 0;
            Sens3.echoHighTime = 0;
            Sens3.echoPin = ECHO3;
            Sens3.trigPin = TRIG3;
            PIC16_SetPin(ECHO3, INPUT);
            PIC16_SetPin(TRIG3, OUTPUT);
            PIC16_WritePin(TRIG3, LOW);
            
            Sens2.distance = 0;
            Sens2.echoHighTime = 0;
            Sens2.echoPin = ECHO2;
            Sens2.trigPin = TRIG2;
            PIC16_SetPin(ECHO2, INPUT);
            PIC16_SetPin(TRIG2, OUTPUT);
            PIC16_WritePin(TRIG2, LOW);

            // INTENTIONAL - no break statement here (must still init Sens1)

        case SINGLE_SENS_CONFIG:
            // Initialize TMR1 & Input Capture Pin
            CCP1_Initialize();
            TMR1_Initialize();
            
            Sens1.distance = 0;
            Sens1.echoHighTime = 0;
            Sens1.echoPin = ECHO1;
            Sens1.trigPin = TRIG1;
            PIC16_SetPin(ECHO1, INPUT);
            PIC16_SetPin(TRIG1, OUTPUT);
            PIC16_WritePin(TRIG1, LOW);

            lastTrig = &Sens1; // default lastTrig to Sens1 (since always used)
            break;

        default:
            printf("ERROR: JSN_Sensor_Init() must contain arg: SINGLE_SENS_CONFIG or TRI_SENS_CONFIG\n");
            break;
    }
    return;
}

//------------------------------------------------------------------------------

void JSN_Sensor_Trig(uint8_t sensNum) {
    micros = FRT_GetMicros();

    // Raise TRIG pin HIGH for TRIG_PULSE_WIDTH microseconds
    switch (sensNum) {
        case 1:
            sensPtr = &Sens1;
            break;
        case 2:
            sensPtr = &Sens2;
            break;
        case 3:
            sensPtr = &Sens3;
            break;
        default:
            printf("ERROR: Can only TRIG Sens[1,2,3]\n");
            break;
    }

    PIC16_WritePin(sensPtr->trigPin, HIGH);
    while ((FRT_GetMicros() - micros) < TRIG_PULSE_WIDTH);
    PIC16_WritePin(sensPtr->trigPin, LOW);
    lastTrig = sensPtr;

    return;
}

//------------------------------------------------------------------------------

unsigned int JSN_Sensor_GetDistance(uint8_t sensNum) {
    switch (sensNum) {
        case 1:
            sensPtr = &Sens1;
            break;
        case 2:
            sensPtr = &Sens2;
            break;
        case 3:
            sensPtr = &Sens3;
            break;
        default:
            printf("ERROR: Can only TRIG Sens[1,2,3]\n");
            break;
    }

    /*
     * This type-casting looks really stupid, but it's 100% necessary,
     * so DON'T TOUCH IT!! (echoHighTime needs to be cast as a 32-bit variable)
     */

    sensPtr->distance = (unsigned int) (((uint32_t) sensPtr->echoHighTime *
            US_WAVE_SPEED) / (MICROS_PER_MILLI << 1));
    return sensPtr->distance;
}

//------------------------------------------------------------------------------

JSN_t* JSN_GetLastTrig(void) {
    return lastTrig;
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

#ifdef JSN_SENSOR_TEST


// Thresholds for timing + distance measurements
#define SAMPLE_PERIOD       50  // Sensor reading occus every [x]ms
#define MIN_DIST_LED        400 // Turn LED on if object within [x]mm of sensor

// Set SENS_CONFIG to either: [SINGLE_SENS_CONFIG or TRI_SENS_CONFIG]
#define SENS_CONFIG         TRI_SENS_CONFIG     

#define LED_PIN             C2

//--- SENSOR TESTING MAIN APPLICATION ---//

int main(void) {
    // Initialize required libraries
    PIC16_Init();
    JSN_Sensor_Init(SENS_CONFIG);
    uint8_t sensConfig = SENS_CONFIG;

    printf("==== JSN_Sensor.c ====\n");
    printf("// JSN_SENSOR_TEST //\n");

    // Initialize function variables
    unsigned long currMilli = 0;
    unsigned long prevMilli = 0;
    uint8_t nextSens = 1;

    // Initialize LED as OUTPUT LOW
    PIC16_SetPin(LED_PIN, OUTPUT);
    PIC16_WritePin(LED_PIN, LOW);

    JSN_Sensor_Trig(3);
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
                    JSN_Sensor_Trig(1);
                    // print Sens3 distance on TXpin
                    printf("S3 = %u\n", JSN_Sensor_GetDistance(3));

                    // Update nextSens based on sensConfig
                    switch (sensConfig) {
                        case SINGLE_SENS_CONFIG:
                            nextSens = 1;
                            break;
                        case TRI_SENS_CONFIG:
                            nextSens = 2;
                            break;
                        default:
                            printf("ERROR: sensConfig must be [SINGLE_SENS_CONFIG or TRI_SENS_CONFIG]\n");
                            break;
                    }

                    break;

                case 2:
                    // Trigger a reading from Sens2
                    JSN_Sensor_Trig(2);
                    // print Sens1 distance on TXpin
                    printf("S1 = %u\n", JSN_Sensor_GetDistance(1));
                    nextSens = 3;
                    break;

                case 3:
                    // Trigger a reading from Sens3
                    JSN_Sensor_Trig(3);
                    // print Sens2 distance on TXpin
                    printf("S2 = %u\n", JSN_Sensor_GetDistance(2));
                    nextSens = 1;
                    break;
            }

            // Turn on LED if any sensor sees object within MIN_DIST_LED [mm]
            if ((Sens1.distance < MIN_DIST_LED) || ((sensConfig == TRI_SENS_CONFIG) &&
                    ((Sens2.distance < MIN_DIST_LED) ||
                    (Sens3.distance < MIN_DIST_LED)))) {
                PIC16_WritePin(LED_PIN, HIGH);
            } else {
                PIC16_WritePin(LED_PIN, LOW);
            }

            // Update prevMilli to ensure SAMPLE_PERIOD remains constant
            prevMilli = currMilli;
        }
    }

    return 0;
}

#endif

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
