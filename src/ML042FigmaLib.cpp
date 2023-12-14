/*!
  @file ML042FigmaLib.cpp
  
  @mainpage ML042 Figma Library
  
  @section intro_sec Introduction
  
  Library to use the PCB board ML042 as an HID interface (bluetooth or USB) to control a Figma project with key strokes
  
  @section author Author
  
  Written by Marco Lurati, contact@marcolurati.ch
  
  @section license License
  
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

/**
 * @brief FigmaButton example
 * @example ML042_Figma_Lib_button_demo/ML042_Figma_Lib_button_demo.ino
*/

/**
 * @brief constructor 1
 * 
 * @param _pin  The pin of the board used to connect the button
 * @param _key Key to send as HID for the button
 */

FigmaButton::FigmaButton(uint8_t _pin, char _key) {
  pin = _pin;
  key_item = _key;
  value = false;
  old_value = false;
  status = 0; // 0: off, 1: pressed (rising edge), 2: on, 3: released (falling edge)
  init();
}

/**
 * @brief constructor 2
 * 
 * @param _pin  The pin of the board used to connect the button
 */

FigmaButton::FigmaButton(uint8_t _pin) {
  pin = _pin;
  value = false;
  old_value = false;
  status = 0; // 0: off, 1: pressed (rising edge), 2: on, 3: released (falling edge)
  init();
}

/**
  * @brief Check if the button is not pressed
  * 
  * @return True if the button is not pressed
 */
bool FigmaButton::off() {
  bool condition = false;
  if(status == 0) condition = true;
  return condition;
}

/**
 * @brief Check if the button as been pressed, from not pressed to pressed (rising edge)
 * 
 * @return True if the button as just been pressed
 */
bool FigmaButton::pressed() {
  bool condition = false;
  if(status == 1) condition = true;
  return condition;
}

/**
 * @brief Check if the button is still pressed
 * 
 * @return True if the button is still pressed
 */
bool FigmaButton::on() {
  bool condition = false;
  if(status == 2) condition = true;
  return condition;
}

/**
 * @brief Check if the button as been released, from pressed to not pressed (falling edge)
 * 
 * @return True if the button has been just released
 */
bool FigmaButton::released() {
  bool condition = false;
  if(status == 3) condition = true;
  return condition;
}

/**
 * @brief Get the button key
 * 
 * @return The key for the button
 */
char FigmaButton::key() {
  return key_item;
}

/**
 * @brief Update the status of the button
 * 
 * 0: off, 1: pressed (rising edge), 2: on, 3: released (falling edge)
 */
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

/**
 * @brief Read the pin status
 */
void FigmaButton::read() {
  value = digitalRead(pin);
}

/**
 * @brief Initialize the pin of the button
 */
void FigmaButton::init() {
  pinMode(pin, INPUT);
}


/**
 * @brief FigmaPot example
 * @example ML042_Figma_Lib_potentiometer_demo/ML042_Figma_Lib_potentiometer_demo.ino
*/

/**
 * @brief constructor 1
 * 
 * @param _pin pin used to read the potentiometer
 * @param _positions amount of positions that will be mapped on the patentiometer
 * @param _spread range above and below the defined position that will still be considered as selected
*/
FigmaPot::FigmaPot(uint8_t _pin, uint8_t _positions, uint16_t _spread) {
  pin = _pin;
  positions = _positions;
  spread = _spread;
  init();
}

/**
 * @brief constructor 2
 * 
 * Simple potentiometer definition without any extended functionalities
 * @param _pin pin used to read the potentiometer
*/
FigmaPot::FigmaPot(uint8_t _pin) {
  pin = _pin;
  init();
}

/**
 * @brief Read and return the current value
 * 
 * @return current potentiometer value
*/
uint16_t FigmaPot::getValue() {
  read();
  return value;
}

/**
 * @brief Add a new position to the potentiometer
 * 
 * @param _position position number, counted from left to right
 * @param _value potentimmeter value of the new position
 * @param _key corresponding key of the new position
*/
void FigmaPot::addPosition(uint8_t _position, uint16_t _value, char _key) {
  positions_values[_position - 1] = _value;
  positions_keys[_position - 1] = _key;
  update();
}

/**
 * @brief Check if the position has changed or not
 * 
 * @return True if the position has changed
 * 
*/
bool FigmaPot::changed() {
  update();
  return position_changed;
}

/**
 * @brief Return the corresponding key for that position
 * 
 * @return The key of the current position
*/
char FigmaPot::key() {
  return positions_keys[current_position];
}

/**
 * @brief Update the values and status of the potentiometer
*/
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

/**
 * @brief Read the current value of the potentiometer
*/
void FigmaPot::read() {
  value = analogRead(pin);
}

/**
 * @brief Initialise the potentiometer pin
*/
void FigmaPot::init() {
  old_position = 255; // init old value out of the possible range
  pinMode(pin, INPUT);
}




/**
 * @brief constructor
 * 
 * @param _pin pin used to read the light sensor
*/
FigmaLightSensor::FigmaLightSensor(uint8_t _pin) {
  pin = _pin;
  init();
  update();
}

/**
 * @brief Add a trigger to the light sensor
 * 
 * @param _threshold threshold value used to determinate if the sensor is active or not
 * @param _spread hysteresis effect around the threshold value to avoid the fireing of the key pressed due to the fluctuating nature of the analog reading of the pins
 * @param _keyAbove corresponding key when the current value is above the threshold + spread
 * @param _keyBelow corrresponding key when the current value is below the threshold - spread
*/
void FigmaLightSensor::triggerThreshold(uint16_t _threshold, uint16_t _spread, char _keyAbove, char _keyBelow) {
  threshold = _threshold;
  spread = _spread;
  keyAbove = _keyAbove;
  keyBelow = _keyBelow;
  old_key = '_';
  current_key = '_';
}

/**
 * @brief Update the current value of the light sensor
*/
void FigmaLightSensor::update() {
  value = analogRead(pin);
  if(value > (threshold + spread)) current_key = keyAbove;
  else if (value < (threshold - spread)) current_key = keyBelow;
}

/**
 * @brief Return true if the light intensity changed from the previous threshold side
 * 
 * @return True if the light intensity switched threshold side
*/
bool FigmaLightSensor::changed() {
  bool changed = false;
  if(old_key != current_key) {
    changed = true;
    old_key = current_key;
  }
  return changed;
}

/**
 * @brief Return the current light sensor value
 * 
 * @return The current sensor value
*/
uint16_t FigmaLightSensor::getValue() {
  return value;
}

/**
 * @brief Return the corresponding key for that position
 * 
 * @return the key of the current position
*/
char FigmaLightSensor::key() {
  return current_key;
}

/**
 * @brief Initialise the light sensor by defining the pin
*/
void FigmaLightSensor::init() {
  pinMode(pin, INPUT);
}





/**
 * @brief constructor
 * 
 * Used to manage a witch with two positions, like a rocket switch
 * 
 * @param _pin connection pin to the board
 * @param _key0 key for the position 0 of the switch
 * @param _key1 key for the position 1 of the switch
 */

FigmaSwitch::FigmaSwitch(uint8_t _pin, char _key0, char _key1) {
  pin = _pin;
  key0 = _key0;
  key1 = _key1;
  changed_flag = false;
  init();
}

/**
 * @brief Get the current switch position
 * 
 * It will be 1 or 0
 * @return current switch postion
*/
bool FigmaSwitch::position() {
  return value;
}

/**
 * @brief Check if the switch position has changed
 * 
 * @return True if the switch position has changed
*/
bool FigmaSwitch::changed() {
  return changed_flag;
}

/**
 * @brief Return the correct key according to the current position
 * 
 * @return key of the current position
*/
char FigmaSwitch::key() {
  char key = '0';
  if(value) key = key1;
  else key = key0;
  return key;
}
/**
 * @brief Update the switch status
*/
void FigmaSwitch::update() {
  read();
  if(old_value != value) {
    old_value = value;
    changed_flag = true;
  }
  else changed_flag = false;
}

/**
 * @brief Read the current switch value
*/
void FigmaSwitch::read() {
  value = digitalRead(pin);
}

/**
 * @brief Initialize the pin of the switch and set the initial values
*/
void FigmaSwitch::init() {
  pinMode(pin, INPUT);
  read();
  old_value = value;
}




/**
 * @brief constructor
 * 
 * @param _pin connection pin to the LED
*/
FigmaLed::FigmaLed(uint8_t _pin) {
  pin = _pin;
  value = false;
  init();
}

/**
 * @brief Change the current LED value
 * 
 * @param _value 1 (on) or 0 (off)
*/
void FigmaLed::set(bool _value) {
  value = _value;
  update();
}

/**
 * @brief Switch on the LED
*/
void FigmaLed::on() {
  value = true;
  update();
}

/**
 * @brief Switch off the LED
*/
void FigmaLed::off() {
  value = false;
  update();
}

/**
 * @brief Invert the LED status
 * 
 * If on->off, if off->on
*/
void FigmaLed::toggle() {
  value = !value;
  update();
}

/**
 * @brief Set the LED pin
*/
void FigmaLed::init() {
  pinMode(pin, OUTPUT);
}

/**
 * @brief Update the pin status
*/
void FigmaLed::update() {
  digitalWrite(pin, value);
}



/**
 * @brief constructor
 * 
 * @param _pin connection pin of the LED
 * @param _value initial PWM value of the pin (0-255)
 * @param _on_at_startup true will switch on the LED at startup, false won't
*/
FigmaLedPWM::FigmaLedPWM(uint8_t _pin, uint8_t _value, bool _on_at_startup) {
  pin = _pin;
  value = _value;
  old_value = 0;
  on_at_startup = _on_at_startup;
  init();
}

/**
 * @brief Switch on the LED with the indicated PWM pin value
 * 
 * @param _value PWM pin value (0-255)
*/
void FigmaLedPWM::on(uint8_t _value) {
  old_value = value;
  value = _value;
  update();
}

/**
 * @brief Switch on the LED to the previous on value
*/
void FigmaLedPWM::on() {
  value = old_value;
  update();
}

/**
 * @brief Switch off the LED
*/
void FigmaLedPWM::off() {
  old_value = value;
  value = 0;
  update();
}

/**
 * @brief Set the LED pin
*/
void FigmaLedPWM::init() {
  pinMode(pin, OUTPUT);
  if(on_at_startup) {
    analogWrite(pin, value);
  }
}

/**
 * @brief Update the pin status
*/
void FigmaLedPWM::update() {
  analogWrite(pin, value);
}