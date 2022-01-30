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
#include "FR_Timer.h"
#include "tmr1.h"
#include "ccp1.h"
#include <stdio.h>


#define JSN_SENSOR_TEST

//==============================================================================
//---------------------------- STATICS VARIABLES -------------------------------
//==============================================================================

static JSN_t *lastTrig;     // pointer to sensor which last sent TRIG signal
static unsigned long micros;
static JSN_t Sens1, Sens2, Sens3;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void JSN_Library_Init(void) {
    // Initialize TMR1 & CCP1 peripherals
    TMR1_Initialize();
    CCP1_Initialize();
    JSN_Sensor_Init(&Sens1, C6, C5);
    return;
}

//------------------------------------------------------------------------------

uint8_t JSN_Sensor_Init(JSN_t *Sensor, PinName_t trigPin, PinName_t echoPin) {
    
    // Set echoPin as INPUT if it is one of the following: [A2,A4,C3,C5]
    switch(echoPin) {
        case A2:
        case A4:
        case C3:
        case C5:
            SetPin(echoPin, INPUT);
            break;
        default:
            return ERROR;
    }
    
    // set trigPin as OUTPUT & initialize low
    switch(trigPin) {
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
            return ERROR;
    }
    
    // Initialize JSN_t instance variables
    Sensor->distance = 0;
    Sensor->echoHighTime = 0;
    Sensor->echoPin = echoPin;
    Sensor->trigPin = trigPin;
    
    lastTrig = Sensor;      // default lastTrig to last initialized
    
    return SUCCESS;
}

//------------------------------------------------------------------------------
/*
 *  EXPECTS that FR_Timer_Init() has already been called!!
 */
void JSN_Sensor_Trig(JSN_t *Sensor) {
    micros = FR_Timer_GetMicros();
    
    // Raise TRIG pin HIGH
    WritePin(Sensor->trigPin, HIGH);
    
    // Block further instruction for defined TRIG pulse width duration
    while((FR_Timer_GetMicros() - micros) < TRIG_PULSE_WIDTH);
    
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
    Sensor->distance = (unsigned int)(((uint32_t)Sensor->echoHighTime * 
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

#define SAMPLE_PERIOD       50  // Sensor reading occus every [x]ms
#define MIN_DIST_LED        500 // Turn LED on if object within [x]mm of sensor

int main(void) {
    // Initialize required libraries
    PIC16_Init();
    FR_Timer_Init();
    JSN_Library_Init();
    
    // Initialize function variables
    unsigned long currMilli = 0;
    unsigned long prevMilli = 0;
    SetPin(C0, OUTPUT);
    WritePin(C0, LOW);
    
    JSN_Sensor_Trig(&Sens1);

    while(1) {
        currMilli = FR_Timer_GetMillis();
        
        // This block runs every SAMPLE_PERIOD milliseconds
        if((currMilli - prevMilli) >= SAMPLE_PERIOD) {
            
            // Turn on LED if sensor sees object within MIN_DIST_LED millimeters
            if(JSN_Sensor_GetDistance(&Sens1) < MIN_DIST_LED) {
                WritePin(C0, HIGH);
            }
            else if (Sens1.distance > MIN_DIST_LED) {
                WritePin(C0, LOW);
            }
            
            // Print distance measured by sensor (Serial TX pin = [RC4])
            printf("Distance = %u \n", JSN_Sensor_GetDistance(&Sens1));
            
            // send new TRIG signal*/
            JSN_Sensor_Trig(&Sens1);
            
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
