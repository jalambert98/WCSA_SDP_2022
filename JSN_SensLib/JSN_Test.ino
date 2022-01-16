/* 
 * File:            JSN_Test.ino
 * Author:          Jack Lambert <joalambe@ucsc.edu>
 * Project:         White Cane Sensor Attachment
 * Course:          UCSC ECE129 - SDP '21
 *
 * Created:         January 15, 2022, 6:30 PM
 * Last Modified:   January 15, 2022, 12:25 AM
 */

#include "JSN_SensLib.h"

#define PING_RATE       500000    // 500,000us = 0.5s
#define BAUDRATE        115200

unsigned int distance[3];
unsigned long currMicro;
unsigned long prevMicro;
  
void setup() {
  SET_LED_OUT();
  LED_OFF();
  JSN_SensLib(INPUT_CAPTURE);
  Serial.begin(BAUDRATE);  
}

void loop() {
  JSN_SensLib::Trig(1);
  delay(250);
  Serial.print("Distance = ");
  Serial.print(JSN_SensLib::GetDistance(1));
  Serial.print("\n");
  delay(250);
}
