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

/*
 * NOTE:    Current main() function demonstrates the two possible 
 *          'forced shutdown' conditions: (1) ADC reads vBat < 1.6V
 *                                        (2) PowerBtn pressed (GPIO falls LOW)
 */
int main(void) {
    // ====== INITIALIZE LIBRARIES ====== //
    // First, initialize libraries for startup chirp & battery level check
    PIC16_Init(); // PMD, Osc, PinManager, WDT, & 

    /* DEBUG LED */
    SET_C0() = OUTPUT;
    WRITE_C0() = HIGH;

    FRT_Init(); // global milli/micro-second counters
    BatteryMonitor_Init(); // ADC, ADCBuffer, BatteryMonitor
    SpeakerTone_Init(); // TMR3, CCP4(OC), SpeakerTone

    // --- Play Startup Chirp --- //
    SpeakerTone_StartupChirp();

    // --- Check battery level --- //
    ADC_StartConversion();

    uint32_t currMilli, prevMilli;
    uint8_t i = 0;
    currMilli = FRT_GetMillis();
    prevMilli = currMilli;

    // Read ADC every 50ms (@20Hz) for 1 second to fill ADCBuffer
    do {
        RESET_WDT();
        currMilli = FRT_GetMillis();

        if ((currMilli - prevMilli) >= 50) {
            ADC_StartConversion();
            prevMilli = currMilli;
            i++;
        }
    } while (i < 20);

    // Force shutdown if filtered reading < 1.6V
    if (ADCBuffer_GetFilteredReading() < 800) {
        SpeakerTone_ShutdownChirp(); // play shutdown chirp
        PowerButton_ForceShutdown(); // drives RA2 LOW & blocks CPU
    }
    /* Otherwise, battery is not critically low!
     * So, finish startup routine. */

    // --- Initialize Remaining Libraries --- //
    PowerButton_Init(); // soft-switching power button routines
    MotorControl_Init(); // TMR2, PWM5, MotorControl
    Lidar_Sensor_Init(); // eusart(already initialized), Lidar_Sensor


    // ========= REMAINING SETUP ========= //
    /*
     * TODO:    - Instantiate global variables
     *          - Gather initial required data
     */

    i = 0;

    // ========== PRIMARY LOOP =========== //
    /*
     * TODO:    - Describe con-ops in main loop
     *          - Program this bish
     */
    while (1) {
        RESET_WDT();
        currMilli = FRT_GetMillis();

        if ((currMilli - prevMilli) >= 200) {
            ADC_StartConversion(); // start new ADC reading

            if (i == 15) { // 200ms * 15 = 3sec
                // check gpioFlag
                if (PowerButton_WasBtnPressed()) {
                    SpeakerTone_ShutdownChirp();
                    PowerButton_ForceShutdown();
                }
                else if (ADCBuffer_GetFilteredReading() < 800) {
                    SpeakerTone_ShutdownChirp();
                    PowerButton_ForceShutdown();
                } 
                else {
                    // play startup chirp sound
                    SpeakerTone_StartupChirp();

                    i = 0;
                }  
            }  
            else { i++; }
            prevMilli = currMilli;
        }
    }

    while (1);
    return 0;
}