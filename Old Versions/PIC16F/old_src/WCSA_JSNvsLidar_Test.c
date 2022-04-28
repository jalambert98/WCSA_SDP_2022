/*
 * File:   WCSA_JSNvsLidar_Test.c
 * Author: Jack Lambert <joalambe@ucsc.edu>
 *
 * Created on March 12, 2022, 12:27 PM
 */
//------------------------------------------------------------------------------

#include <xc.h>
#include "PIC16Xpress_DevBoard.h"
#include "JSN_Sensor.h"
#include "Lidar_Sensor.h"
#include "FRT.h"

#define JSN_VS_LIDAR_TEST

//------------------------------------------------------------------------------

#ifdef JSN_VS_LIDAR_TEST

#define JSN_SAMPLE_RATE         50      // 50ms --> 20Hz
#define LIDAR_SAMPLE_RATE       10      // 10ms --> 100Hz

int main(void) {
    // Initialize required libraries
    PIC16_Init();
    JSN_Sensor_Init(SINGLE_SENS_CONFIG);
    Lidar_Sensor_Init();
    
    /*
     * In order to preserve the EUSART TX pin for printf / logging
     * messages (viewed on AD2), we will set the Lidar sensor for
     * automatic readings at a fixed rate [100Hz]. 
     * (No trigger messages need to be sent over TX Pin)
     */
    Lidar_Sensor_SetFrameRate(100);
    Lidar_Sensor_SetOutput_mm();
    
    // Setup FRT references
    unsigned long currMilliJSN = FRT_GetMillis();
    unsigned long prevMilliJSN = currMilliJSN;
    unsigned long currMilliLidar = currMilliJSN;
    unsigned long prevMilliLidar = prevMilliJSN;
    
    // Send initial TRIG JSN Sens1
    JSN_Sensor_Trig(1);
    
    // Primary loop prints Lidar & JSN Sensor readings over EUSART
    while(1) {
        currMilliJSN = FRT_GetMillis();
        currMilliLidar = currMilliJSN;
        
        // Report Lidar reading every 10ms [@100Hz]
        if ((currMilliLidar - prevMilliLidar) >= LIDAR_SAMPLE_RATE) {
            printf("L    %u\n", Lidar_Sensor_GetDistance());
            prevMilliLidar = currMilliLidar; 
        }
        
        // Report JSN reading every 50ms [@20Hz]
        if ((currMilliJSN - prevMilliJSN) >= JSN_SAMPLE_RATE) {
            printf("J    %u\n", JSN_Sensor_GetDistance(1));
            JSN_Sensor_Trig(1);     // send new TRIG pulse to JSN
            prevMilliJSN = currMilliJSN;
        }
    }
    
    while(1);
    return 0;
}

#endif
