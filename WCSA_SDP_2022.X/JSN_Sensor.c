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


// #define JSN_SENSOR_TEST       // toggle comment to enable/disable test harness

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
#define TRIG2               A1
#define ECHO1               C5
#define ECHO2               C3

#define SAMPLE_PERIOD       50  // Sensor reading occus every [x]ms
#define MIN_DIST_LED        500 // Turn LED on if object within [x]mm of sensor


int main(void) {
    // Initialize required libraries
    PIC16_Init();
    
    /*
     * If invalid trig/echoPin, Init() function will print error statement
     * & this conditional statement will halt further program execution
     */
    if(JSN_Sensor_Init(&Sens1, TRIG1, ECHO1) == ERROR)
        while(1);
    if(JSN_Sensor_Init(&Sens2, TRIG2, ECHO2) == ERROR)
        while(1);

    // Initialize function variables
    unsigned long currMilli = FRT_GetMillis();  // initial timer reading
    unsigned long prevMilli = currMilli;        // before event->(prev == curr)
    uint8_t i = 1;                              // read Sens1 first
    
    // Initialize LED as OUTPUT LOW
    SetPin(C0, OUTPUT);
    WritePin(C0, LOW);

    /*
     * Initially trigger Sens2 in order to prepare readings from
     * BOTH sensors after the first TRIG cycle
     */
    JSN_Sensor_Trig(&Sens2);
  
    while (1) {
        // Continuously update free running timer (milliseconds)
        currMilli = FRT_GetMillis();

        // Trigger a sensor reading every SAMPLE_PERIOD milliseconds
        if ((currMilli - prevMilli) >= SAMPLE_PERIOD) {            
            /*
             * Alternate sensor to trig each cycle 
             * (each sensor reads every [2*SAMPLE_PERIOD])
             */
            switch (i) {
                case 1:
                    // Trigger a reading from Sens1
                    JSN_Sensor_Trig(&Sens1);
                    i = 2;
                    break;
                case 2:                    
                    // Trigger a reading from Sens2
                    JSN_Sensor_Trig(&Sens2);
                    i = 1;
                    break;
            }
            
            // Turn on LED if either sensor sees object within MIN_DIST_LED [mm]
            if ((Sens1.distance < MIN_DIST_LED)||(Sens2.distance < MIN_DIST_LED)) {
                WritePin(C0, HIGH);
            } else {
                WritePin(C0, LOW);
            }
            
            // Print distance measured by sensor (Serial TX pin = [RC4])
            printf("%u", JSN_Sensor_GetDistance(&Sens1));
            printf("%u", JSN_Sensor_GetDistance(&Sens2));

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
