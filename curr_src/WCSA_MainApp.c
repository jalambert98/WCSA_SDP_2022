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
// ======= PIN FUNCTIONS ======= //
#define LIDAR_TX_PIN        C4
#define LIDAR_RX_PIN        B5

#define MOTOR_PIN           C1

#define SPEAKER_TONE_PIN    A4
#define SPEAKER_SDWN_PIN    B7
#define SPEAKER_GNSEL_PIN   C6

#define PMIC_STAT1_PIN      B4
#define PMIC_STAT2_PIN      C2

#define BAT_ADC_PIN         A5

#define PWR_BTN_GPIO_PIN    A2

// ======= THRESHOLD VALS ======= //
#define WARNING_DISTANCE    1000
#define LOW_BAT_THRESHOLD   800     // 800 on ADC --> ~= 1.6V

#define ADC_READ_RATE       25      // 25ms --> 40Hz
#define LIDAR_READ_RATE     2       // 10ms --> 100Hz
#define PWR_BTN_POLL_RATE


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

    uint16_t distance = 2500;
    uint16_t motorDC = 0;
    uint32_t currMilli, prevMilli;
    uint8_t i = 0;
    currMilli = FRT_GetMillis();
    prevMilli = currMilli;

    // Read ADC every 25ms (@40Hz) for 500ms --> 20 readings (16val buffer)
    do {
        RESET_WDT();
        currMilli = FRT_GetMillis();

        if ((currMilli - prevMilli) >= ADC_READ_RATE) {
            ADC_StartConversion();
            prevMilli = currMilli;
            i++;
        }
    } while (i < 20);

    // Force shutdown if filtered reading < 1.6V
    if (ADCBuffer_GetFilteredReading() < LOW_BAT_THRESHOLD) {
        SpeakerTone_ShutdownChirp(); // play shutdown chirp
        PowerButton_ForceShutdown(); // drives RA2 LOW & blocks CPU
    }
    /* Otherwise, battery is not critically low!
     * So, finish startup routine. */

    // --- Initialize Remaining Libraries --- //
    PowerButton_Init(); // soft-switching power button routines
    MotorControl_Init(); // TMR2, PWM5, MotorControl
    Lidar_Sensor_Init(); // eusart(already initialized), Lidar_Sensor
    Lidar_Sensor_Trig();

    // ========= REMAINING SETUP ========= //
    i = 0;
    distance = 0;
    currMilli = FRT_GetMillis();
    prevMilli = currMilli;

    while (1) {
        RESET_WDT();
        currMilli = FRT_GetMillis();

        // ------- 100Hz Block ------- //
        if ((currMilli - prevMilli) >= LIDAR_READ_RATE) {
            distance = Lidar_Sensor_GetDistance(); //get current Lidar reading
            Lidar_Sensor_Trig(); //TRIG new Lidar reading

            // If measured distance < 1m
            if (distance < WARNING_DISTANCE) {
                if (distance != 0) {
                    motorDC = 500;
                    printf("\nWARNING: %umm\n", distance);
                } else {
                    motorDC = 0;
                }
            } else {
                motorDC = 0;
            }

            MotorControl_SetIntensity(motorDC);
            if (motorDC == 0) {
                MotorControl_Off();
            } else {
                MotorControl_On();
            }
            
            // ------- 5Hz Block ------- //
            if (i == 20) {
                ADC_StartConversion();

                if (PowerButton_WasBtnPressed()) {
                    SpeakerTone_ShutdownChirp();
                    PowerButton_ForceShutdown();
                } 
                else if (ADCBuffer_GetFilteredReading() < LOW_BAT_THRESHOLD) {
                    SpeakerTone_ShutdownChirp();
                    PowerButton_ForceShutdown();
                }
                i = 0;
            } else {
                i++;
            }

            prevMilli = currMilli;
        }
    }

    while (1);
    return 0;
}