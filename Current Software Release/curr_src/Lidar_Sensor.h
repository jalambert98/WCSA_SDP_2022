/* 
 * File:    Lidar_Sensor.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on March 4th, 2022 at 8:25PM
 */
//------------------------------------------------------------------------------

#include "pin_manager.h"
#include "eusart.h"

#ifndef LIDAR_SENSOR_H
#define	LIDAR_SENSOR_H


#define LIDAR_TX_HEAD           0x5A
#define LIDAR_RX_FRAMEHEADER    0x59
#define LIDAR_RX_MSG_LEN        9

#define FRAMERATE_MSG_LEN       0x06
#define FRAMERATE_MSG_ID        0x03

#define TRIG_MSG_LEN            0x04
#define TRIG_MSG_ID             0x04
#define TRIG_MSG_CKSUM          0x62

#define SETOUT_MSG_LEN          0x05
#define SETOUT_MSG_ID           0x05
#define SETOUT_CM_DATA          0x01
#define SETOUT_MM_DATA          0x06
#define SETOUT_CM_CKSUM         0x65
#define SETOUT_MM_CKSUM         0x6A

#define SAVESET_MSG_LEN         0x04
#define SAVESET_MSG_ID          0x11
#define SAVESET_MSG_CKSUM       0x6F

#define INDEX_DIST_L            2
#define INDEX_DIST_H            3
#define INDEX_STRENGTH_L        4
#define INDEX_STRENGTH_H        5
#define INDEX_TEMP_L            6
#define INDEX_TEMP_H            7

#define BYTE_SIZE               8

//------------------------------------------------------------------------------

typedef struct {
    uint8_t data[LIDAR_RX_MSG_LEN];
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

void Lidar_Sensor_Init(void);

//------------------------------------------------------------------------------

void Lidar_Sensor_UpdateChecksum(void);

//------------------------------------------------------------------------------

void Lidar_Sensor_RXSM(uint8_t ch);

//------------------------------------------------------------------------------

uint16_t Lidar_Sensor_GetDistance(void);

//------------------------------------------------------------------------------

uint16_t Lidar_Sensor_GetStrength(void);

//------------------------------------------------------------------------------

uint16_t Lidar_Sensor_GetTemp(void);

//------------------------------------------------------------------------------

void Lidar_Sensor_SetFrameRate(uint16_t frameRate);

//------------------------------------------------------------------------------

void Lidar_Sensor_Trig(void);

//------------------------------------------------------------------------------

void Lidar_Sensor_SetOutput_cm(void);

//------------------------------------------------------------------------------

void Lidar_Sensor_SetOutput_mm(void);

//------------------------------------------------------------------------------

void Lidar_Sensor_SaveSettings(void);

//------------------------------------------------------------------------------

#endif	/* LIDAR_SENSOR_H */

