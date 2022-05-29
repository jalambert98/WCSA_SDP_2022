/* 
 * File:   MotorControl.c
 * Author: Jack
 *
 * Created on February 8, 2022, 12:25 AM
 */
//------------------------------------------------------------------------------

#include "MotorControl.h"

// [PWM5] output --> Pin[RC1]
//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

//#define MOTORCONTROL_TEST


//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

static uint16_t dutyCyclePerMilli;
static uint16_t dutyCycle10bit;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void MotorControl_Init(void) {  
    SET_C1() = OUTPUT;
    WRITE_C1() = LOW;
    
    // Initialize required libraries    
    TMR2_Initialize();
    PWM5_Initialize();
    
    // Initialize to 50% duty cycle (TMR/PWM disabled)
    dutyCyclePerMilli = HALF_DC_PERMILLI;
    dutyCycle10bit = HALF_DC_10BIT; 
    MotorControl_Off();
    return;
}

//------------------------------------------------------------------------------

uint8_t MotorControl_SetIntensity(uint16_t dutyCycle) {
    // As long as dutyCycle is within [0, 1000]...
    if (dutyCycle <= MAX_DC_PERMILLI) {
        
        // Store user-assigned dutyCycle [%]
        dutyCyclePerMilli = dutyCycle;
        
        // ...and calculate associated ratio of 10-bit range
        dutyCycle10bit = (uint16_t)(((uint32_t)dutyCycle * MAX_DC_10BIT) / 
                                                            MAX_DC_PERMILLI);
        // Then update PWMDC register with calculated value
        PWM5_LoadDutyValue(dutyCycle10bit);
        return SUCCESS;
    }
    else
        return ERROR;
}

//------------------------------------------------------------------------------

void TMR2_Initialize(void)
{
    // PR2 249; 
    PR2 = 0xF9;

    // TMR2 0; 
    TMR2 = 0x00;

    // Clearing IF flag.
    PIR1bits.TMR2IF = 0;

    // T2CKPS 1:4; T2OUTPS 1:8; TMR2ON on; 
    T2CON = 0x3D;
}

//------------------------------------------------------------------------------

void TMR2_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 1;
}

//------------------------------------------------------------------------------

void TMR2_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 0;
}

//------------------------------------------------------------------------------

void TMR2_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer2 register
    TMR2 = timerVal;
}

//------------------------------------------------------------------------------

void PWM5_Initialize(void) {
    // PPS module to connect PWM5 output to pin RC1
    RC1PPS = 0x02; //RC1->PWM5:PWM5; 
    
    // PWM5POL active_hi; PWM5EN enabled; 
    PWM5CON = 0x80;

    // PWM5DCH 0; 
    PWM5DCH = 0x00;

    // PWM5DCL 0; 
    PWM5DCL = 0x00;

    // Select timer
    PWMTMRSbits.P5TSEL = 1;
}

//------------------------------------------------------------------------------

void PWM5_LoadDutyValue(uint16_t dutyValue) {
    // Writing to 8 MSBs of PWM duty cycle in PWMDCH register
    PWM5DCH = (dutyValue & 0x03FC) >> 2;

    // Writing to 2 LSBs of PWM duty cycle in PWMDCL register
    PWM5DCL = (dutyValue & 0x0003) << 6;
}

//------------------------------------------------------------------------------

void MotorControl_On(void) {
    // Enable TMR/PWM
    TMR2_StartTimer();
    PWM5CONbits.PWM5EN = 1;
    return;
}

//------------------------------------------------------------------------------

void MotorControl_Off(void) {
    // Disable & reset TMR/PWM
    TMR2_StopTimer();
    TMR2_WriteTimer(0x00);  // clear TMR2 ticks after stopping motor pulse
    PWM5CONbits.PWM5EN = 0;
    WRITE_C1() = LOW;
    return;
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

/* ---------- TEST HARNESS FOR MOTOR CONTROL SUBSYSTEM ---------- */
#ifdef MOTORCONTROL_TEST

#include "WCSA_system.h"
#include "FRT.h"

//#define OG
#define NEW


#ifdef OG

// ======= DEFINES ======= //
#define DC_UPDATE_RATE      50000   // update duty cycle every 50ms (20Hz)


// ======= MAIN() ======= //
int main(void) {
    // Init required libraries
    PIC16_Init();
    FRT_Init();
    MotorControl_Init();    // motorControl pin[RB6]
    
    printf("//=== MotorControl.c ===//\n");
    printf("MOTORCONTROL_TEST - Last compiled on %s at %s\n", __DATE__, __TIME__);
    
    // Init to 0% duty cycle & enable motor output
    uint16_t duty = 0;
    MotorControl_SetIntensity(duty);
    MotorControl_On();
    
    // Init microsecond counters to current time
    uint32_t currMicro = FRT_GetMicros();
    uint32_t prevMicro = currMicro;
    
    // Main loop //
    while(1) {
        /*
         * NOTE:    WDT will force a reset if not cleared 
         *          within every 2 sec or less
         */
        RESET_WDT();  // reset watchdog timer at start of each loop
        
        currMicro = FRT_GetMicros();    // update microsecond counter
        
        // This block runs @40Hz
        if ((currMicro - prevMicro) >= DC_UPDATE_RATE) {
            
            duty += 10;    // increase duty-cycle by 1.0%
            
            if (duty > MAX_DC_PERMILLI) { // reset to 0% after exceeding 100.0%
                duty = 0;
            }
            
            // Update PWM duty-cycle
            MotorControl_SetIntensity(duty);
            prevMicro = currMicro;  // store time of last update
        }
    }
    
    while(1);
    return 0;
}
#endif

#ifdef NEW
int main(void) {
    PIC16_Init();
    FRT_Init();
    MotorControl_Init();
    RESET_WDT();
    
    uint16_t duty = 500;
    uint32_t currMilli, prevMilli;
    currMilli = FRT_GetMillis();
    prevMilli = currMilli;
    uint8_t onOff = 0;
    
    while(1) {
        RESET_WDT();
        currMilli = FRT_GetMillis();
        
        if((currMilli - prevMilli) >= 500) {
            if (onOff == 0) {
                MotorControl_SetIntensity(duty);
                MotorControl_On();
                onOff = 1;
            }
            else if (onOff == 1) {
                MotorControl_SetIntensity(0);
                MotorControl_Off();
                onOff = 0;
            }
            prevMilli = currMilli;
        }
    }
    while(1);
    return 0;
}
#endif

#endif


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
