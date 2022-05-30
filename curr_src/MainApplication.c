/*
 * File:   WCSA_MainApp.c
 * Author: Jack Lambert - <joalambe@ucsc.edu>
 *
 * Created on May 10, 2022, 6:19 PM
 */
//------------------------------------------------------------------------------

#include "WCSA_system.h"


//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================
// ======= PIN FUNCTIONS + QUICK REFERENCE ======= //
/* 
 * All values [xy] correspond to PIC16F pin [Rxy]
 *  (e.g. MOTOR_PIN is pin RC1 on MCU)
 */ 
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


// ============== THRESHOLD VALUES ============== //
#define WARNING_DISTANCE        1000
#define MIN_VALID_DISTANCE      90

#define LOW_BAT_WARNING_RATE    (uint32_t)(300000)  // [300,000 ms --> 5 min]

#define ADC_READ_RATE           10      // 10ms --> 100Hz (startup)
#define LIDAR_READ_RATE         10      // 10ms --> 100Hz (main loop)

// check power conditions every 20 lidar readings
#define LOOP_COUNTER_THRESHOLD  20


//==============================================================================
//---------------------------- MAIN APPLICATION --------------------------------
//==============================================================================

int main(void) {
    
    // ====== INITIALIZE LIBRARIES ====== //
    // First, initialize libraries for startup chirp & battery level check
    PIC16_Init();               // PMD, Osc, PinManager, WDT, & eusart
    FRT_Init();                 // global milli/micro-second counters
    BatteryMonitor_Init();      // ADC, ADCBuffer, BatteryMonitor
    SpeakerTone_Init();         // TMR3, CCP4(OC), SpeakerTone

    // --- Function variables --- //
    uint16_t distance = 2500;           // initialize to safe distance
    uint16_t motorDC = 0;               // initialize motor OFF
    uint16_t batLvl = 1000;             // initialize batLvl near full charge
    
    batLvl_t batStateCurr = BAT_FULL;   // initialize batState to FULL
    batLvl_t batStatePrev = BAT_FULL;   // curr = prev = FULL
    
    pmicState_t chgStatCurr = NOT_CHARGING;     // initialize PMIC to IDLE
    pmicState_t chgStatPrev = NOT_CHARGING;     // curr = prev = IDLE
    
    uint32_t currMilli, prevMilli;      // global counter variables
    uint32_t prevWarningMilli;          // time of last low battery warning
    uint8_t i = 0;                      // outer loop counter / iterator
    
    
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
            ADC_StartConversion();  // request new ADC conversion every 10ms
            prevMilli = currMilli;
            i++;
        }
    } while (i < 75);   // ...until 75 readings have been taken

    // --- Force shutdown if filtered reading < 1.6V --- //
    batLvl = ADCBuffer_GetFilteredReading();
    batStateCurr = GetBatState(batLvl);
    batStatePrev = batStateCurr;
    
    if (batStateCurr == BAT_EMPTY) {
        SpeakerTone_ShutdownChirp();    // play shutdown chirp
        PowerButton_ForceShutdown();    // drives RA2 LOW & blocks CPU
    }
    /* Otherwise, battery is not critically low!
     * So, finish startup routine. */

    
    // ========= REMAINING SETUP ========= //
    // --- Initialize Remaining Libraries --- //
    PowerButton_Init();     // soft-switching power button routines
    MotorControl_Init();    // TMR2, PWM5, MotorControl
    Lidar_Sensor_Init();    // eusart(already initialized), Lidar_Sensor
    Lidar_Sensor_Trig();    // send initial trig message, so reading is ready
    
    // main function variable assignments
    i = 0;
    distance = 0;
    currMilli = FRT_GetMillis();
    prevMilli = currMilli;

    
    // ============ PRIMARY LOOP ============ //
    while (1) {
        // === "Constant-Update" Block === //
        RESET_WDT();                    // clear watchdog timer
        currMilli = FRT_GetMillis();    // update current millisecond counter

        // ========== 100Hz Block ========== //
        // --- Update current LiDAR Reading --- //
        if ((currMilli - prevMilli) >= LIDAR_READ_RATE) {
            distance = Lidar_Sensor_GetDistance();  // get last Lidar reading
            Lidar_Sensor_Trig();                    // TRIG new Lidar reading

            // --- First, verify that LiDAR distance is valid ---//
            if (distance < MIN_VALID_DISTANCE)
                motorDC = 0;    // motor off if invalid reading  
            else {
                // --- Motor Intensity Update based on distance --- //
                // If measured distance < WARNING_DISTANCE (1m)...
                // ... calculate motor intensity based on measured distance
                if (distance < WARNING_DISTANCE) {
                    motorDC = (uint16_t)((uint32_t)((WARNING_DISTANCE+MIN_VALID_DISTANCE-distance)*MAX_DC_PERMILLI)/WARNING_DISTANCE);
                } 
                else {  // set vibration intensity = 0 if beyond warning distance
                    motorDC = 0;
                }
            }

            // Update motor intensity to new value
            MotorControl_SetIntensity(motorDC); 
            
            if (motorDC == 0) { // if intensity == 0, disable motor peripherals
                MotorControl_Off();
            }
            else {              // if intensity != 0, enable motor peripherals
                MotorControl_On();
            }
            
            
            // ========== 5Hz Block ========== //
            // Every 20 LiDAR readings... (100Hz / 20 = 5Hz)
            if (i == LOOP_COUNTER_THRESHOLD) {
                // ----- UPDATE power variables ----- //
                batLvl = ADCBuffer_GetFilteredReading(); // get current batLvl
                batStatePrev = batStateCurr;         // update batStatePrev
                batStateCurr = GetBatState(batLvl);  // Curr from filtered val
                batLvl = ADC_GetCurrReading();  // reuse batLvl for raw reading
                ADC_StartConversion();  // Update batLvl with new ADC reading 
                chgStatPrev = chgStatCurr;
                chgStatCurr = PMIC_STATUS_MASK();
                
                
                // ----- Check for SHUTDOWN conditions ----- //
                // If user has pressed power button while system ON...
                if (PowerButton_WasBtnPressed()) {
                    SpeakerTone_ShutdownChirp();    // play shutdown chirp
                    PowerButton_ForceShutdown();    // force shutdown
                } 
                // If INSTANTANEOUS vBat reading EVER dips below ~3.0V...
                else if (batLvl < BAT_CRITICALLY_LOW) {
                    SpeakerTone_ShutdownChirp();    // play shutdown chirp
                    PowerButton_ForceShutdown();    // force shutdown
                }
                // If filtered vBat avg is below BAT_EMPTY_THRESHOLD (~3.2V)...
                else if (batStateCurr == BAT_EMPTY) {
                    SpeakerTone_ShutdownChirp();    // play shutdown chirp
                    PowerButton_ForceShutdown();    // force shutdown
                }
                
                
                // ----- Check for PMIC CHARGING conditions ----- //
                // If charging status has changed...
                if (chgStatCurr != chgStatPrev) {
                    switch (chgStatCurr) {
                        // if battery just finished charging...
                        case CHARGE_COMPLETE:
                            // Play "charge complete" chirp
                            SpeakerTone_ChargeCompleteChirp();
                            break;
                        // if charger was just plugged in...
                        case NOW_CHARGING:
                            SpeakerTone_NowChargingChirp(TRUE);
                            break;
                        // if charger was just removed...
                        case NOT_CHARGING:
                            SpeakerTone_NowChargingChirp(FALSE);
                            break;
                        default:    // otherwise
                            break;  // do nothing
                    }
                }
                
                
                // ----- Check for BAT STATE WARNING conditions ----- //
                // Only play one of these warnings every 5 min...
                if ((currMilli - prevWarningMilli) > LOW_BAT_WARNING_RATE) {
                    
                    // --- If battery is within BAT_25 range... ---//
                    if (batStateCurr == BAT_25) {
                        // Play lowBat warning chirp if over 5min since last played
                        SpeakerTone_LowBatteryChirp();
                        prevWarningMilli = currMilli;
                    }

                    // --- If batLvl state has recently changed... ---//
                    else if (batStateCurr != batStatePrev) {
                        // ...play corresponding batLvl chirp
                        switch (batStateCurr) {
                            case BAT_25:    // (< 25%) --> LowBatteryChirp 
                                SpeakerTone_LowBatteryChirp(); 
                                // update last warning time
                                prevWarningMilli = currMilli;
                                break;

                            case BAT_50:    // (< 50%) --> BAT_50 chirp 
                                if (batStatePrev != BAT_75)
                                    break;
                            case BAT_75:    // (< 75%) --> BAT_75 chirp
                                if (batStatePrev != BAT_FULL)
                                    break;
                                
                                // Play BatLvlChirp if batState drops
                                SpeakerTone_BatLvlChirp(batStateCurr);
                                prevWarningMilli = currMilli;   
                            default:
                                break;
                        }
                    }
                }
                
                // ----- Update Loop Counter & FR timer --- //
                // Reset loop counter every 200ms [@5Hz]
                i = 0;
            } 
            // Increment loop counter every 10ms [@100Hz]
            else { i++; }
            prevMilli = currMilli;  // update prevMilli every 10ms [@100Hz]
        }
    }

    while (1);
    return 0;
}

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
