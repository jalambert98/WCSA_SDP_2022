/* 
 * File:    WCSA_system.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: Generated originally by Microchip Code Configurator (as "mcc.c") and 
 *       then further modified by Jack Lambert
 * 
 * Created on January 26, 2022, 8:45 PM
 */
//------------------------------------------------------------------------------

#include "WCSA_system.h"


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void PIC16_Init(void) {
    INTERRUPT_GlobalInterruptDisable();
    INTERRUPT_PeripheralInterruptDisable();
    
    // Manually disable all peripheral interrupts
    PIE0 = 0x00;
    PIE1 = 0x00;
    PIE2 = 0x00;
    PIE3 = 0x00;
    PIE4 = 0x00;
    
    // Manually clear any existing interrupt flags
    PIR0 = 0x00;
    PIR1 = 0x00;
    PIR2 = 0x00;
    PIR3 = 0x00;
    PIR4 = 0x00;
    
    PMD_Initialize();           // disables unused peripherals
    PIN_MANAGER_Initialize();   // configures default pin states
    OSCILLATOR_Initialize();    // configures HFO to [Fosc=32MHz], [Fins=8MHz]
    WDT_Initialize();           // WDT to force reset of not cleared every 2s
    EUSART_Initialize();        // eusart overrides stdio [RX=RB5],[TX=RC4]
    
    // Enable global + peripheral interrupts
    INTERRUPT_PeripheralInterruptEnable();
    INTERRUPT_GlobalInterruptEnable();
}

//------------------------------------------------------------------------------

void OSCILLATOR_Initialize(void) {
    // NOSC HFINTOSC with 2x PLL; NDIV 1; 
    OSCCON1 = 0x00;
    // CSWHOLD may proceed; SOSCPWR Low power; SOSCBE crystal oscillator; 
    OSCCON3 = 0x00;
    // LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN enabled; 
    OSCEN = 0x40;
    // HFFRQ 16_MHz; 
    OSCFRQ = 0x06;
    // HFTUN 0; 
    OSCTUNE = 0x00;
    // Wait for PLL to stabilize
    while (PLLR == 0) {
    }
}

//------------------------------------------------------------------------------

void WDT_Initialize(void) {
    // WDTPS --> 8s WDT reset period SWDTEN OFF; 
    WDTCON = 0x1A;
}

//------------------------------------------------------------------------------

void PMD_Initialize(void) {
    // CLKRMD CLKR enabled; SYSCMD SYSCLK enabled; FVRMD FVR enabled; IOCMD IOC enabled; NVMMD NVM enabled; 
    PMD0 = 0x01;
    // TMR0MD TMR0 disabled; TMR1MD TMR1 enabled; TMR4MD TMR4 disabled; TMR5MD TMR5 disabled; TMR2MD TMR2 enabled; TMR3MD TMR3 enabled; NCOMD DDS(NCO) enabled; TMR6MD TMR6 disabled; 
    PMD1 = 0x71;
    // DACMD DAC disabled; CMP1MD CMP1 disabled; ADCMD ADC enabled; CMP2MD CMP2 disabled; 
    PMD2 = 0x46;
    // CCP2MD CCP2 disabled; CCP1MD CCP1 disabled; CCP4MD CCP4 enabled; CCP3MD CCP3 enabled; PWM6MD PWM6 disabled; PWM5MD PWM5 enabled; CWG2MD CWG2 disabled; CWG1MD CWG1 disabled; 
    PMD3 = 0xE3;
    // MSSP1MD MSSP1 disabled; UART1MD EUSART enabled; MSSP2MD MSSP2 disabled; 
    PMD4 = 0x06;
    // DSMMD DSM disabled; CLC3MD CLC3 disabled; CLC4MD CLC4 disabled; CLC1MD CLC1 disabled; CLC2MD CLC2 disabled; 
    PMD5 = 0x1F;
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
