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

#define TRIG1           0x07
#define ECHO1           0x04

JSN_Sensor *sens;
uint8_t i;
unsigned int dist;
  
void setup() {
  sens = new JSN_Sensor(TRIG1, ECHO1);
  
  // Begin serial comms over UART
  Serial.begin(BAUDRATE);

  // Initialize interrupt hardware associated with JSN sensors
  JSN_Sensor::Init(INPUT_CAPTURE);
}

void loop() {
  sens->Trig();
  delay(10);
  dist = sens->GetDistance();
  Serial.print("Distance");
  Serial.print(i+1);
  Serial.print(" = ");
  Serial.print(dist);
  Serial.print("mm\n");
  delay(10);
}
