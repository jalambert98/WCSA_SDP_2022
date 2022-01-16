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
// Used for specifying to CONSTRUCTOR which hardware system to implement
#define EXTERNAL_INTERRUPTS   0x00
#define INPUT_CAPTURE         0x01

// Manual pin manipulation via bitwise operations on CPU registers
//-------------- POTENTIAL TRIG PINS --------------//
#define SET_PIN5_OUT()        (DDRC |= (0x01 << DDC6))
#define WRITE_PIN5_HIGH()     (PORTC |= (0x01 << PORTC6))
#define WRITE_PIN5_LOW()      (PORTC &= ~(0x01 << PORTC6))

#define SET_PIN6_OUT()        (DDRD |= (0x01 << DDD7))
#define WRITE_PIN6_HIGH()     (PORTD |= (0x01 << PORTD7))
#define WRITE_PIN6_LOW()      (PORTD &= ~(0x01 << PORTD7))

#define SET_PIN7_OUT()        (DDRE |= (0x01 << DDE6))
#define WRITE_PIN7_HIGH()     (PORTE |= (0x01 << PORTE6))
#define WRITE_PIN7_LOW()      (PORTE &= ~(0x01 << PORTE6))

#define SET_PIN8_OUT()        (DDRB |= (0x01 << DDB4))
#define WRITE_PIN8_HIGH()     (PORTB |= (0x01 << PORTB4))
#define WRITE_PIN8_LOW()      (PORTB &= ~(0x01 << PORTB4))

#define SET_PIN9_OUT()        (DDRB |= (0x01 << DDB5))
#define WRITE_PIN9_HIGH()     (PORTB |= (0x01 << PORTB5))
#define WRITE_PIN9_LOW()      (PORTB &= ~(0x01 << PORTB5))

//-------------- POTENTIAL ECHO PINS --------------//
#define SET_PIN2_IN()         (DDRD &= ~(0x01 << DDD1))
#define READ_PIN2()           (PIND1)

#define SET_PIN3_IN()         (DDRD &= ~(0x01 << DDD0))
#define READ_PIN3()           (PIND0)

#define SET_PIN4_IN()         (DDRD &= ~(0x01 << DDD4))
#define READ_PIN4()           (PIND4)

#define SET_PIN7_IN()         (DDRE &= ~(0x01 << DDE6))
#define READ_PIN7()           (PINE6)

//---------- GLOBAL INTERRUPT DISABLE/ENABLE ----------//
#define INTERRUPT_DISABLE()   (SREG &= ~(0x01 << SREG_I))
#define INTERRUPT_ENABLE()    (SREG |= (0x01 << SREG_I))

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

    //------------------------------------------------------------------------------
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
     

  //==============================================================================
  //------------------------------ PRIVATE LIBRARY -------------------------------
  //==============================================================================
  private:
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
    static unsigned int JSN_TOF_mm(unsigned long tofMicro);

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
    static unsigned int JSN_ReadTMR1();

    //------------------------------------------------------------------------------
    /**
     * @funct    ISR(INTx_vect)
     * 
     * @param    None
     * 
     * @return   None
     * 
     * @brief    These ISRs should auto-run anytime the corresponding ECHO[1,2,3] 
     *           pin changes state. During each ISR call, the current micros() 
     *           value is stored. When the ECHO1 pin falls LOW, the time duration 
     *           is calculated and stored as the time-of-flight (in microseconds).
     * 
     * @author   Jack Lambert, [DATE]
     **/
   /* ISR(INT1_vect);
      ISR(INT0_vect);
      ISR(INT6_vect); */
};

#endif
