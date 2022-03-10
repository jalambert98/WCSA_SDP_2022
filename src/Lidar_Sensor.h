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
    uint8_t data[9];
    uint16_t distance;
    uint16_t strength;
    uint16_t temp;
    uint8_t checksum;
} Lidar_MsgRX_t;

//------------------------------------------------------------------------------

typedef enum {
    IDLE,
    W4_HEADER_2,
    W4_DIST_L,
    W4_DIST_H,
    W4_STRENGTH_L,
    W4_STRENGTH_H,
    W4_TEMP_L,
    W4_TEMP_H,
    W4_CHECKSUM       
} Lidar_StateRX_t;

//------------------------------------------------------------------------------

uint8_t Lidar_Sensor_CalcChecksum(void);

//------------------------------------------------------------------------------

void Lidar_Sensor_RXSM(uint8_t ch);

//------------------------------------------------------------------------------

#endif	/* LIDAR_SENSOR_H */

