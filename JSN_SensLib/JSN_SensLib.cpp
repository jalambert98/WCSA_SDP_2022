/* 
 * File:            JSN_SensLib.cpp
 * Author:          Jack Lambert <joalambe@ucsc.edu>
 * Project:         White Cane Sensor Attachment
 * Course:          UCSC ECE129 - SDP '21
 *
 * Created:         January 12, 2022, 1:35 PM
 * Last Modified:   January 12, 2022, 7:30 PM
 */

 #include "Arduino.h"
 #include "JSN_SensLib.h"
 
//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define US_WAVE_SPEED       340     // speed of ultrasonic wave = 340[m/s]
#define MICROS_PER_MILLI    1000


//==============================================================================
//---------------------------- STATICS VARIABLES -------------------------------
//==============================================================================
      
static unsigned long timeUp[3], timeDown[3], echoHighTime[3]; // in microseconds
static unsigned int distance[3];                              // in millimeters
static uint8_t echoSet[3];                                    // 0 or 1


//==============================================================================
//-------------------------------- CONSTRUCTOR ---------------------------------
//==============================================================================

JSN_SensLib::JSN_SensLib() {  
  // Configure TRIG pins as MCU outputs
  pinMode(TRIG1, OUTPUT);   // pin5
  pinMode(TRIG2, OUTPUT);   // pin6
  pinMode(TRIG3, OUTPUT);   // pin8

  // Initialize TRIG pins LOW
  digitalWrite(TRIG1, LOW);
  digitalWrite(TRIG2, LOW);
  digitalWrite(TRIG3, LOW);

  // Configure ECHO pins as MCU inputs
  pinMode(ECHO1, INPUT);    // pin2
  pinMode(ECHO2, INPUT);    // pin3
  pinMode(ECHO3, INPUT);    // pin7

  // Configure ECHO pins to run ISR each input pin value CHANGE
  attachInterrupt(digitalPinToInterrupt(ECHO1), ISR_ECHO1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ECHO2), ISR_ECHO2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ECHO3), ISR_ECHO3, CHANGE);

  // Initialize static vars
  uint8_t i = 0;
  for(i=0; i<3; i++) {
    echoSet[i] = 0;
    echoHighTime[i] = 0;
    timeUp[i] = 0;
    timeDown[i] = 0;
    distance[i] = 0;
  }
}


//==============================================================================
//----------------------------- FUNCTION LIBRARY -------------------------------
//==============================================================================

void JSN_Init() {
  // Possibly unnecessary
}

//------------------------------------------------------------------------------

unsigned int JSN_GetDistance(uint8_t sens) {
  return distance[sens-1];
}

//------------------------------------------------------------------------------

void JSN_Trig(uint8_t sens) {
  // Raise specified TRIG pin HIGH for 10us, then reset LOW
  uint8_t trig = 0;
  switch(sens) {
    case 1:
      trig = TRIG1;
      break;
    case 2:
      trig = TRIG2;
      break;
    case 3:
      trig = TRIG3;
      break;
  }

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
}

//------------------------------------------------------------------------------

unsigned int JSN_TOF_mm(unsigned long tofMicro) {
  return (tofMicro*US_WAVE_SPEED)/(MICROS_PER_MILLI<<1);
}


//==============================================================================
//------------------------ INTERRUPT SERVICE ROUTINES --------------------------
//==============================================================================

static void ISR_ECHO1() {
  // If ECHO1 pin is currently HIGH, but was previously LOW...
  if (digitalRead(ECHO1) == HIGH) {
    if (echoSet[0] == 0) {
      //...indicate that it was set high & store current micros()
      echoSet[0] = 1;
      timeUp[0] = micros();
    }
  }
  // If ECHO1 pin is currently LOW, but was previously HIGH...
  else if (digitalRead(ECHO1) == LOW) {
    if (echoSet[0] == 1) {
      //...indicate that it was set low & store current micros()
      echoSet[0] = 0;
      timeDown[0] = micros();

      // Then calculate ToF & convert to mm distance
      echoHighTime[0] = timeDown[0] - timeUp[0];
      distance[0] = JSN_TOF_mm(echoHighTime[0]);
    }
  }
}

//------------------------------------------------------------------------------

static void ISR_ECHO2() {
  // If ECHO2 pin is currently HIGH, but was previously LOW...
  if (digitalRead(ECHO2) == HIGH) {
    if (echoSet[1] == 0) {
      //...indicate that it was set high & store current micros()
      echoSet[1] = 1;
      timeUp[1] = micros();
    }
  }
  // If ECHO2 pin is currently LOW, but was previously HIGH...
  else if (digitalRead(ECHO2) == LOW) {
    if (echoSet[1] == 1) {
      //...indicate that it was set low & store current micros()
      echoSet[1] = 0;
      timeDown[1] = micros();

      // Then calculate ToF & convert to mm distance
      echoHighTime[1] = timeDown[1] - timeUp[1];
      distance[1] = JSN_TOF_mm(echoHighTime[1]);
    }
  }
}

//------------------------------------------------------------------------------

static void ISR_ECHO3() {
  // If ECHO3 pin is currently HIGH, but was previously LOW...
  if (digitalRead(ECHO3) == HIGH) {
    if (echoSet[2] == 0) {
      //...indicate that it was set high & store current micros()
      echoSet[2] = 1;
      timeUp[2] = micros();
    }
  }
  // If ECHO3 pin is currently LOW, but was previously HIGH...
  else if (digitalRead(ECHO3) == LOW) {
    if (echoSet[2] == 1) {
      //...indicate that it was set low & store current micros()
      echoSet[2] = 0;
      timeDown[2] = micros();

      // Then calculate ToF & convert to mm distance
      echoHighTime[2] = timeDown[2] - timeUp[2];
      distance[2] = JSN_TOF_mm(echoHighTime[2]);
    }
  }
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
