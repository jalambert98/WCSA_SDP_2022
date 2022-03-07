/* 
 * File:    Lidar_Sensor.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on March 4th, 2022 at 8:25PM
 */
//------------------------------------------------------------------------------

#include "PIC16Xpress_DevBoard.h"
#include "eusart.h"

#ifndef LIDAR_SENSOR_H
#define	LIDAR_SENSOR_H

#define LIDAR_TX_HEAD           0x5A
#define LIDAR_RX_FRAMEHEADER    0x59

//------------------------------------------------------------------------------

typedef struct {
    uint8_t msg[9];
    uint16_t distance;
    uint16_t strength;
    uint16_t temp;
    uint8_t checksum;
} Lidar_MsgRX_t;

//------------------------------------------------------------------------------

uint8_t Lidar_Checksum(void);

#endif	/* LIDAR_SENSOR_H */

