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

uint8_t Lidar_Sensor_CalcChecksum(void) {
    return 0;
}

//------------------------------------------------------------------------------

void Lidar_Sensor_RXSM(uint8_t ch) {
    return;
}

//------------------------------------------------------------------------------
