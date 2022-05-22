/* 
 * File:    BatteryMonitor.c
 * Author:  Jack Lambert     <joalambe@ucsc.edu>
 * Project: WCSA_SDP_2022
 *
 * NOTE: ADC code originally generated by Microchip Code Configurator (MCC) 
 *       and then further modified by Jack Lambert.
 *       BatteryMonitor implementations were written from scratch.
 * 
 * Created on May 2, 2022, 3:10 PM
 */
//------------------------------------------------------------------------------

#include <xc.h>
#include "BatteryMonitor.h"


// ADC(vBat) == pin[RA5]
//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define ACQ_US_DELAY        5

#define BUFFER_SIZE         64
#define BUFFER_SHIFT        6    // 2^6 = 64 = BUFFER_SIZE

// #define BATTERYMONITOR_TEST

//==============================================================================
//----------------------------- STATICS & ENUMS --------------------------------
//==============================================================================

static volatile adc_result_t adcReading;

//------------------------------------------------------------------------------
/*
 * @struct:     static struct ADCBuffer
 * 
 * @vars:       unsigned int  : vals[BUFFER_SIZE]   - Data held within buffer
 *              unsigned char : tail          - Index where new data is 
 * @brief:      Circular buffer to hold the last <BUFFER_SIZE> values read by
 *              the ADC. Used in order to report the average value (digital LPF)
 * @author:     Jack Lambert <joalambe@ucsc.edu>
 *              April 1, 2021
 */
static struct {
    unsigned int vals[BUFFER_SIZE];
    unsigned char tail;
} ADCBuffer;


//==============================================================================
//------------------------ PRIVATE FUNCTION PROTOTYPES -------------------------
//==============================================================================
/*
 * @funct:  ADCBuffer_Init()
 * 
 * @param:  None
 * @return: None
 * @brief:  Initializes ADC circular buffer used for digital LPF
 * @author: Jack Lambert <joalambe@ucsc.edu>
 *          April 1, 2021
 */
void ADCBuffer_Init(void);

//------------------------------------------------------------------------------
/*
 * @funct:  ADCBuffer_AddData(newVal)
 * 
 * @param:  unsigned int : newVal   -   value to add to circular buffer
 * @return: None
 * @brief:  Adds newVal to the tail index of ADC circular buffer
 * @author: Jack Lambert <joalambe@ucsc.edu>
 *          April 1, 2021
 */
void ADCBuffer_AddData(unsigned int newVal);


//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

void BatteryMonitor_Init(void) {
    /* Set internal FVR to output +2.048V fixed reference */
    FVRCON = 0x82;
    
    /* Initialize ADC --> (ADCclk = [Fosc/64]),
     * [(-Ref = Vss),(+Ref = FVR)], right-justified result  */
    ADC_Initialize();
    
    ADC_SelectChannel(vBat);    // vBat = ADCH5 = pinRA5
    
    adcReading = 0;   // initialize static var to 0 in-case it is read early
    
    ADCBuffer_Init();
}

//------------------------------------------------------------------------------

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

void ADC_ISR(void) {
    adcReading = ADC_GetConversionResult();
    ADCBuffer_AddData(adcReading);
    
    // Clear the ADC interrupt flag
    PIR1bits.ADIF = 0;
}

//------------------------------------------------------------------------------

adc_result_t ADC_GetCurrReading(void) {
    return adcReading;
}


//==============================================================================
//------------------------- PRIVATE FUNCTION LIBRARY ---------------------------
//==============================================================================

void ADCBuffer_Init(void) {
    unsigned char i;
    for (i = 0; i < BUFFER_SIZE; i++)
        ADCBuffer.vals[i] = 0; // clear buffer data

    ADCBuffer.tail = 0; // reset tail index
}

//------------------------------------------------------------------------------

void ADCBuffer_AddData(unsigned int newVal) {
    ADCBuffer.vals[ADCBuffer.tail] = newVal; // add newVal to buffer
    ADCBuffer.tail = (ADCBuffer.tail + 1) % BUFFER_SIZE; // increment tail
}

//------------------------------------------------------------------------------

uint16_t ADCBuffer_GetFilteredReading(void) {
    uint32_t sumResult = 0; // Running sum of each currProduct
    uint8_t iVals = ADCBuffer.tail; // Starting index for vals[] array
    uint8_t iFilter = 0; // Index for weightsLPF[] array

    do {
        sumResult += ADCBuffer.vals[iVals];
        iVals = (iVals + 1) % BUFFER_SIZE; // increment iVals from tail
        iFilter++; // increment iFilter from 0
    } while (iFilter < BUFFER_SIZE); // perform for all BUFFER_SIZE vals

    // Shift to "divide" by sum of all filter weights
    uint16_t filtered = (uint16_t)(sumResult >> BUFFER_SHIFT);
    return filtered;
}


//==============================================================================
//------------------------- CONDITIONAL TEST HARNESS ---------------------------
//==============================================================================

/* ---------- TEST HARNESS FOR BATTERY MONITORING SUBSYSTEM ---------- */
#ifdef BATTERYMONITOR_TEST

#include "WCSA_system.h"
#include "FRT.h"
#include "SpeakerTone.h"

// ======= DEFINES ======= //
#define ADC_THRESHOLD   800     // [800/1023]*2.048V (FVR) = 1.6V threshold


// ======= MAIN() ======= //
int main(void) {
    PIC16_Init();               // system init
    BatteryMonitor_Init();      // battery monitor setup
    SpeakerTone_Init();         
    FRT_Init();                 // global milli/micro-second counter
    
    //--- Initial Print Statement ---//
    printf("//=== BatteryMonitor.c ===//\n");
    printf("BATTERYMONITOR_TEST - Last compiled on %s at %s\n\n", __DATE__, __TIME__);

    SET_C0() = OUTPUT;          // debugging output pin to LED
    WRITE_C0() = LOW;           // begin output LOW

    unsigned long currMilli = FRT_GetMillis();  // for FRT timing
    unsigned long prevMilli = currMilli;
    adc_result_t currReading = 0;
    adc_result_t filteredReading = 0;
    uint8_t batteryLow = 0;
    

    // ----- primary loop behavior ----- //
    while (1) {
        /*
         * NOTE:    WDT will force a reset if not cleared 
         *          within every 2 sec or less
         */
        RESET_WDT();        // reset WDT at start of each loop
        
        // update free-running timer
        currMilli = FRT_GetMillis();

        // Every 200ms, run this block...
        if ((currMilli - prevMilli) >= 200) {
            
            ADC_StartConversion();  // start new ADC conversion on vBat pin
            /* 
             * ADC_ISR will update adcReading static variable
             * automatically, once the conversion is finished.
             */

            currReading = ADC_GetCurrReading();
            filteredReading = ADCBuffer_GetFilteredReading();
            
            if (filteredReading > ADC_THRESHOLD) { // if pinRA5 reads > 1.6V
                WRITE_C0() = HIGH;                     // turn on LED
                if (batteryLow == 1) {
                    batteryLow = 0;
                    SpeakerTone_StartupChirp();
                }
            }
            else {                          // if RA5 <= 1.6V
                if (batteryLow == 0) {
                    batteryLow = 1;
                    SpeakerTone_ShutdownChirp();
                }
                WRITE_C0() = LOW;               // turn off LED
            }
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
