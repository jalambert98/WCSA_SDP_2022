/* 
 * File:            JSN_SensLib.cpp
 * Author:          Jack Lambert <joalambe@ucsc.edu>
 * Project:         White Cane Sensor Attachment
 * Course:          UCSC ECE129 - SDP '21
 *
 * Created:         January 12, 2022, 1:35 PM
 * Last Modified:   January 15, 2022, 8:55 PM
 */

 #include "Arduino.h"
 #include "JSN_SensLib.h"
 
//==============================================================================
//-------------------------------- #DEFINES ------------------------------------
//==============================================================================

#define US_WAVE_SPEED       340     // speed of ultrasonic wave = 340[m/s]
#define MICROS_PER_MILLI    1000


//==============================================================================
//---------------------------- STATICS VARIABLES -------------------------------
//==============================================================================
      
static volatile unsigned long timeUp[3], timeDown[3], echoHighTime[3]; // in microseconds
static volatile unsigned int distance[3];                              // in millimeters
static volatile uint8_t echoSet[3];                                    // 0 or 1
static uint8_t sel_sys;


//==============================================================================
//-------------------------------- CONSTRUCTOR ---------------------------------
//==============================================================================

JSN_SensLib::JSN_SensLib(uint8_t SYSTEM_USING) {
  sel_sys = SYSTEM_USING;
  /* Save current INT flag states */
  unsigned char sreg = SREG;
  /* Temporarily disable interrupts */
  INTERRUPT_DISABLE();

  switch(SYSTEM_USING) {
    case EXTERNAL_INTERRUPTS:
      // Configure TRIG pins as MCU outputs
      SET_PIN5_OUT();   // pin5 --> TRIG1
      SET_PIN6_OUT();   // pin6 --> TRIG2
      SET_PIN8_OUT();   // pin8 --> TRIG3
    
      // Initialize TRIG pins LOW
      WRITE_PIN5_LOW();
      WRITE_PIN6_LOW();
      WRITE_PIN8_LOW();
    
      // Configure ECHO pins as MCU inputs
      SET_PIN2_IN();    // pin2 <-- ECHO1
      SET_PIN3_IN();    // pin3 <-- ECHO2
      SET_PIN7_IN();    // pin7 <-- ECHO3
    
      // Configure ECHO pins to run ISR each pin value CHANGE
      EIMSK = 0x00;     // Clear interrupt mask reg
      EICRA = 0x00;     // Clear ext interrupt control reg A
      EICRB = 0x00;     // Clear ext interrupt control reg B
      EIFR = 0x00;      // Clear any existing ext interrupt flags

      EICRA |= (0x01 << ISC10); // INT1 ext interrupts on rising & falling edges
      EICRA |= (0x01 << ISC00); // INT0 ext interrupts on rising & falling edges
      EICRB |= (0x01 << ISC60); // INT6 ext interrupts on rising & falling edges

      EIMSK |= (0x01 << INT1);  // Enable INT1 interrupts on pin2
      EIMSK |= (0x01 << INT0);  // Enable INT0 interrupts on pin3
      EIMSK |= (0x01 << INT6);  // Enable INT6 interrupts on pin7
            
      break;
      
    case INPUT_CAPTURE:      
      // Configure directions for TRIG & ECHO pins
      SET_PIN7_OUT();     // pin7 --> trig1
      SET_PIN8_OUT();     // pin8 --> trig2
      SET_PIN9_OUT();     // pin9 --> trig3

      WRITE_PIN7_LOW();
      WRITE_PIN8_LOW();
      WRITE_PIN9_LOW();

      SET_PIN4_IN();      // pin4 --> ECHO (shared)
      
      // Configure TMR1 & Input Capture 1
      TCCR1A = 0x00;                    // clear TMR1 control reg A
      TCCR1B = 0x00;                    // clear TMR1 control reg B
      TIMSK1 = 0x00;                    // clear TMR1 interrupt mask reg
      TIFR1 = 0x00;                     // clear existing TMR1 interrupt flags
      ICR1 = 0x0000;                    // clear IC1 reg

      TCCR1B |= (1 << CS01);            // Use 1:8 prescalar (TMR1 ticks @2MHz)
      TCCR1B |= (1 << ICES1);           // initialize IC1 interrupts on rising edges
      TIMSK1 |= (1 << ICIE1);           // enable IC1 interrupts

      break;

    default:
      // ERROR
      break;
  }
  
  MCUCR |= (0x01 << PUD);   // disable pullup resistors

  // Initialize static vars
  uint8_t i = 0;
  for(i=0; i<3; i++) {
    echoSet[i] = 0;
    echoHighTime[i] = 0;
    timeUp[i] = 0;
    timeDown[i] = 0;
    distance[i] = 0;
  }
  
  /* Restore global interrupt flag */
  SREG = sreg;
  INTERRUPT_ENABLE();
  
}


//==============================================================================
//----------------------------- FUNCTION LIBRARY -------------------------------
//==============================================================================

unsigned int JSN_SensLib::GetDistance(uint8_t sens) {
  distance[sens-1] = JSN_SensLib::TOF_mm(echoHighTime[sens-1]);
  return distance[sens-1];
}

//------------------------------------------------------------------------------

void JSN_SensLib::Trig(uint8_t sens) {
  // Raise specified TRIG pin HIGH for 10us, then reset LOW
  switch(sel_sys) {
    case EXTERNAL_INTERRUPTS:
      switch(sens) {
        case 1:
          WRITE_PIN5_HIGH();
          delayMicroseconds(11);
          WRITE_PIN5_LOW();
          break;
        case 2:
          WRITE_PIN6_HIGH();
          delayMicroseconds(11);
          WRITE_PIN6_LOW();
          break;
        case 3:
          WRITE_PIN8_HIGH();
          delayMicroseconds(11);
          WRITE_PIN8_LOW();
          break;
      }
      break;

    case INPUT_CAPTURE:
      switch(sens) {
        case 1:
          WRITE_PIN7_HIGH();
          delayMicroseconds(11);
          WRITE_PIN7_LOW();
          break;
        case 2:
          WRITE_PIN8_HIGH();
          delayMicroseconds(11);
          WRITE_PIN8_LOW();
          break;
        case 3:
          WRITE_PIN9_HIGH();
          delayMicroseconds(11);
          WRITE_PIN9_LOW();
          break;
      }
    break;
  }
}

//------------------------------------------------------------------------------

unsigned int JSN_SensLib::TOF_mm(unsigned long tofMicro) {
  return (tofMicro*US_WAVE_SPEED)/(MICROS_PER_MILLI<<1);
}

//------------------------------------------------------------------------------

unsigned int JSN_SensLib::ReadTMR1() {
  unsigned char sreg;
  unsigned int tmr1;

  /* Save current INT flag states */
  sreg = SREG;
  /* Temporarily disable interrupts */
  INTERRUPT_DISABLE();

  /* Store TCNT1 (TMR1 register) value in tmr1 */
  tmr1 = TCNT1;
  /* Restore global interrupt flag */
  SREG = sreg;
  INTERRUPT_ENABLE();

  return tmr1;
}


//==============================================================================
//------------------------ INTERRUPT SERVICE ROUTINES --------------------------
//==============================================================================

ISR(TIMER1_CAPT_vect) {
  switch(READ_PIN4()) {
    case 1:
      timeUp[0] = ICR1;
      TCCR1B &= ~(1 << ICES1);  // next interrupt on falling edge
      break;
    case 0:
      timeDown[0] = ICR1;
      echoHighTime[0] = timeDown[0] - timeUp[0];
      TCCR1B |= (1 << ICES1);   // next interrupt on rising edge
      break;
    }

}

//------------------------------------------------------------------------------

ISR(INT1_vect) {
  // If ECHO1 pin is currently HIGH, but was previously LOW...
  switch(READ_PIN2()) {
    case 1:
      timeUp[0] = micros();
      break;
    case 0:
      timeDown[0] = micros();
      echoHighTime[0] = timeDown[0] - timeUp[0];
      Serial.print(echoHighTime[0]);
      break;
  }
  EIFR |= (0x01 << INTF1); // clear interrupt flag
}

//------------------------------------------------------------------------------

/*ISR(INT0_vect) {
  // If ECHO2 pin is currently HIGH, but was previously LOW...
  if (READ_PIN3() == HIGH) {
    if (echoSet[1] == 0) {
      //...indicate that it was set high & store current micros()
      echoSet[1] = 1;
      timeUp[1] = micros();
    }
  }
  // If ECHO2 pin is currently LOW, but was previously HIGH...
  else if (READ_PIN3() == LOW) {
    if (echoSet[1] == 1) {
      //...indicate that it was set low & store current micros()
      echoSet[1] = 0;
      timeDown[1] = micros();

      // Then calculate ToF & convert to mm distance
      echoHighTime[1] = timeDown[1] - timeUp[1];
    }
  }
}

//------------------------------------------------------------------------------

ISR(INT6_vect) {
  // If ECHO3 pin is currently HIGH, but was previously LOW...
  if (READ_PIN7() == HIGH) {
    if (echoSet[2] == 0) {
      //...indicate that it was set high & store current micros()
      echoSet[2] = 1;
      timeUp[2] = micros();
    }
  }
  // If ECHO3 pin is currently LOW, but was previously HIGH...
  else if (READ_PIN7() == LOW) {
    if (echoSet[2] == 1) {
      //...indicate that it was set low & store current micros()
      echoSet[2] = 0;
      timeDown[2] = micros();

      // Then calculate ToF & convert to mm distance
      echoHighTime[2] = timeDown[2] - timeUp[2];
    }
  }
}*/


//==============================================================================
//--------------------------------END OF FILE-----------------------------------
//==============================================================================
