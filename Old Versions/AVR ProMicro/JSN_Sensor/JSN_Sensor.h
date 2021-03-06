/* 
 * File:            JSN_Sensor.h
 * Author:          Jack Lambert <joalambe@ucsc.edu>
 * Project:         White Cane Sensor Attachment
 * Course:          UCSC ECE129 - SDP '21
 *
 * Created:         January 12, 2022, 01:45 PM
 * Last Modified:   January 16, 2022, 09:25 PM
 */
 
#ifndef JSN_Sensor_h
#define JSN_Sensor_h

#include "Arduino.h"

//==============================================================================
//---------------------------------#DEFINES-------------------------------------
//==============================================================================

// Used for specifying to JSN_Sensor::Init() which hardware system to implement
#define EXTERNAL_INTERRUPTS   0x00
#define INPUT_CAPTURE         0x01

// System clock frequency
#define CLOCK_FREQ            16000000

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
#define READ_PIN2()           (0x01 & (PIND >> PIND1))

#define SET_PIN3_IN()         (DDRD &= ~(0x01 << DDD0))
#define READ_PIN3()           (0x01 & (PIND >> PIND0))

#define SET_PIN4_IN()         (DDRD &= ~(0x01 << DDD4))
#define READ_PIN4()           (0x01 & (PIND >> PIND4))

#define SET_PIN7_IN()         (DDRE &= ~(0x01 << DDE6))
#define READ_PIN7()           (0x01 & (PINE >> PINE6))

// for debugging
#define SET_LED_OUT()         (DDRC |= (0x01 << DDC7))
#define LED_ON()              (PORTC |= (0x01 << PORTC7))
#define LED_OFF()             (PORTC &= ~(0x01 << PORTC7))

//---------- GLOBAL INTERRUPT DISABLE/ENABLE ----------//
#define INTERRUPT_DISABLE()   (SREG &= ~(0x01 << SREG_I))
#define INTERRUPT_ENABLE()    (SREG |= (0x01 << SREG_I))

class JSN_Sensor
{
  public:
    //--------------- INSTANCE VARIABLES ---------------//
    volatile unsigned long echoHighTime;         // in microseconds
    volatile unsigned int distance;             // in millimeters
    uint8_t trigPin, echoPin;                   // IO pins for each sensor

//==============================================================================
//------------------------------ PUBLIC LIBRARY --------------------------------
//==============================================================================
    /**
     * @constr   JSN_Sensor(uint8_t trigPin, uint8_t echoPin)
     * 
     * @param    <uint8_t trigPin> : MCU pin# to assign to this sensor's TRIG pin
     *           <uint8_t echoPin> : MCU pin# to assign to this sensor's ECHO pin
     * 
     * @return   None
     * 
     * @brief    Creates an instance of JSN_Sensor
     * 
     * @author   Jack Lambert, 2022.01.12  
     **/
    JSN_Sensor(uint8_t trigPin, uint8_t echoPin);

    //------------------------------------------------------------------------------
    /**
     * @funct    Init(uint8_t SYSTEM_USING)
     * 
     * @param    <uint8_t SYSTEM_USING> : Either EXTERNAL_INTERRUPTS or 
     *                                    INPUT_CAPTURE should be passed as
     *                                    the argument to this constructor.
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
     * @author   Jack Lambert, 2022.01.13
     **/
    static void Init(uint8_t SYSTEM_USING);

    //------------------------------------------------------------------------------
    /**
     * @funct    GetDistance()
     * 
     * @param    None
     * 
     * @return   unsigned int dist  :  distance reading (in mm) last measured by the 
     *                                 calling object (instance of JSN_Sensor)
     * 
     * @brief    Called by an instance of JSN_Sensor to return the last updated
     *           distance reading from the calling sensor (in mm)
     * 
     * @author   Jack Lambert, 2022.01.13
     **/
    unsigned int GetDistance();

    //------------------------------------------------------------------------------
    /**
     * @funct    Trig()
     * 
     * @param    None
     * 
     * @return   None
     * 
     * @brief    Sends the appropriate trigger signal (HIGH for >10us) to the sensor
     *           associated with the instance of JSN_Sensor calling this function
     * 
     * @author   Jack Lambert, 2022.01.13
     **/
    void Trig();

    //------------------------------------------------------------------------------
    /**
     * @funct    ReadTMR1()
     * 
     * @param    None
     * 
     * @return   unsigned int : TMR1 (ticks)
     * 
     * @brief    Returns the current 16-bit TMR1 counter value. (1 tick = 0.5us)
     * 
     * @author   Jack Lambert, 2022.01.16
     **/
    static unsigned int ReadTMR1();

    //------------------------------------------------------------------------------
    /**
     * @funct    ISR(X_vect)
     * 
     * @param    None
     * 
     * @return   None
     * 
     * @brief    These ISRs should auto-run anytime the corresponding ECHO pin 
     *           changes state. During each ISR call, the current TMR1 value
     *           is stored. When the ECHO pin falls LOW, the time duration 
     *           is calculated and stored as the time-of-flight (in TMR1 ticks).
     * 
     * @author   Jack Lambert, 2022.01.16
     **/
    /*ISR(INT1_vect);
      ISR(INT0_vect);
      ISR(INT6_vect);
      ISR(TIMER1_CAPT_vect)*/    
    //------------------------------------------------------------------------------
};

#endif

//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
