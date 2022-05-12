/*
 * File:   WCSA_MainApp.c
 * Author: Jack Lambert - <joalambe@ucsc.edu>
 *
 * Created on May 10, 2022, 6:19 PM
 */
//------------------------------------------------------------------------------

#include "WCSA_system.h"
#include "Lidar_Sensor.h"

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================



//==============================================================================
//---------------------------- MAIN APPLICATION --------------------------------
//==============================================================================

int main(void) {
    // ====== INITIALIZE LIBRARIES ====== //
    PIC16_Init();           // PMD, Osc, PinManager, WDT, & eusart
    FRT_Init();             // global milli/micro-second counters
    BatteryMonitor_Init();  // ADC, ADCBuffer, BatteryMonitor
    SpeakerTone_Init();     // TMR3, CCP4(OC), SpeakerTone
    
    /* 
     * NOTE:    Maybe, measure vBat here & force shutdown if system detects
     *          critical battery before initializing remaining libraries?
     */
    PowerButton_Init();     // soft-switching power button routines
    MotorControl_Init();    // TMR2, PWM5, MotorControl
    Lidar_Sensor_Init();    // eusart(already initialized), Lidar_Sensor
    
    
    // ========= REMAINING SETUP ========= //
    /*
     * TODO:    - Instantiate global variables
     *          - Run startup routine
     *          - Gather initial required data
     */
    SpeakerTone_StartupChirp();
    
    uint32_t currMilli, prevMilli;
    currMilli = FRT_GetMillis();
    prevMilli = currMilli;
     
    uint8_t upOrDown = 1;
    
    // ========== PRIMARY LOOP =========== //
    /*
     * TODO:    - Describe con-ops in main loop
     *          - Program this bish
     */
    while(1) {
        RESET_WDT();
        currMilli = FRT_GetMillis();
        
        if((currMilli - prevMilli) >= 2000) {
            if(upOrDown == 1) {
                SpeakerTone_StartupChirp();
                upOrDown = 0;
            }
            else if(upOrDown == 0) {
                SpeakerTone_ShutdownChirp();
                upOrDown = 1;
            }
            
            prevMilli = currMilli;
        }
        
    }
    
    while(1);
    return 0;
}