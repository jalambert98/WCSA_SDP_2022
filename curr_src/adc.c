
/**
  Section: Included Files
 */

#include <xc.h>
#include "adc.h"
#include "device_config.h"

// #define ADC_TEST

//------------------------------------------------------------------------------
/**
  Section: Macro Declarations
 */
#define ACQ_US_DELAY 5

static volatile adc_result_t adcReading;

//------------------------------------------------------------------------------

/**
  Section: ADC Module APIs
 */

void ADC_Initialize(void) {
    // set the ADC to the options selected in the User Interface

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
    return ((adc_result_t) ((ADRESH << 8) + ADRESL));
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
    // Clear the ADC interrupt flag
    PIR1bits.ADIF = 0;

}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

#ifdef ADC_TEST
#include "mcc.h"
#include "FRT.h"

int main(void) {
    PIC16_Init();
    ADC_SelectChannel(vBat);

    SET_C0() = OUTPUT;
    WRITE_C0() = LOW;

    unsigned long currMilli = FRT_GetMillis();
    unsigned long prevMilli = currMilli;

    while (1) {
        currMilli = FRT_GetMillis();

        if ((currMilli - prevMilli) >= 100) {
            ADC_StartConversion();
            while(!ADC_IsConversionDone());
            adcReading = ADC_GetConversionResult();

            if ((adcReading & 0x3FF) > 400)
                WRITE_C0() = HIGH;
            else
                WRITE_C0() = LOW;

            prevMilli = currMilli;
        }
    }

    while (1);
    return 0;
}

#endif
//------------------------------------------------------------------------------
/**
 End of File
 */
