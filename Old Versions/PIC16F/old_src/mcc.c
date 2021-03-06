/* 
 * File:    mcc.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: Generated originally by Microchip Code Configurator (MCC) and then
 *       further modified by Jack Lambert
 * 
 * Created on January 26, 2022, 8:45 PM
 */
//------------------------------------------------------------------------------

#include "mcc.h"

//------------------------------------------------------------------------------

void PIC16_Init(void)
{
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
    
    // Init individual libraries
    PMD_Initialize();           // disables unnecessary peripherals
    PIN_MANAGER_Initialize();   // default IO state: TRISx = INPUT, LATx = LOW
    OSCILLATOR_Initialize();    // Instruction clk [Fosc/4] = 4MHz
    WDT_Initialize();           // WDT is disabled - still needs setup
    TMR0_Initialize();          // Linked to FRT module (getMillis + Micros)
    EUSART_Initialize();        // EUSART (for Lidar + Debugging)
    
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
    // HFFRQ 8_MHz; 
    OSCFRQ = 0x04;
    // HFTUN 0; 
    OSCTUNE = 0x00;
    // Wait for PLL to stabilize
    while(PLLR == 0);
}

//------------------------------------------------------------------------------

void WDT_Initialize(void) {
    // WDTPS 1:65536; SWDTEN OFF; 
    WDTCON = 0x16;
}

//------------------------------------------------------------------------------

void PMD_Initialize(void) {
    // CLKRMD CLKR enabled; SYSCMD SYSCLK enabled; FVRMD FVR enabled; IOCMD IOC disabled; NVMMD NVM enabled; 
    PMD0 = 0x01;
    // TMR0MD TMR0 enabled; TMR1MD TMR1 enabled; TMR4MD TMR4 disabled; TMR5MD TMR5 disabled; TMR2MD TMR2 enabled; TMR3MD TMR3 enabled; NCOMD DDS(NCO) enabled; TMR6MD TMR6 disabled; 
    PMD1 = 0x70;
    // DACMD DAC disabled; CMP1MD CMP1 disabled; ADCMD ADC disabled; CMP2MD CMP2 disabled; 
    PMD2 = 0x66;
    // CCP2MD CCP2 enabled; CCP1MD CCP1 enabled; CCP4MD CCP4 enabled; CCP3MD CCP3 enabled; PWM6MD PWM6 disabled; PWM5MD PWM5 enabled; CWG2MD CWG2 disabled; CWG1MD CWG1 disabled; 
    PMD3 = 0xE0;
    // MSSP1MD MSSP1 enabled; UART1MD EUSART enabled; MSSP2MD MSSP2 disabled; 
    PMD4 = 0x04;
    // DSMMD DSM disabled; CLC3MD CLC3 disabled; CLC4MD CLC4 disabled; CLC1MD CLC1 disabled; CLC2MD CLC2 disabled; 
    PMD5 = 0x1F;
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
