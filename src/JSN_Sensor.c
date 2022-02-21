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
#include <stdio.h>

//------------------------------------------------------------------------------

#define TRIG1               C6
#define ECHO1               C5

#define TRIG2               A1
#define ECHO2               C3

#define TRIG3               B7
#define ECHO3               A2

// #define JSN_SENSOR_TEST       // toggle comment to enable/disable test harness

//==============================================================================
//---------------------------- STATICS VARIABLES -------------------------------
//==============================================================================

static JSN_t *lastTrig; // pointer to sensor which last sent TRIG signal
static JSN_t *sensPtr;  // a "cursor" for the currently selected sensor
static unsigned long micros;
static JSN_t Sens1, Sens2, Sens3;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void JSN_Sensor_Init(void) {
    // Initialize JSN_t instance variables
    Sens1.distance = 0;
    Sens1.echoHighTime = 0;
    Sens1.echoPin = ECHO1;
    Sens1.trigPin = TRIG1;
    SetPin(ECHO1, INPUT);
    SetPin(TRIG1, OUTPUT);
    WritePin(TRIG1, LOW);

    Sens2.distance = 0;
    Sens2.echoHighTime = 0;
    Sens2.echoPin = ECHO2;
    Sens2.trigPin = TRIG2;
    SetPin(ECHO2, INPUT);
    SetPin(TRIG2, OUTPUT);
    WritePin(TRIG2, LOW);

    Sens3.distance = 0;
    Sens3.echoHighTime = 0;
    Sens3.echoPin = ECHO3;
    Sens3.trigPin = TRIG3;
    SetPin(ECHO3, INPUT);
    SetPin(TRIG3, OUTPUT);
    WritePin(TRIG3, LOW);

    lastTrig = &Sens3; // default lastTrig to last initialized
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
            printf("ERROR: Can only TRIG Sens[1,2,3]");
            break;
    }
    
    WritePin(sensPtr->trigPin, HIGH);
    while ((FRT_GetMicros() - micros) < TRIG_PULSE_WIDTH);
    WritePin(sensPtr->trigPin, LOW);
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
            printf("ERROR: Can only TRIG Sens[1,2,3]");
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

// DevBoard pin designators for test harness execution


// Thresholds for timing + distance measurements
#define SAMPLE_PERIOD       50  // Sensor reading occus every [x]ms
#define MIN_DIST_LED        400 // Turn LED on if object within [x]mm of sensor

// Modularize number of sensors currently in use (inside test harness)
#define NUM_SENSORS         3

//--- SENSOR TESTING MAIN APPLICATION ---//

int main(void) {
    // Initialize required libraries
    PIC16_Init();
    uint8_t numSens = NUM_SENSORS;

    printf("==== WCSA_MainApp.c ====\n");
    printf("// JSN_SENSOR_TEST: %d //\n", numSens);
    
    /*
     * If invalid trig/echoPin, JSN_Sensor_Init() will print error statement
     * & this conditional statement will halt further program execution
     * 
     * NOTE: "break;" statements have purposely been omitted from switch cases
     */
    switch (numSens) {
        case 3:
            if (JSN_Sensor_Init(&Sens3, TRIG3, ECHO3) == ERROR)
                while (1);
        case 2:
            if (JSN_Sensor_Init(&Sens2, TRIG2, ECHO2) == ERROR)
                while (1);
        case 1:
            if (JSN_Sensor_Init(&Sens1, TRIG1, ECHO1) == ERROR)
                while (1);
    }

    // Initialize function variables
    unsigned long currMilli = 0;
    unsigned long prevMilli = 0;
    uint8_t nextSens = 1;

    // Initialize LED as OUTPUT LOW
    SetPin(C0, OUTPUT);
    WritePin(C0, LOW);

    JSN_Sensor_Trig(&Sens3);
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
                    JSN_Sensor_Trig(&Sens1);
                    // print Sens3 distance on TXpin
                    printf("S3 %u", JSN_Sensor_GetDistance(&Sens3));

                    // Update nextSens based on numSens
                    if (numSens > 1)
                        nextSens = 2;
                    else
                        nextSens = 1;

                    break;

                case 2:
                    // Trigger a reading from Sens2
                    JSN_Sensor_Trig(&Sens2);
                    // print Sens1 distance on TXpin
                    printf("S1 %u", JSN_Sensor_GetDistance(&Sens1));

                    // Update nextSens based on numSens
                    if (numSens > 2)
                        nextSens = 3;
                    else
                        nextSens = 1;

                    break;

                case 3:
                    // Trigger a reading from Sens3
                    JSN_Sensor_Trig(&Sens3);
                    // print Sens2 distance on TXpin
                    printf("S2 %u", JSN_Sensor_GetDistance(&Sens2));

                    // Always trigger Sens1 next, after Sens3
                    nextSens = 1;

                    break;
            }

            // Turn on LED if any sensor sees object within MIN_DIST_LED [mm]
            if ((Sens1.distance < MIN_DIST_LED) ||
                    (Sens2.distance < MIN_DIST_LED) ||
                    (Sens3.distance < MIN_DIST_LED)) {
                WritePin(C0, HIGH);
            } else {
                WritePin(C0, LOW);
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
