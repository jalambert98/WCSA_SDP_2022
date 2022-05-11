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
     
    
    // ========== PRIMARY LOOP =========== //
    /*
     * TODO:    - Describe con-ops in main loop
     *          - Program this bish
     */
    while(1) {
        
    }
    
    while(1);
    return 0;
}
