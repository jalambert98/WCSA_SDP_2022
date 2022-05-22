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
#define WARNING_DISTANCE        1000

#define BAT_EMPTY_THRESHOLD     800     // 800 on ADC --> ~= 1.6V
#define BAT_25_THRESHOLD        850
#define BAT_50_THRESHOLD        900
#define BAT_75_THRESHOLD        950
#define BAT_FULL_THRESHOLD      1000

#define LOW_BAT_WARNING_RATE    (uint32_t)(300000)  //[300,000ms --> 5min]

#define ADC_READ_RATE           25      // 25ms --> 40Hz
#define LIDAR_READ_RATE         10      // 10ms --> 100Hz
#define LOOP_COUNTER_THRESHOLD  20       

//------------------------------------------------------------------------------

batLvl_t GetBatState(uint16_t batLvl);
batLvl_t GetBatState(uint16_t batLvl) {
    if (batLvl > BAT_FULL_THRESHOLD)
        return BAT_FULL;
    else if (batLvl > BAT_75_THRESHOLD)
        return BAT_75;
    else if (batLvl > BAT_50_THRESHOLD)
        return BAT_50;
    else if (batLvl > BAT_25_THRESHOLD)
        return BAT_25;
    else
        return BAT_EMPTY;
}

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
    PIC16_Init();               // PMD, Osc, PinManager, & WDT
    FRT_Init();                 // global milli/micro-second counters
    BatteryMonitor_Init();      // ADC, ADCBuffer, BatteryMonitor
    SpeakerTone_Init();         // TMR3, CCP4(OC), SpeakerTone

    // --- Function variables --- //
    uint16_t distance = 2500;           // initialize to safe distance
    uint16_t motorDC = 0;               // initialize motor OFF
    uint16_t batLvl = 1000;             // initialize batLvl near full charge
    batLvl_t batStateCurr = BAT_FULL;   // initialize batState to FULL
    batLvl_t batStatePrev = BAT_FULL;
    uint32_t currMilli, prevMilli;      // global counter variables
    uint32_t prevWarningMilli;          // time of last low battery warning
    uint8_t i = 0;                      // loop counter / iterator
    
    
    // ======= STARTUP ROUTINE ======= //
    // --- Play Startup Chirp --- //
    SpeakerTone_StartupChirp();

    // --- Debug print statement via UART pin --- //
    printf("// ======= WCSA_MainApp.c ======= //\n");
    printf("Last compiled on %s at %s\n\n", __DATE__, __TIME__);

    // --- Check battery level --- //
    ADC_StartConversion();  // send initial ADC conversion request

    // update timer variables
    currMilli = FRT_GetMillis();
    prevMilli = currMilli;
    prevWarningMilli = currMilli;

    // Read ADC every 10ms (@100Hz) for 750ms --> 75 readings (64val buffer)
    do {
        RESET_WDT();
        currMilli = FRT_GetMillis();

        if ((currMilli - prevMilli) >= ADC_READ_RATE) {
            ADC_StartConversion();  // request new ADC conversion every 25ms
            prevMilli = currMilli;
            i++;
        }
    } while (i < 75);   // ...until 75 readings have been taken

    // Force shutdown if filtered reading < 1.6V
    batLvl = ADCBuffer_GetFilteredReading();
    batStatePrev = batStateCurr;
    batStateCurr = GetBatState(batLvl);
    
    if (batStateCurr == BAT_EMPTY) {
        SpeakerTone_ShutdownChirp();    // play shutdown chirp
        PowerButton_ForceShutdown();    // drives RA2 LOW & blocks CPU
    }
    /* Otherwise, battery is not critically low!
     * So, finish startup routine. */

    // --- Initialize Remaining Libraries --- //
    PowerButton_Init();     // soft-switching power button routines
    MotorControl_Init();    // TMR2, PWM5, MotorControl
    Lidar_Sensor_Init();    // eusart(already initialized), Lidar_Sensor
    Lidar_Sensor_Trig();    // send initial trig message, so reading is ready

    
    // ========= REMAINING SETUP ========= //
    i = 0;
    distance = 0;
    currMilli = FRT_GetMillis();
    prevMilli = currMilli;

    // ======= PRIMARY LOOP ======= //
    while (1) {
        RESET_WDT();
        currMilli = FRT_GetMillis();

        // ======= 100Hz Block ======= //
        // --- LiDAR Reading Update --- //
        if ((currMilli - prevMilli) >= LIDAR_READ_RATE) {
            distance = Lidar_Sensor_GetDistance();  // get last Lidar reading
            Lidar_Sensor_Trig();                    // TRIG new Lidar reading

            // --- Motor Intensity Update based on distance --- //
            // If measured distance < 1m...
            // ... calculate motor intensity based on measured distance
            if (distance < WARNING_DISTANCE) {
                motorDC = (WARNING_DISTANCE - distance);
            } 
            else {  // set vibration intensity = 0 if beyond warning distance
                motorDC = 0;
            }

            // Update motor intensity to new value
            MotorControl_SetIntensity(motorDC); 
            
            if (motorDC == 0) { // if intensity == 0, disable motor peripherals
                MotorControl_Off();
            }
            else {              // if intensity != 0, enable motor peripherals
                MotorControl_On();
            }
            
            // ======= 5Hz Block ======= //
            // Every 20 LiDAR readings... (100Hz / 20 = 5Hz)
            if (i == LOOP_COUNTER_THRESHOLD) {
                batLvl = ADCBuffer_GetFilteredReading(); // get current batLvl
                batStatePrev = batStateCurr;         // update batState
                batStateCurr = GetBatState(batLvl);  // determine new batState
                ADC_StartConversion();  // Update batLvl with new ADC reading 

                
                // --- Check for SHUTDOWN conditions --- //
                // If user has pressed power button while system ON...
                if (PowerButton_WasBtnPressed()) {
                    SpeakerTone_ShutdownChirp();    // play shutdown chirp
                    PowerButton_ForceShutdown();    // force shutdown
                } 
                // If battery is below BAT_EMPTY_THRESHOLD (3.2V)...
                else if (batStateCurr == BAT_EMPTY) {
                    SpeakerTone_ShutdownChirp();    // play shutdown chirp
                    PowerButton_ForceShutdown();    // force shutdown
                }
                
                // --- Check for WARNING conditions --- //
                // If battery is below BAT_25_THRESHOLD (x.yV)...
                else if (batStateCurr == BAT_25) {
                    // If battery just changed to BAT_25 state...
                    if (batStateCurr != batStatePrev) {
                        SpeakerTone_LowBatteryChirp();
                        prevWarningMilli = currMilli;
                    }
                    
                    // Play lowBat warning chirp if over 10min since last played
                    if ((currMilli - prevWarningMilli) > LOW_BAT_WARNING_RATE) {
                        SpeakerTone_LowBatteryChirp();
                        prevWarningMilli = currMilli;
                    }
                }
                // If battery is below BAT_50_THRESHOLD (x.yV)...
                else if (batStateCurr == BAT_50) {
                    // If battery just changed to BAT_50 state...
                    if (batStateCurr != batStatePrev) {
                        SpeakerTone_ChargingChirp(BAT_50);  // play BAT_50 chirp
                    }
                }
                // If battery is below BAT_75_THRESHOLD (x.yV)...
                else if (batStateCurr == BAT_75) {
                    // If battery just changed to BAT_75 state...
                    if (batStateCurr != batStatePrev) {
                        SpeakerTone_ChargingChirp(BAT_75);  // play BAT_75 chirp
                    }
                }
                // If battery is below BAT_FULL_THRESHOLD (x.yV)...
                else if (batStateCurr == BAT_FULL) {
                    // If battery just changed to BAT_FULL state...
                    if (batStateCurr != batStatePrev) {
                        SpeakerTone_ChargingChirp(BAT_FULL); // play BAT_FULL chirp
                    }
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