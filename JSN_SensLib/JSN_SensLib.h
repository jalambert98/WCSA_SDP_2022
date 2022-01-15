/* 
 * File:            JSN_SensLib.h
 * Author:          Jack Lambert <joalambe@ucsc.edu>
 * Project:         White Cane Sensor Attachment
 * Course:          UCSC ECE129 - SDP '21
 *
 * Created:         January 12, 2022, 1:45 PM
 * Last Modified:   January 12, 2022, 6:25 PM
 */
 
#ifndef JSN_SensLib_h
#define JSN_SensLib_h

#include "Arduino.h"

//==============================================================================
//---------------------------------#DEFINES-------------------------------------
//==============================================================================

// Used for specifying to constructor which system to implement
#define EXTERNAL_INTERRUPTS   (uint8_t)0
#define INPUT_CAPTURE         (uint8_t)1

// Used for referencing pins according to their function (rather than #)
#define TRIG1_PIN             (uint8_t)5
#define TRIG2_PIN             (uint8_t)6
#define TRIG3_PIN             (uint8_t)8
#define ECHO1_PIN             (uint8_t)2
#define ECHO2_PIN             (uint8_t)3
#define ECHO3_PIN             (uint8_t)7

// Used for INPUT_CAPTURE mode config setup
#define SET_PIN7_OUT()        (DDRE |= (1 << 6))
#define SET_PIN8_OUT()        (DDRB |= (1 << 4))
#define SET_PIN9_OUT()        (DDRB |= (1 << 5))
#define SET_PIN4_IN()         (DDRD &= ~(1 << 4))

class JSN_SensLib
{
//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

  public:
    /**
     * @constr   JSN_SensLib()
     * 
     * @param    uint8_t SYSTEM_USING : Either EXTERNAL_INTERRUPTS or 
     *                                  INPUT_CAPTURE should be passed as the
     *                                  argument to this constructor.
     * 
     * @return   None
     * 
     * @brief    For EXTERNAL_INTERRPUTS mode: This constructor sets pin[5,6,8] 
     *           as OUTPUT mode: TRIG[1,2,3]. Sets pin[2,3,7] as INPUT mode: 
     *           ECHO[1,2,3] - these pins are configured to trigger the static 
     *           ISRs, ISR_ECHO[1,2,3](), whenever the value of the corresponding 
     *           ECHO pin changes state.
     * 
     *           For INPUT_CAPTURE mode: This constructor sets pin[7,8,9] to
     *           TRIG[1,2,3] as outputs to sensors. Sets pin[4] as a singular
     *           ECHO input (multiplexed 1 of 3 sensor signals)
     * 
     * @author   Jack Lambert, 2022.01.12  
     **/
    JSN_SensLib(uint8_t SYSTEM_USING);

    //------------------------------------------------------------------------------
    /**
     * @funct    JSN_GetDistance(uint8_t sens)
     * 
     * @param    uint8_t sens       :  value of [1,2,3] corresponding to each JSN
     * 
     * @return   unsigned int dist  :  distance reading (in mm) last measured by the 
     *                                 indicated sensor
     * 
     * @brief    Returns the distance reading (in mm) last reported by the indicated
     *           ultrasonic sensor & updated to dist1 static var
     * 
     * @author   Jack Lambert, 2022.01.13
     **/
     unsigned int JSN_GetDistance(uint8_t sens);


//==============================================================================
//------------------------------ PRIVATE LIBRARY -------------------------------
//==============================================================================

  private:
    /**
     * @funct    JSN_Trig(uint8_t sens)
     * 
     * @param    uint8_t sens  :  value of [1,2,3] for corresponding sensor
     * 
     * @return   None
     * 
     * @brief    Sends the appropriate trigger signal (HIGH for >10us) to the
     *           specified ultrasonic sensor.
     * 
     * @author   Jack Lambert, 2022.01.13
     **/
    void JSN_Trig(uint8_t sens);

    //------------------------------------------------------------------------------
    /**
     * @funct    JSN_TOF_mm(tofMicro)
     * 
     * @param    unsigned long tofMicro : Time of flight of ultrasonic wave, 
     *                                    represented in microseconds
     * 
     * @return   int mm   :  Distance [mm] between sensor & nearest object in FoV
     * 
     * @brief    Used as a helper function to convert the time of flight (in 
     *           microseconds) to a physical distance measurement (in mm).
     * 
     * @author   Jack Lambert, 2022.01.13
     **/
    unsigned int JSN_TOF_mm(unsigned long tofMicro);

    //------------------------------------------------------------------------------
    /**
     * @funct    JSN_TOF_mm(tofMicro)
     * 
     * @param    unsigned long tofMicro : Time of flight of ultrasonic wave, 
     *                                    represented in microseconds
     * 
     * @return   int mm   :  Distance [mm] between sensor & nearest object in FoV
     * 
     * @brief    Used as a helper function to convert the time of flight (in 
     *           microseconds) to a physical distance measurement (in mm).
     * 
     * @author   Jack Lambert, [DATE]
     **/
    unsigned int JSN_ReadTMR1();

    //------------------------------------------------------------------------------
    /**
     * @funct    ISR_ECHO[1,2,3]()
     * 
     * @param    None
     * 
     * @return   None
     * 
     * @brief    These ISRs should auto-run anytime the corresponding ECHO[1,2,3] 
     *           pin changes state. During each ISR call, the current micros() 
     *           value is stored. When the ECHO1 pin falls LOW, the time duration 
     *           is calculated and stored as the time-of-flight (in TMR ticks).
     * 
     * @author   Jack Lambert, [DATE]
     **/
    static void ISR_ECHO1();
    static void ISR_ECHO2();
    static void ISR_ECHO3();
};

#endif
