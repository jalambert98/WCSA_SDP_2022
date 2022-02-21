/* 
 * File:    mcc.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * Created on January 26, 2022, 8:45 PM
 */
//------------------------------------------------------------------------------

#include "mcc.h"
#include "eusart.h"

//------------------------------------------------------------------------------

void SYSTEM_Initialize(void) {
    PMD_Initialize();
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    WDT_Initialize();
    CCP3_Initialize();
    CCP1_Initialize();
    TMR2_Initialize();
    TMR0_Initialize();
    CCP2_Initialize();
    CCP4_Initialize();
    TMR3_Initialize();
    PWM5_Initialize();
    TMR1_Initialize();
    EUSART_Initialize(); 
}

//------------------------------------------------------------------------------

void OSCILLATOR_Initialize(void) {
    // NOSC HFINTOSC with 2x PLL; NDIV 1; 
    OSCCON1 = 0x00;
    // CSWHOLD may proceed; SOSCPWR Low power; SOSCBE crystal oscillator; 
    OSCCON3 = 0x00;
    // LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCEN = 0x00;
    // HFFRQ 8_MHz; 
    OSCFRQ = 0x04;
    // HFTUN 0; 
    OSCTUNE = 0x00;
    // Wait for PLL to stabilize
    while (PLLR == 0) {
    }
}

//------------------------------------------------------------------------------

void WDT_Initialize(void) {
    // WDTPS 1:65536; SWDTEN OFF; 
    WDTCON = 0x16;
}

//------------------------------------------------------------------------------

void PMD_Initialize(void) {
    /* EVERYTHING IS CURRENTLY ENABLED!! 
     * FIX THIS WHEN YOU FINISH THE PERIPHERAL LIST!! */
    PMD0 = 0x00;
    PMD1 = 0x00;

    // DACMD DAC disabled; CMP1MD CMP1 disabled; ADCMD ADC disabled; CMP2MD CMP2 disabled; 
    PMD2 = 0x66;
    PMD3 = 0x00;
    PMD4 = 0x00;

    // DSMMD DSM disabled; CLC3MD CLC3 disabled; CLC4MD CLC4 disabled; CLC1MD CLC1 disabled; CLC2MD CLC2 disabled; 
    PMD5 = 0x1F;
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
