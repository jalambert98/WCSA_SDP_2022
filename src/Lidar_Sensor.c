/* 
 * File:    Lidar_Sensor.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on March 4th, 2022 at 8:25PM
 */
//------------------------------------------------------------------------------

#include "Lidar_Sensor.h"
#include "FRT.h"
#include "eusart.h"
#include "PIC16Xpress_DevBoard.h"

#define LIDAR_SENSOR_TEST


//------------------------------------------------------------------------------

static Lidar_MsgRX_t currMsg;
static Lidar_StateRX_t currState;
static uint8_t msgIndex;


//------------------------------------------------------------------------------

void Lidar_Sensor_Init(void) {
    // Set RX State Machine to IDLE state
    currState = IDLE;

    // Initialize all MsgRX variables to zero
    uint8_t i;
    for (i = 0; i < LIDAR_RX_MSG_LEN; i++) {
        currMsg.data[i] = 0;
    }
    currMsg.distance = 0;
    currMsg.strength = 0;
    currMsg.temp = 0;
    currMsg.checksum = 0;
    msgIndex = 0;
}

//------------------------------------------------------------------------------

void Lidar_Sensor_UpdateChecksum(void) {
    uint8_t i;
    currMsg.checksum = 0;

    for (i = 0; i < (LIDAR_RX_MSG_LEN - 1); i++) {
        currMsg.checksum += currMsg.data[i];
    }

    return;
}

//------------------------------------------------------------------------------

void Lidar_Sensor_RXSM(uint8_t ch) {
    switch (currState) {
        case IDLE: // index[0]
            if (ch == LIDAR_RX_FRAMEHEADER) {
                currMsg.data[msgIndex] = ch;
                currState = W4_HEADER_2;
                msgIndex++; // --> [1]
            }
            // otherwise, do nothing (remain in IDLE)
            break;

        case W4_HEADER_2: // index[1]
            if (ch == LIDAR_RX_FRAMEHEADER) {
                currMsg.data[msgIndex] = ch;
                currState = W4_DIST_L;
                msgIndex++; // --> [2]
            } else {
                // Reset RX State Machine if incorrect header byte
                currState = IDLE;
                msgIndex = 0;
            }
            break;

        case W4_DIST_L: // index[2]
            currMsg.data[msgIndex] = ch;
            currState = W4_DIST_H;
            msgIndex++; // --> [3]
            break;

        case W4_DIST_H: // index[3]
            currMsg.data[msgIndex] = ch;
            currState = W4_STRENGTH_L;
            msgIndex++; // --> [4]
            break;

        case W4_STRENGTH_L: // index[4]
            currMsg.data[msgIndex] = ch;
            currState = W4_STRENGTH_H;
            msgIndex++; // --> [5]
            break;

        case W4_STRENGTH_H: // index[5]
            currMsg.data[msgIndex] = ch;
            currState = W4_TEMP_L;
            msgIndex++; // --> [6]
            break;

        case W4_TEMP_L: // index[6]
            currMsg.data[msgIndex] = ch;
            currState = W4_TEMP_H;
            msgIndex++; // --> [7]
            break;

        case W4_TEMP_H: // index[7]
            currMsg.data[msgIndex] = ch;
            currState = W4_CHECKSUM;
            msgIndex++; // --> [8]
            break;

        case W4_CHECKSUM: // index[8]
            currMsg.data[msgIndex] = ch;
            currState = IDLE;
            msgIndex = 0;
            Lidar_Sensor_UpdateChecksum();

            if (ch == currMsg.checksum) {
                // Received message is valid, so update struct variables
                currMsg.distance = (uint16_t) (currMsg.data[INDEX_DIST_H] << BYTE_SIZE)
                        + currMsg.data[INDEX_DIST_L];

                currMsg.strength = (uint16_t) (currMsg.data[INDEX_STRENGTH_H] << BYTE_SIZE)
                        + currMsg.data[INDEX_STRENGTH_L];

                currMsg.temp = ((uint16_t) (currMsg.data[INDEX_TEMP_H] << BYTE_SIZE)
                        + currMsg.data[INDEX_TEMP_L]);
                currMsg.temp = (currMsg.temp / 8) - 256;

                // should trigger some kind of "data ready" event here
            }
            break;
    }
    return;
}

//------------------------------------------------------------------------------

Lidar_MsgRX_t* Lidar_Sensor_GetCurrMsg(void) {
    return &currMsg;
}

//------------------------------------------------------------------------------

void Lidar_Sensor_SetFrameRate(uint16_t frameRate) {
    // Separate 16-bit FrameRate into high & low bytes
    uint8_t frameRateL = (uint8_t) (frameRate & 0x00FF);
    uint8_t frameRateH = (uint8_t) ((frameRate & 0xFF00) >> BYTE_SIZE);

    // Assemble message to send to Lidar Sensor
    uint8_t msg[FRAMERATE_MSG_LEN];
    msg[0] = LIDAR_TX_HEAD;
    msg[1] = FRAMERATE_MSG_LEN;
    msg[2] = FRAMERATE_MSG_ID;
    msg[3] = frameRateL;
    msg[4] = frameRateH;

    // Calculate checksum (last byte of msg)
    uint8_t cksum = 0;
    uint8_t i;
    for (i = 0; i < (FRAMERATE_MSG_LEN - 1); i++) {
        cksum += msg[i];
    }
    msg[5] = cksum;
    
    // Send framerate message to sensor
    for (i = 0; i< FRAMERATE_MSG_LEN; i++) {
        EUSART_Write(msg[i]);
    }
    
    // Send SAVE_SETTINGS message to sensor
    Lidar_Sensor_SaveSettings();
    return;
}

//------------------------------------------------------------------------------

void Lidar_Sensor_Trig(void) {
    // Assemble message
    uint8_t msg[TRIG_MSG_LEN] = {LIDAR_TX_HEAD, 
                                 TRIG_MSG_LEN, 
                                 TRIG_MSG_ID, 
                                 TRIG_MSG_CKSUM};
    // Send message
    uint8_t i;
    for (i = 0; i < TRIG_MSG_LEN; i++) {
        EUSART_Write(msg[i]);
    }
}

//------------------------------------------------------------------------------

void Lidar_Sensor_SaveSettings(void) {
    // Assemble message
    uint8_t msg[SAVESET_MSG_LEN] = {LIDAR_TX_HEAD, 
                                    SAVESET_MSG_LEN, 
                                    SAVESET_MSG_ID, 
                                    SAVESET_MSG_CKSUM};
    // Send message
    uint8_t i;
    for (i = 0; i < SAVESET_MSG_LEN; i++) {
        EUSART_Write(msg[i]);
    }
}

//------------------------------------------------------------------------------

#ifdef LIDAR_SENSOR_TEST

#define SAMPLE_RATE         10  // 10ms --> 100Hz

int main(void) {
    PIC16_Init();
    Lidar_Sensor_Init();
    
    printf("//=== Lidar_Sensor.c ===//\n");
    printf("LIDAR_SENSOR_TEST - Last compiled on %s at %s\n", __DATE__, __TIME__);

    Lidar_Sensor_SetFrameRate(100);
    
    unsigned long currMilli = FRT_GetMillis();
    unsigned long prevMilli = currMilli;

    while (1) {
        currMilli = FRT_GetMillis();
        if ((currMilli - prevMilli) >= SAMPLE_RATE) {
            
            printf("Dist = %u[cm]\n", Lidar_Sensor_GetCurrMsg()->distance);
            printf("Strength = %u\n", Lidar_Sensor_GetCurrMsg()->strength);
            printf("Temp = %u[degC]\n\n", Lidar_Sensor_GetCurrMsg()->temp);
            
            //printf("%u\n", Lidar_Sensor_GetCurrMsg()->distance);
        }
    }

    while (1);
    return 0;
}

#endif

// #define LIDAR_TX_UPDATE

#ifdef LIDAR_TX_UPDATE

#define SAMPLE_RATE         1000

int main(void) {
    PIC16_Init();
    Lidar_Sensor_Init();
    Lidar_Sensor_SetFrameRate(0);
    
    unsigned long currMilli = FRT_GetMillis();
    unsigned long prevMilli = currMilli;
    
    while(1) {
        currMilli = FRT_GetMillis();
        
        if((currMilli - prevMilli) >= SAMPLE_RATE) {
            Lidar_Sensor_Trig();
            prevMilli = currMilli;
        }
        
    }
    
    while(1);
    return 0;
}

#endif