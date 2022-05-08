/* 
 * File:    adc.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: Generated originally by Microchip Code Configurator (MCC) and then
 *       further modified by Jack Lambert
 * 
 * Created on May 2, 2022, 3:10 PM
 */
//------------------------------------------------------------------------------

#include <xc.h>
#include "adc.h"
#include "device_config.h"

//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define ACQ_US_DELAY 5

#define ADC_TEST

//==============================================================================
//---------------------------- STATIC VARIABLES --------------------------------
//==============================================================================

static volatile adc_result_t adcReading;


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void ADC_Initialize(void) {
    // ADFM right; ADNREF VSS; ADPREF FVR; ADCS FOSC/64; 
    ADCON1 = 0xE3;

    // ADACT no_auto_trigger; 
    ADACT = 0x00;

    // ADRESL 0; 
    ADRESL = 0x00;

    // ADRESH 0; 
    ADRESH = 0x00;

    // ADGO stop; ADON enabled; CHS ANA5; 
    ADCON0 = 0x15;
    
    // Enable 2.048V fixed voltage reference as ADC +REF
    FVRCON = 0x82;

    // Enabling ADC interrupt.
    PIE1bits.ADIE = 1;
}

//------------------------------------------------------------------------------

void ADC_SelectChannel(adc_channel_t channel) {
    // select the A/D channel
    ADCON0bits.CHS = channel;
    
    // Turn on the ADC module
    ADCON0bits.ADON = 1;
}

//------------------------------------------------------------------------------

void ADC_StartConversion(void) {
    // Start the conversion
    ADCON0bits.ADGO = 1;
}

//------------------------------------------------------------------------------

bool ADC_IsConversionDone(void) {
    // Start the conversion
    return ((bool) (!ADCON0bits.ADGO));
}

//------------------------------------------------------------------------------

adc_result_t ADC_GetConversionResult(void) {
    // Conversion finished, return the result
    return ((adc_result_t) ((ADRESH << 8) | ADRESL));
}

//------------------------------------------------------------------------------

adc_result_t ADC_GetConversion(adc_channel_t channel) {
    // select the A/D channel
    ADCON0bits.CHS = channel;

    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Acquisition time delay
    __delay_us(ACQ_US_DELAY);

    // Start the conversion
    ADCON0bits.ADGO = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.ADGO) {
    }

    // Conversion finished, return the result
    return ((adc_result_t) ((ADRESH << 8) + ADRESL));
}

//------------------------------------------------------------------------------

void ADC_TemperatureAcquisitionDelay(void) {
    __delay_us(200);
}

//------------------------------------------------------------------------------

void ADC_ISR(void) {
    adcReading = ADC_GetConversionResult();
    
    // Clear the ADC interrupt flag
    PIR1bits.ADIF = 0;
}

//------------------------------------------------------------------------------

adc_result_t ADC_GetCurrReading(void) {
    return adcReading;
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

#ifdef ADC_TEST
#include "mcc.h"
#include "FRT.h"

#define ADC_THRESHOLD   800     // [800/1023]*2.048V (FVR) = 1.6V threshold

int main(void) {
    PIC16_Init();               // system init
    ADC_SelectChannel(vBat);    // vBat = ADCH5 = pinRA5

    SET_C0() = OUTPUT;          // debugging output pin to LED
    WRITE_C0() = LOW;           // begin output LOW

    unsigned long currMilli = FRT_GetMillis();  // for FRT timing
    unsigned long prevMilli = currMilli;

    // primary loop behavior
    while (1) {
        /*
         * NOTE:    WDT will force a reset if not cleared 
         *          within every 2 sec or less
         */
        asm("CLRWDT");  // clear watchdog timer at start of each loop
        
        // update free-running timer
        currMilli = FRT_GetMillis();

        // Every 200ms, run this block...
        if ((currMilli - prevMilli) >= 200) {
            
            ADC_StartConversion();  // start new ADC conversion on vBat pin
            /* 
             * ADC_ISR will update adcReading static variable
             * automatically, once the conversion is finished.
             */

            
            if (ADC_GetCurrReading() >= ADC_THRESHOLD) // if pinRA5 reads > 1.6V
                WRITE_C0() = HIGH;
            else
                WRITE_C0() = LOW;

            // update time of last reading
            prevMilli = currMilli;
        }
    }

    while (1);
    return 0;
}

#endif


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
