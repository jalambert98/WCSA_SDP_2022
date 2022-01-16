/* 
 * File:            JSN_SensLib.ino
 * Author:          Jack Lambert <joalambe@ucsc.edu>
 * Project:         White Cane Sensor Attachment
 * Course:          UCSC ECE129 - SDP '21
 *
 * Created:         January 12, 2022, 1:30 PM
 * Last Modified:   
 */

#include "JSN_SensLib.h"

#define PING_RATE       500000    // 500,000us = 0.5s

unsigned int distance[3];
unsigned long currMicro;
unsigned long prevMicro;
JSN_SensLib jsn = new JSN_SensLib(EXTERNAL_INTERRUPTS);
  
void setup() {
  Serial.begin(115200);
}

void loop() {
  currMicro = micros();
  if (currMicro - prevMicro > PING_RATE) {
    jsn.JSN_Trig(1);
    distance[0] = jsn.JSN_GetDistance(1);
    Serial.print(distance[0]);
  }
}
