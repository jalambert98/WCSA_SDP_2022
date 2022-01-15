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

#define TRIG1     (uint8_t)5
#define TRIG2     (uint8_t)6
#define TRIG3     (uint8_t)8

#define ECHO1     (uint8_t)2
#define ECHO2     (uint8_t)3
#define ECHO3     (uint8_t)7


class JSN_SensLib
{
//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================

  public:
    /**
     * @constr   JSN_SensLib()
     * 
     * @param    None
     * 
     * @return   None
     * 
     * @brief    Sets pin[5,6,8] as OUTPUT mode: TRIG[1,2,3]. Sets pin[2,3,7] as 
     *           INPUT mode: ECHO[1,2,3] - these pins are configured to trigger 
     *           the static ISRs, ISR_ECHO[1,2,3](), whenever the value of the 
     *           corresponding ECHO pin changes state
     * 
     * @author   Jack Lambert, 2022.01.12  
     **/
    JSN_SensLib();

    //------------------------------------------------------------------------------
    /**
     * @funct    JSN_Init()
     * 
     * @param    None
     * 
     * @return   None
     * 
     * @brief    **NOT SURE IF REQUIRED (since constructor performs most initialization)
     *           **BUT MAY END UP USING FOR ADDITIONAL SETUP AS WELL
     * 
     * @author   Jack Lambert, [DATE]
     **/
    void JSN_Init();

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
     * @author   Jack Lambert, [DATE]
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
     * @author   Jack Lambert, [DATE]
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
     * @author   Jack Lambert, [DATE]
     **/
    unsigned int JSN_TOF_mm(unsigned long tofMicro);

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
