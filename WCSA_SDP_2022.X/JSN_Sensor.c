/* 
 * File:    JSN_Sensor.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 * Kenan Gedik 
 * Created on January 24, 2022, 10:29 PM
 */
//------------------------------------------------------------------------------

#include "JSN_Sensor.h"
#include "PIC16Xpress_DevBoard.h"
#include "FRT.h"
#include "tmr1.h"
#include "ccp1.h"
#include <stdio.h>

#define JSN_SENSOR_TEST       // toggle comment to enable/disable test harness

//==============================================================================
//---------------------------- STATICS VARIABLES -------------------------------
//==============================================================================

static JSN_t *lastTrig; // pointer to sensor which last sent TRIG signal
static unsigned long micros;
static JSN_t Sens1, Sens2, Sens3;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

uint8_t JSN_Sensor_Init(JSN_t *Sensor, PinName_t trigPin, PinName_t echoPin) {
    /*
     * Need to move JSN_Sensor_Init() calls into this function once
     * MCU pin config is finalized
     */

    // Set echoPin as INPUT if it is one of the following: [A2,A4,C3,C5]
    switch (echoPin) {
        case A2:
        case A4:
        case C3:
        case C5:
            SetPin(echoPin, INPUT);
            break;
        default:
            printf("ERROR: Invalid echoPin (must be [A2, A4, C3, C5])");
            return ERROR;
    }

    // set trigPin as OUTPUT & initialize low
    switch (trigPin) {
        case A5:
        case C4:
        case C6:
        case C7:
        case B7:
        case B6:
        case B5:
        case B4:
        case C2:
        case C1:
        case C0:
        case A1:
        case A0:
            SetPin(trigPin, OUTPUT);
            WritePin(trigPin, LOW);
            break;
        default:
            printf("ERROR: Invalid trigPin (must NOT be [A2, A3, A4, C3, C5])");
            return ERROR;
    }

    // Initialize JSN_t instance variables
    Sensor->distance = 0;
    Sensor->echoHighTime = 0;
    Sensor->echoPin = echoPin;
    Sensor->trigPin = trigPin;

    lastTrig = Sensor; // default lastTrig to last initialized

    return SUCCESS;
}

//------------------------------------------------------------------------------

void JSN_Sensor_Trig(JSN_t *Sensor) {
    micros = FRT_GetMicros();

    // Raise TRIG pin HIGH
    WritePin(Sensor->trigPin, HIGH);

    // Block further instruction for defined TRIG pulse width duration
    while ((FRT_GetMicros() - micros) < TRIG_PULSE_WIDTH);

    // Lower TRIG pin after pulse duration elapsed
    WritePin(Sensor->trigPin, LOW);

    // Indicate that this Sensor was last to send TRIG pulse
    lastTrig = Sensor;
    return;
}

//------------------------------------------------------------------------------

unsigned int JSN_Sensor_GetDistance(JSN_t *Sensor) {
    /*
     * This type-casting looks really stupid, but it's 100% necessary,
     * so DON'T TOUCH IT!! (echoHighTime needs to be cast as a 32-bit variable)
     */
    Sensor->distance = (unsigned int) (((uint32_t) Sensor->echoHighTime *
            US_WAVE_SPEED) / (MICROS_PER_MILLI << 1));
    return Sensor->distance;
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
#define TRIG1               C6
#define ECHO1               C5

#define TRIG2               A1
#define ECHO2               C3

#define TRIG3               B7
#define ECHO3               A2

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
            }
            else {
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
