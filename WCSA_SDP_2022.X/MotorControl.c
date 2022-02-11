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

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define MAX_DC_PERCENT      100     // 100% duty cycle --> ALWAYS ON
#define MAX_DC_10BIT        1023    // (1023/1023) ticks high --> ALWAYS ON

#define HALF_DC_PERCENT     50      // 50% = half duty cycle
#define HALF_DC_10BIT       512     // (512/1023) = half duty cycle

#define MOTORCONTROL_TEST

//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

uint8_t dutyCyclePercent;
uint16_t dutyCycle10bit;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void MotorControl_Init(void) {  
    // Initialize to 50% duty cycle (TMR/PWM disabled)
    dutyCyclePercent = HALF_DC_PERCENT;
    dutyCycle10bit = HALF_DC_10BIT; 
    MotorControl_Off();
    return;
}

//------------------------------------------------------------------------------

uint8_t MotorControl_SetIntensity(uint8_t dutyCycle) {
    
    // As long as dutyCycle is within [0, 100]%...
    if ((dutyCycle >= 0) && (dutyCycle <= MAX_DC_PERCENT)) {
        
        // Store user-assigned dutyCycle [%]
        dutyCyclePercent = dutyCycle;
        
        // ...and calculate associated ratio of 10-bit range
        dutyCycle10bit = (uint16_t)(((uint32_t)dutyCycle * MAX_DC_10BIT) / 
                                                            MAX_DC_PERCENT);
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

#define DC_UPDATE_RATE      250000 // update duty cycle every [x]us

int main(void) {
    // Init required libraries
    PIC16_Init();
    MotorControl_Init();    // motorControl pin[RB6]
    
    // Init to 0% duty cycle & enable motor output
    uint8_t duty = 0;
    MotorControl_SetIntensity(duty);
    MotorControl_On();
    
    // Init microsecond counters to current time
    unsigned long currMicro = FRT_GetMicros();
    unsigned long prevMicro = currMicro;
    
    // Main loop //
    while(1) {
        currMicro = FRT_GetMicros();    // update microsecond counter
        
        // This block runs @4Hz
        if ((currMicro - prevMicro) >= DC_UPDATE_RATE) {
            
            duty += 10;     // increase duty-cycle by 10%
            
            if (duty > MAX_DC_PERCENT) {  // reset to 0% after exceeding 100%
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
