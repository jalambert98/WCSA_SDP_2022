/* 
 * File:            JSN_Sensor.cpp
 * Author:          Jack Lambert <joalambe@ucsc.edu>
 * Project:         White Cane Sensor Attachment
 * Course:          UCSC ECE129 - SDP '21
 *
 * Created:         January 12, 2022, 01:35 PM
 * Last Modified:   January 16, 2022, 09:35 PM
 */

 #include "Arduino.h"
 #include "JSN_Sensor.h"
 
//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define US_WAVE_SPEED       340     // speed of ultrasonic wave = 340[m/s]
#define TRIG_PULSE_WIDTH    11      // 11us > 10us minimum pulse width
#define MICROS_PER_MILLI    1000


//==============================================================================
//---------------------------- STATICS VARIABLES -------------------------------
//==============================================================================
      
static uint8_t sel_sys;       // either EXTERNAL_INTERRUPTS or INPUT_CAPTURE
static uint8_t sreg;          // mem location for storing global interrupt flags
static volatile JSN_Sensor *lastTrig; // pointer to obj which last called Trig()
static volatile unsigned long ticksUp, ticksDown;   // in TMR1 ticks


//==============================================================================
//-------------------------------- CONSTRUCTOR ---------------------------------
//==============================================================================

JSN_Sensor::JSN_Sensor(uint8_t trigPin, uint8_t echoPin) {
  // Initialize private instance vars
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  this->echoHighTime = 0;
  this->distance = 0;

  lastTrig = this;  // initialize module var to this incase ISR runs early

  //----- Configure the indicated TRIG pin as output & initialize LOW -----//
  switch(trigPin) {
    case 5:
      SET_PIN5_OUT();
      WRITE_PIN5_LOW();
      break;
    case 6:
      SET_PIN6_OUT();
      WRITE_PIN6_LOW();
      break;
    case 7:
      SET_PIN7_OUT();
      WRITE_PIN7_LOW();
    case 8:
      SET_PIN8_OUT();
      WRITE_PIN8_LOW();
      break;
    case 9:
      SET_PIN9_OUT();
      WRITE_PIN9_LOW();
      break;
    default:
      Serial.print("ERROR: Invalid TRIG pin! (Must be one of the following: [5,6,7,8,9])\n");
      break;
  }

  //------------ Configure the indicated ECHO pin as input ------------//
  switch(echoPin) {
    case 2:
      SET_PIN2_IN();
      break;
    case 3:
      SET_PIN3_IN();
      break;
    case 4:
      SET_PIN4_IN();
      break;
    case 7:
      SET_PIN7_IN();
      break;
    default:
      Serial.print("ERROR: Invalid ECHO pin! (Must be one of the following: [2,3,4,7])\n");
      break;
  }
}


//==============================================================================
//----------------------------- FUNCTION LIBRARY -------------------------------
//==============================================================================

void JSN_Sensor::Init(uint8_t SYSTEM_USING) {
  /*===============================================*/
  /* README before using!!                         */
  /* See notes above each switch case following:   */
  /*    switch(SYSTEM_USING) {                     */
  /*===============================================*/
  // Store the user-specified hardware system for future function calls
  sel_sys = SYSTEM_USING;

  // Store current global flag states, then disable interrupts
  sreg = SREG;
  INTERRUPT_DISABLE();

  // Pause all hardware timers
  GTCCR = ((0x01 << TSM) | (0x01 << PSRASY) | (0x01 << PSRSYNC));

  // Clear relevant hardware registers
  TCNT1 = 0x0000;   // clear TMR1 counter reg
  TCCR1A = 0x00;    // clear TMR1 control reg A
  TCCR1B = 0x00;    // clear TMR1 control reg B
  TIMSK1 = 0x00;    // clear TMR1 interrupt mask reg
  TIFR1 = 0x00;     // clear existing TMR1 interrupt flags
  ICR1 = 0x0000;    // clear IC1 reg
  EIMSK = 0x00;     // Clear ext interrupt mask reg
  EICRA = 0x00;     // Clear ext interrupt control reg A
  EICRB = 0x00;     // Clear ext interrupt control reg B
  EIFR = 0x00;      // Clear any existing ext interrupt flags

  // TMR1 ticks @{[f=2MHz], [T=0.5us]}
  TCCR1B |= (1 << CS01);  // Configure TMR1 for 1:8 prescalar 

  switch(SYSTEM_USING) {
    /* NOTE!!! For EXTERNAL_INTERRUPTS:
     * Ensure that pins[5,6,8] are already configured as TRIG outputs,
     * and that pins[2,3,7] are already configured as ECHO inputs.
     */
    case EXTERNAL_INTERRUPTS:
      // Configure ECHO pins to run ISR each pin value CHANGE
      EICRA |= (0x01 << ISC10); // INT1 ext interrupts on rising & falling edges
      EICRA |= (0x01 << ISC00); // INT0 ext interrupts on rising & falling edges
      EICRB |= (0x01 << ISC60); // INT6 ext interrupts on rising & falling edges
      EIMSK |= (0x01 << INT1);  // Enable INT1 interrupts on pin2
      EIMSK |= (0x01 << INT0);  // Enable INT0 interrupts on pin3
      EIMSK |= (0x01 << INT6);  // Enable INT6 interrupts on pin7    
      break;
      
    /* NOTE!!! For INPUT_CAPTURE:
     * Ensure that pins[7,8,9] are already configured as TRIG outputs,
     * and that pin[4] is already configured as an ECHO input.
     */   
    case INPUT_CAPTURE:   
      // Configure Input Capture 1
      TCCR1B |= (0x01 << ICES1);      // Initialize IC1 interrupts on rising edges
      TCCR1B |= (0x01 << ICNC1);      // Enable IC1 noise canceler
      TIMSK1 |= (0x01 << ICIE1);      // Enable IC1 interrupts
      break;

    default:
      Serial.print("ERROR: Init() function arg must be either EXTERNAL_INTERRUPTS or INPUT_CAPTURE\n");
      break;
  }
  
  /* Restore global interrupt flag */
  SREG = sreg;
  INTERRUPT_ENABLE();

  /* Resume all hardware timers */
  GTCCR = 0;
}

//------------------------------------------------------------------------------

unsigned int JSN_Sensor::GetDistance() {
  return this->distance;
}

//------------------------------------------------------------------------------

void JSN_Sensor::Trig() {
  // Indicate that this JSN_Sensor was last to send TRIG signal
  lastTrig = this;

  // Raise specified TRIG pin HIGH for >10us, then reset LOW
  switch(this->trigPin) {
    case 5:
      WRITE_PIN5_HIGH();
      delayMicroseconds(TRIG_PULSE_WIDTH);
      WRITE_PIN5_LOW();
      break;
    case 6:
      WRITE_PIN6_HIGH();
      delayMicroseconds(TRIG_PULSE_WIDTH);
      WRITE_PIN6_LOW();
      break;
    case 7:
      WRITE_PIN7_HIGH();
      delayMicroseconds(TRIG_PULSE_WIDTH);
      WRITE_PIN7_LOW();
    case 8:
      WRITE_PIN8_HIGH();
      delayMicroseconds(TRIG_PULSE_WIDTH);
      WRITE_PIN8_LOW();
      break;
    case 9:
      WRITE_PIN9_HIGH();
      delayMicroseconds(TRIG_PULSE_WIDTH);
      WRITE_PIN9_LOW();
      break;
    default:
      Serial.print("ERROR: Invalid TRIG pin! (Must be one of the following: [5,6,7,8,9])\n");
      break;
  }
}

//------------------------------------------------------------------------------

unsigned int JSN_Sensor::ReadTMR1() {
  unsigned int tmr1;

  /* Save current INT flag states */
  sreg = SREG;
  /* Temporarily disable interrupts */
  INTERRUPT_DISABLE();

  /* Store current value of TMR1 ticks */
  tmr1 = TCNT1;

  /* Restore global interrupt flag */
  SREG = sreg;
  INTERRUPT_ENABLE();

  return tmr1;  // return TMR1 ticks value
}


//==============================================================================
//------------------------ INTERRUPT SERVICE ROUTINES --------------------------
//==============================================================================

/* 
 * If INPUT_CAPTURE hardware system is selected...
 *    then, this ISR will automatically run whenever pin[4] changes state, 
 *    and the TMR1 ticks (at the time of pin state change) is stored into ICR1 
 *  
 * The ISR calculates the distance measurement from the sensor & assigns it to
 * the distance var of the last JSN_Sensor object to call Trig()
 */

ISR(TIMER1_CAPT_vect) {
  // Must temporarily disable interrupts while reading 16-bit registers (ICR1)
  sreg = SREG;
  INTERRUPT_DISABLE();

  switch(READ_PIN4()) {
    case HIGH:
      // If pin[4] is HIGH...
      ticksUp = ICR1;        // store TMR1 ticks at rising edge of ECHO pin

      TCCR1B &= ~(0x01 << ICES1); // set next ISR call to occur on falling edge
      break;

    case LOW:
      // If pin[4] is LOW...
      ticksDown = ICR1;      // store TMR1 ticks at falling edge of ECHO pin

      // Calculate Time-of-Flight (and convert TMR1 ticks to microseconds)
      lastTrig->echoHighTime = ((ticksDown - ticksUp) >> 1);

      // Convert microseconds (ToF) to millimeters (distance from sensor to object)
      lastTrig->distance = (lastTrig->echoHighTime*US_WAVE_SPEED)/(MICROS_PER_MILLI<<1);
      TCCR1B |= (0x01 << ICES1);  // next interrupt on rising edge
      break;
  }
  /* Restore global interrupt flag */
  SREG = sreg;
  INTERRUPT_ENABLE();

  TIFR1 |= (0x01 << ICF1);        // clear interrupt flag
}

//------------------------------------------------------------------------------

/* 
 * If EXTERNAL_INTERRUPTS hardware system is selected...
 *    then, these 3 ISRs will automatically run whenever pins[2,3,7] change
 *    state, and the TMR1 ticks (at the time of pin state change) is stored
 *    into ticksUp or ticksDown
 *  
 * The ISR calculates the distance measurement from the sensor & assigns it to
 * the distance var of the last JSN_Sensor object to call Trig()
 */

ISR(INT1_vect) {
  switch(READ_PIN2()) {
    case HIGH:
      // If pin[2] is HIGH...
      ticksUp = JSN_Sensor::ReadTMR1();   // store TMR1 ticks at rising edge
      break;

    case LOW: 
      // If pin[2] is LOW...
      ticksDown = JSN_Sensor::ReadTMR1(); // store TMR1 ticks at falling edge

      // Calculate & update BOTH: echoHighTime & distance
      lastTrig->echoHighTime = ((ticksDown - ticksUp) >> 1);

      // Convert microseconds (ToF) to millimeters (distance from sensor to object)
      lastTrig->distance = (lastTrig->echoHighTime*US_WAVE_SPEED)/(MICROS_PER_MILLI<<1);
      break;
  }
  EIFR |= (0x01 << INTF1); // clear interrupt flag
}

//------------------------------------------------------------------------------

ISR(INT0_vect) {
  switch(READ_PIN3()) {
    case HIGH:
      // If pin[3] is HIGH...
      ticksUp = JSN_Sensor::ReadTMR1();   // store TMR1 ticks at rising edge
      break;

    case LOW: 
      // If pin[3] is LOW...
      ticksDown = JSN_Sensor::ReadTMR1(); // store TMR1 ticks at falling edge

      // Calculate & update BOTH: echoHighTime & distance
      lastTrig->echoHighTime = ((ticksDown - ticksUp) >> 1);

      // Convert microseconds (ToF) to millimeters (distance from sensor to object)
      lastTrig->distance = (lastTrig->echoHighTime*US_WAVE_SPEED)/(MICROS_PER_MILLI<<1);
      break;
  }
  EIFR |= (0x01 << INTF0); // clear interrupt flag
}

//------------------------------------------------------------------------------

ISR(INT6_vect) {
  switch(READ_PIN7()) {
    case HIGH:
      // If pin[7] is HIGH...
      ticksUp = JSN_Sensor::ReadTMR1();   // store TMR1 ticks at rising edge
      break;
      
    case LOW: 
      // If pin[7] is LOW...
      ticksDown = JSN_Sensor::ReadTMR1(); // store TMR1 ticks at falling edge

      // Calculate & update BOTH: echoHighTime & distance
      lastTrig->echoHighTime = ((ticksDown - ticksUp) >> 1);

      // Convert microseconds (ToF) to millimeters (distance from sensor to object)
      lastTrig->distance = (lastTrig->echoHighTime*US_WAVE_SPEED)/(MICROS_PER_MILLI<<1);
      break;
  }
  EIFR |= (0x01 << INTF6); // clear interrupt flag
}


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
