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

static uint16_t distance;


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
    PIC16_Init(); // PMD, Osc, PinManager, & WDT
    FRT_Init(); // global milli/micro-second counters
    BatteryMonitor_Init(); // ADC, ADCBuffer, BatteryMonitor
    SpeakerTone_Init(); // TMR3, CCP4(OC), SpeakerTone

    // --- Play Startup Chirp --- //
    SpeakerTone_StartupChirp();
    
    printf("// ======= WCSA_MainApp.c ======= //\n");
    printf("Last compiled on %s at %s\n\n", __DATE__, __TIME__);

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
    Lidar_Sensor_SetFrameRate(0);
    Lidar_Sensor_SetOutput_mm();
    Lidar_Sensor_Trig();

    // ========= REMAINING SETUP ========= //
    /*
     * TODO:    - Instantiate global variables
     *          - Gather initial required data
     */

    i = 0;
    distance = 0;

    // ========== PRIMARY LOOP =========== //
    /*
     * TODO:    - Describe con-ops in main loop
     *          - Program this bish
     */
    while (1) {
        RESET_WDT();
        currMilli = FRT_GetMillis();

        if ((currMilli - prevMilli) >= 100) {
            distance = Lidar_Sensor_GetDistance();
            printf("%dmm\n", distance);
            
            if (distance < 1000) {
                MotorControl_SetIntensity(900);
                MotorControl_On();
            }
            else {
                MotorControl_Off();
            }
            
            
            Lidar_Sensor_Trig();
            
            if (i == 20) {
                ADC_StartConversion();
                
                if (PowerButton_WasBtnPressed()) {
                    SpeakerTone_ShutdownChirp();
                    PowerButton_ForceShutdown();
                }
                else if (ADCBuffer_GetFilteredReading() < 800) {
                    SpeakerTone_ShutdownChirp();
                    PowerButton_ForceShutdown();
                } 
                i = 0;
            }
            else {i++;}
            
            prevMilli = currMilli;
        }
    }

    while (1);
    return 0;
}