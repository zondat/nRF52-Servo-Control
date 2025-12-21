/****************************************************************************************************************************
  NRF52_ISR_Servo.hpp
  For :
  - nRF52832-based boards such as AdaFruit Feather nRF52832, 
  - nRF52840-based boards such as Adafruit nRF52840 Express, Itsy-Bitsy nRF52840 Express, NINA_B302_ublox, etc.
  
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/NRF52_ISR_Servo
  Licensed under MIT license

  Version: 1.2.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      22/08/2021 Initial coding for nRF52832/nRF52840 boards
  1.1.0   K Hoang      03/03/2022 Convert to `h-only` style. Optimize code. Add support to `Sparkfun Pro nRF52840 Mini`
  1.2.0   K Hoang      23/04/2022 Permit using servos with different pulse ranges simultaneously. Delete left-over `cpp`
  1.2.1   K Hoang      26/10/2022 Add support to Seeed_XIAO_NRF52840 and Seeed_XIAO_NRF52840_SENSE
 *****************************************************************************************************************************/

#pragma once

#ifndef NRF52_Servo_HPP
	#define NRF52_Servo_HPP

////////////////////////////////////////

#if !(defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || \
      defined(NRF52840_CLUE) || defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || \
      defined(NRF52840_LED_GLASSES) || defined(MDBT50Q_RX) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) || \
      defined(ARDUINO_Seeed_XIAO_nRF52840) || defined(ARDUINO_Seeed_XIAO_nRF52840_Sense) )
  #error This code is designed to run on Adafruit or Seeed nRF52 platform! Please check your Tools->Board setting.
#endif


////////////////////////////////////////

#include "Arduino.h"
#include <Adafruit_TinyUSB.h>
#include <stddef.h>
#include <inttypes.h>

#if defined(ARDUINO)
  #if ARDUINO >= 100
    #include <Arduino.h>
  #else
    #include <WProgram.h>
  #endif
#endif



////////////////////////////////////////

// From Servo.h - Copyright (c) 2009 Michael Margolis.  All right reserved.

#define MIN_PULSE_WIDTH         800       // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH         2000      // the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH     1500      // default pulse width when servo is attached
#define REFRESH_INTERVAL        20000     // minumim time to refresh servos in microseconds 

////////////////////////////////////////

/**
 * NRF52 Only definitions
 * ---------------------
 */
//PWM_PRESCALER_PRESCALER_DIV_128 -> NRF_PWM_CLK_125kHz -> resolution 8µs
//MaxValue = 2450 -> PWM period = 20ms
//20ms - 50Hz
#define DUTY_CYCLE_RESOLUTION     8
#define MAXVALUE                  MAX_PULSE_WIDTH
#define CLOCKDIV                  PWM_PRESCALER_PRESCALER_DIV_128

////////////////////////////////////////
#define SERVO_TOKEN 0x76726553

class NRF52_Servo
{
  public:
    NRF52_Servo(){}
    virtual ~NRF52_Servo() { 
      if (hardware_pwm != nullptr) {
        hardware_pwm->releaseOwnership(SERVO_TOKEN);
        hardware_pwm = nullptr;
      }
    }
    bool init(const uint8_t pin);
    void write(uint16_t value);
    void writeMicroseconds(uint16_t value);
    void setMaxPulseUs(uint16_t maxPulseUs) {this->maxPulseUs=maxPulseUs; }
    void setMinPulseUs(uint16_t minPulseUs) {this->minPulseUs=minPulseUs; }
    bool isEnabled() {return enable;}
    uint16_t get_current_value(){return current_value;}

  private:
    HardwarePWM* hardware_pwm = nullptr;
    bool enable = false;
    uint8_t pin;
    uint16_t current_value = 0, maxPulseUs = MAX_PULSE_WIDTH, minPulseUs = MIN_PULSE_WIDTH;
};

////////////////////////////////////////

#endif    // NRF52_Servo_HPP
