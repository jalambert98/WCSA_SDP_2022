/* 
 * File:    PowerButton.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: CCP3 code originally generated by Microchip Code Configurator (MCC) 
 *       and then further modified by Jack Lambert.
 *       PowerButton implementations were written from scratch.
 * 
 * Created on May 8, 2022, 5:00 PM
 */
//------------------------------------------------------------------------------

#include <xc.h>
#include "PowerButton.h"
#include "SpeakerTone.h"
#include "MotorControl.h"
#include "WCSA_system.h"

// RA2->CCP3:CCP3;
//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

// #define POWERBUTTON_TEST


//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

static volatile uint8_t gpioFlag;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void PowerButton_Init(void) {
    // Pin[RA2] = GPIO pin for Soft-Switching Power Button circuit
    SET_A2() = INPUT; // configured as input on startup
    gpioFlag = LOW;

    /* CCP3 configured to pin RA2 
     * & ISR runs on FALLING edges */
    CCP3_Initialize();
}

//------------------------------------------------------------------------------

void PowerButton_ForceShutdown(void) {
    // Drive GPIO pin LOW in FET latching circuit
    gpioFlag = HIGH;
    SET_A2() = OUTPUT;
    WRITE_A2() = LOW;

    // shutdown motor + speaker peripherals
    MotorControl_Off();
    SpeakerTone_Off();
    
    // block further CPU instruction
    while (1) {
        RESET_WDT();
    }
}

//------------------------------------------------------------------------------

uint8_t PowerButton_WasBtnPressed(void) {
    return gpioFlag;
}

//------------------------------------------------------------------------------

void CCP3_Initialize(void) {
    // CCP3MODE Falling edge; CCP3EN enabled; CCP3FMT right_aligned; 
    CCP3CON = 0x84;

    // PPS Module to connect pinRA2 to CCP3 input
    CCP3PPS = 0x02; //RA2->CCP3:CCP3;

    // CCP3CTS0 CCP3 pin; 
    CCP3CAP = 0x00;

    // CCPR3H 0; 
    CCPR3H = 0x00;

    // CCPR3L 0; 
    CCPR3L = 0x00;

    // Selecting Timer 1
    CCPTMRSbits.C3TSEL = 0x1;

    // Clear the CCP3 interrupt flag
    PIR4bits.CCP3IF = 0;

    // Enable the CCP3 interrupt
    PIE4bits.CCP3IE = 1;
}

//------------------------------------------------------------------------------

void CCP3_CaptureISR(void) {
    /*
     * NOTE:    This shutdown routine only runs after detecting
     *          a FALLING EDGE on GPIO pinRA2 (PwrBtn pressed)
     */

    // Clear the CCP3 interrupt flag
    PIR4bits.CCP3IF = 0;
    
    // flag set HIGH indicates shutdown requested (polled in main)
    gpioFlag = HIGH;
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

/* ---------- TEST HARNESS FOR POWER BUTTON SUBSYSTEM ---------- */
#ifdef POWERBUTTON_TEST

int main(void) {
    // --- initialize libraries --- //
    PIC16_Init();
    FRT_Init();
    SpeakerTone_Init();
    PowerButton_Init();

    // --- primary loop --- //
    /*
     *  DO NOTHING, until momentary press detected.
     *  Then, run shutdown routine.
     */
    while (1) {
        if (PowerButton_WasBtnPressed())
            PowerButton_ForceShutdown();
        else
            RESET_WDT();
    }
    return 0;
}

#endif  /* POWERBUTTON_TEST */


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
