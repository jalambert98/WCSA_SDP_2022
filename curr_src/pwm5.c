
/**
  Section: Included Files
 */

#include <xc.h>
#include "pwm5.h"

// RC1->PWM5:PWM5;
//------------------------------------------------------------------------------

/**
  Section: PWM Module APIs
 */

void PWM5_Initialize(void) {
    // Set the PWM to the options selected in the PIC10 / PIC12 / PIC16 / PIC18 MCUs.
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
/**
 End of File
 */
