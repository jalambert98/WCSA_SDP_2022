/* 
 * File:   MotorControl.c
 * Author: Jack
 *
 * Created on February 8, 2022, 12:25 AM
 */
//------------------------------------------------------------------------------

#include <xc.h>
#include <stdint.h>
#include "MotorControl.h"
#include "tmr2.h"

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

uint8_t TMR2_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TMR2;

    return readVal;
}

//------------------------------------------------------------------------------

void TMR2_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer2 register
    TMR2 = timerVal;
}

//------------------------------------------------------------------------------

void TMR2_LoadPeriodRegister(uint8_t periodVal)
{
   PR2 = periodVal;
}

//------------------------------------------------------------------------------

bool TMR2_HasOverflowOccured(void)
{
    // check if  overflow has occurred by checking the TMRIF bit
    bool status = PIR1bits.TMR2IF;
    if(status)
    {
        // Clearing IF flag.
        PIR1bits.TMR2IF = 0;
    }
    return status;
}

//------------------------------------------------------------------------------

void PWM5_Initialize(void) {
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
#include "mcc.h"
#include "FRT.h"

#define DC_UPDATE_RATE      25000   // update duty cycle every 25ms (40Hz)

int main(void) {
    // Init required libraries
    PIC16_Init();
    MotorControl_Init();    // motorControl pin[RB6]
    
    printf("//=== MotorControl.c ===//\n");
    printf("MOTORCONTROL_TEST - Last compiled on %s at %s\n", __DATE__, __TIME__);
    
    // Init to 0% duty cycle & enable motor output
    uint16_t duty = 0;
    MotorControl_SetIntensity(duty);
    MotorControl_On();
    
    // Init microsecond counters to current time
    unsigned long currMicro = FRT_GetMicros();
    unsigned long prevMicro = currMicro;
    
    // Main loop //
    while(1) {
        /*
         * NOTE:    WDT will force a reset if not cleared 
         *          within every 2 sec or less
         */
        asm("CLRWDT");  // clear watchdog timer at start of each loop
        
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
