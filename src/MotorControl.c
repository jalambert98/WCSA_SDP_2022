/* 
 * File:   MotorControl.c
 * Author: Jack
 *
 * Created on February 8, 2022, 12:25 AM
 */
//------------------------------------------------------------------------------

#include "MotorControl.h"
#include "tmr2.h"
#include "pwm5.h"

// [PWM5] output --> Pin[RC1]
//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define MAX_DC_PERMILLI     1000    // 100.0% duty cycle --> ALWAYS ON
#define MAX_DC_10BIT        1023    // (1023/1023) ticks high --> ALWAYS ON

#define HALF_DC_PERMILLI    500     // 50.0% = half duty cycle
#define HALF_DC_10BIT       512     // (512/1023) = half duty cycle

// #define MOTORCONTROL_TEST

//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

static uint16_t dutyCyclePerMilli;
static uint16_t dutyCycle10bit;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void MotorControl_Init(void) {  
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

void MotorControl_On(void) {
    // Enable TMR/PWM
    TMR2_StartTimer();
    return;
}

//------------------------------------------------------------------------------

void MotorControl_Off(void) {
    // Disable & reset TMR/PWM
    TMR2_StopTimer();
    TMR2_WriteTimer(0x00);  // clear TMR2 ticks after stopping motor pulse
    return;
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

#ifdef MOTORCONTROL_TEST

#include "FRT.h"

#define DC_UPDATE_RATE      25000   // update duty cycle every 25ms (40Hz)

int main(void) {
    // Init required libraries
    PIC16_Init();
    MotorControl_Init();    // motorControl pin[RB6]
    
    printf("//=== MotorControl.c ===//\n");
    printf("MOTORCONTROL_TEST last compiled on %s at %s\n", __DATE__, __TIME__);
    
    // Init to 0% duty cycle & enable motor output
    uint16_t duty = 0;
    MotorControl_SetIntensity(duty);
    MotorControl_On();
    
    // Init microsecond counters to current time
    unsigned long currMicro = FRT_GetMicros();
    unsigned long prevMicro = currMicro;
    
    // Main loop //
    while(1) {
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

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
