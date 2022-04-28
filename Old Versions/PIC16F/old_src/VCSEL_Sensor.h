/* 
 * File:    VCSEL_Sensor.h
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on March 4th, 2022 at 8:25PM
 */
//------------------------------------------------------------------------------

#include "PIC16Xpress_DevBoard.h"
#include "i2c1_master.h"

#ifndef VCSEL_SENSOR_H
#define	VCSEL_SENSOR_H

#define VCSEL_I2C_ADDRESS       0x52
#define VCSEL_I2C_WRITE         0x52
#define VCSEL_I2C_READ          0x53


//------------------------------------------------------------------------------

typedef struct {
    uint8_t msg[9];
    
} VCSEL_MsgRX_t;



#endif	/* VCSEL_SENSOR_H */

