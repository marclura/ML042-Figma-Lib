/*
  @file ML042FigmaLib.cpp

  Created by Marco Lurati, November 18, 2023
  
  MIT License

  Copyright (c) 2023 marclura

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  
*/

#include <Arduino.h>
#include "ML042FigmaLib.h"

/*!
 * FigmaButton class
 */

/* Constructor */

FigmaButton::FigmaButton(uint8_t _pin, char _key) {
  pin = _pin;
  key_item = _key;
  value = false;
  old_value = false;
  status = 0; // 0: off, 1: pressed (rising edge), 2: on, 3: released (falling edge)
  init();
}

/* Public methods */
bool FigmaButton::off() {
  bool condition = false;
  if(status == 0) condition = true;
  return condition;
}

bool FigmaButton::pressed() {
  bool condition = false;
  if(status == 1) condition = true;
  return condition;
}

bool FigmaButton::on() {
  bool condition = false;
  if(status == 2) condition = true;
  return condition;
}

bool FigmaButton::released() {
  bool condition = false;
  if(status == 3) condition = true;
  return condition;
}

char FigmaButton::key() {
  return key_item;
}

void FigmaButton::update() {
  read();
  if(!old_value && !value) status = 0;  // off
  else if(!old_value && value) {  // pressed (rising edge)
    status = 1;
    old_value = true;
  }
  else if(old_value && value) status = 2; // on
  else if(old_value && !value) {  // released (falling edge)
    status = 3;
    old_value = false;
  }
}

/* Private methods */

void FigmaButton::read() {
  value = digitalRead(pin);
}

void FigmaButton::init() {
  pinMode(pin, INPUT);
}



/*!
 * FigmaPot class
 */

/* Constructor */

FigmaPot::FigmaPot(uint8_t _pin, uint8_t _positions, uint16_t _spread) {
  pin = _pin;
  positions = _positions;
  spread = _spread;
  init();
}

FigmaPot::FigmaPot(uint8_t _pin) {
  pin = _pin;
  init();
}

/* Public methods */
uint16_t FigmaPot::getValue() {
  read();
  return value;
}

void FigmaPot::addPosition(uint8_t _position, uint16_t _value, char _key) {
  positions_values[_position - 1] = _value;
  positions_keys[_position - 1] = _key;
  update();
}

bool FigmaPot::positionChanged() {
  update();
  return position_changed;
}

char FigmaPot::key() {
  return positions_keys[current_position];
}


/* Private methods */
void FigmaPot::update() {
  bool position_found = false;
  position_changed = false;
  read();
  for(uint8_t i=0; i<positions; i++) {  // check if the potentiometer is on a defined position or not
    if(value < (positions_values[i] + spread) && value > (positions_values[i] - spread)) {
      current_position = i;
      if(old_position != current_position) {  // new position detected
        position_changed = true;
        old_position = current_position;
      }
      break;
    }
  }
}

void FigmaPot::read() {
  value = analogRead(pin);
}

void FigmaPot::init() {
  old_position = 255; // init old value out of the possible range
  pinMode(pin, INPUT);
}



/*!
 * FigmaEncoder class
 */

/* Constructor */

FigmaEncoder::FigmaEncoder(uint8_t _pinA, uint8_t _pinB, uint8_t _clicks_per_turn) {
  pinA = _pinA;
  pinB = _pinB;
  clicks_per_turn = _clicks_per_turn;
  init();
}

/* Public methods */

bool FigmaEncoder::clickRight() {

}

bool FigmaEncoder::clickLeft() {

}

void FigmaEncoder::update() {

}

uint16_t FigmaEncoder::angle() {
  return angle_encoder;
}

bool FigmaEncoder::angleChanged() {

}

void FigmaEncoder::addPosition(uint16_t _angle, char _key) {
  
}

char FigmaEncoder::key() {
  return key_encoder;
}


/* Private methods */

void FigmaEncoder::init() {
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
}



/*!
 * FigmaSwitch class
 */

/* Constructor */

FigmaSwitch::FigmaSwitch(uint8_t _pin, char _key0, char _key1) {
  pin = _pin;
  key0 = _key0;
  key1 = _key1;
  changed_flag = false;
  init();
}

/* Public methods */
bool FigmaSwitch::position() {
  return value;
}

char FigmaSwitch::key() {
  char key = '0';
  if(value) key = key1;
  else key = key0;
  return key;
}

bool FigmaSwitch::changed() {
  return changed_flag;
}


void FigmaSwitch::update() {
  read();
  if(old_value != value) {
    old_value = value;
    changed_flag = true;
  }
  else changed_flag = false;
}

/* Private methods */
void FigmaSwitch::read() {
  value = digitalRead(pin);
}

void FigmaSwitch::init() {
  pinMode(pin, INPUT);
  read();
  old_value = value;
}




/*!
 * FigmaLed class
 */

/* Constructor */

FigmaLed::FigmaLed(uint8_t _pin) {
  pin = _pin;
  value = false;
  init();
}

/* Public methods */

void FigmaLed::set(uint8_t _value) {
  value = _value;
  update();
}

void FigmaLed::on() {
  value = true;
  update();
}

void FigmaLed::off() {
  value = false;
  update();
}

void FigmaLed::toggle() {
  value = !value;
  update();
}

/* Private methods */

void FigmaLed::init() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, value);
}

void FigmaLed::update() {
  digitalWrite(pin, value);
}


/*!
 * FigmaLedPWM class
 */

/* Constructor */

FigmaLedPWM::FigmaLedPWM(uint8_t _pin, uint8_t _value, bool _on_at_startup) {
  pin = _pin;
  value = _value;
  old_value = 0;
  on_at_startup = _on_at_startup;
  init();
}

/* Public methods */

void FigmaLedPWM::on(uint8_t _value) {
  old_value = value;
  value = _value;
  update();
}

void FigmaLedPWM::on() {
  value = old_value;
  update();
}

void FigmaLedPWM::off() {
  old_value = value;
  value = 0;
  update();
}

/* Private methods */

void FigmaLedPWM::init() {
  pinMode(pin, OUTPUT);
  if(on_at_startup) {
    analogWrite(pin, value);
  }
}

void FigmaLedPWM::update() {
  analogWrite(pin, value);
}