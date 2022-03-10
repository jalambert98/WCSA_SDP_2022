/* 
 * File:    Lidar_Sensor.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on March 4th, 2022 at 8:25PM
 */
//------------------------------------------------------------------------------

#include "Lidar_Sensor.h"
#include "PIC16Xpress_DevBoard.h"


static Lidar_MsgRX_t msg;
static Lidar_StateRX_t state;

//------------------------------------------------------------------------------

void Lidar_Sensor_Init(void) {
    // Set RX State Machine to IDLE state
    state = IDLE;
    
    // Initialize all MsgRX variables to zero
    uint8_t i;
    for (i = 0; i < 9; i++) {
        msg.data[i] = 0;
    }
    msg.distance = 0;
    msg.strength = 0;
    msg.temp = 0;
    msg.checksum = 0;
}

//------------------------------------------------------------------------------

uint8_t Lidar_Sensor_CalcChecksum(void) {
    return 0;
}

//------------------------------------------------------------------------------

void Lidar_Sensor_RXSM(uint8_t ch) {
    return;
}

//------------------------------------------------------------------------------
