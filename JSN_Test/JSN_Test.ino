/* 
 * File:            JSN_Test.ino
 * Author:          Jack Lambert <joalambe@ucsc.edu>
 * Project:         White Cane Sensor Attachment
 * Course:          UCSC ECE129 - SDP '21
 *
 * Created:         January 15, 2022, 6:30 PM
 * Last Modified:   January 15, 2022, 12:25 AM
 */

#include "JSN_Sensor.h"

#define PING_RATE       500000    // 500,000us = 0.5s
#define BAUDRATE        115200
#define NUM_SENSORS     3

#define TRIG1           0x05
#define TRIG2           0x06
#define TRIG3           0x08
#define ECHO1           0x02
#define ECHO2           0x03
#define ECHO3           0x07

JSN_Sensor *sens[3];
uint8_t i;
  
void setup() {
  sens[0] = new JSN_Sensor(TRIG1, ECHO1);
  sens[1] = new JSN_Sensor(TRIG2, ECHO2);
  sens[2] = new JSN_Sensor(TRIG3, ECHO3);
  
  // Begin serial comms over UART
  Serial.begin(BAUDRATE);

  // Initialize interrupt hardware associated with JSN sensors
  JSN_Sensor::Init(EXTERNAL_INTERRUPTS);
}

void loop() {
  for(i=0; i<3; i++) {
    sens[i]->Trig();
    delay(250);
    Serial.print("Distance");
    Serial.print(i+1);
    Serial.print(" = ");
    Serial.print(sens[i]->GetDistance());
    Serial.print("mm\n");
    delay(250);
  }
}
