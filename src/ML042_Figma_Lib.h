/*
  @file ML042_Figma_Lib.h

  ----------------------------------------------------------------------------------
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

#ifndef ML042_Figma_Lib_h
#define ML042_Figma_Lib_h

#include <Arduino.h>

/*!
 * FigmaButton class
 */
class FigmaButton {
    public:
        /*!
        * FigmaButton Datatype declaration Class Constructor
        * @class
        * @param {number} _pin - connection pin
        * @param {char} _key - key to press
        */
        FigmaButton(uint8_t _pin, char _key);    // constructor
    
        /*!
        * Check if the button is not pressed
        * @method
        * @return {boolean} button not pressed
        */
        bool off();

        /*!
        * Check if the button as been pressed, from not pressed to pressed (rising edge)
        * @method
        * @return {boolean} button just pressed
        */
        bool pressed();

        /*!
        * Check if the button is still pressed
        * @method
        * @return {boolean} button still pressed
        */
        bool on();

        /*!
        * Check if the button as been released, from pressed to not pressed (falling edge)
        * @method
        * @return {boolean} button just released
        */
        bool released();

        /*!
        * Get the button key
        * @method
        * @return {char} key of the button
        */
        char key();

    protected:
        uint8_t pin;
        char key;
        bool value;
        bool old_value;
        uint8_t status; // 0: off, 1: pressed (rising edge), 2: on, 3: released (falling edge)

        /*!
        * Update the status of the button, 0: off, 1: pressed (rising edge), 2: on, 3: released (falling edge)
        * @method
        */
        void update();

        /*!
        * Read the button pin
        * @method
        */
        void read();

        /*!
        * Initialize the pin of the button
        * @method
        */
        void init();

};

/*!
 * FigmaPot class
 */
class FigmaPot {
    public:
        /*!
        * FigmaPot Datatype declaration Class Constructor
        * @class
        * @param {number} _pin - connection pin
        */
        FigmaPot(uint8_t _pin);  // constructor

        /*!
        * Read and return the value
        * @method
        */
        uint16_t read();
        
    protected:
        uint8_t pin;
        uint16_t value;
        void init();
};

/*!
 * FigmaEncoder class
 */
class FigmaEncoder {
    public:
        /*!
        * FigmaEncoder Datatype declaration Class Constructor
        * @class
        * @param {number} _pin - connection pin
        */
        FigmaEncoder(uint8_t _pinA, uint8_t _pinB);  // constructor
    
    protected:
        uint8_t pinA;
        uint8_t pinB;
        void init();
};

/*!
 * FigmaSwitch class
 */
class FigmaSwitch {
    public:
        /*!
        * FigmaSwitch Datatype declaration Class Constructor
        * @class
        * @param {number} _pin - connection pin
        */
        FigmaSwitch(uint8_t _pin, char _key0, char _key1);  // constructor

        /*!
        * Get the current switch position, 0 or 1
        * @method
        * @return {boolean} siwtch position
        */
        bool position();

        /*!
        * Check if the switch position has changed
        * @method
        * @return {boolean} switch position has changed
        */
        bool changed();

        /*!
        * Get the current key according to the current position
        * @method
        * @return {char} current key according to the current position
        */
        char key();
    
    protected:
        uint8_t pin;
        char key0;
        char key1;
        bool value;
        bool old_value;
        bool changed_flag;

        /*!
        * Update the switch status
        * @method
        */
        void update();

        /*!
        * Read the current switch value, 0 or 1
        * @method
        */
        void read();

        /*!
        * Initialize the pin of the switch and set the initial values
        * @method
        */
        void init();
};

/*!
 * FigmaLed class
 */
class FigmaLed {
    public:
        /*!
        * FigmaLed Datatype declaration Class Constructor
        * @class
        * @param {number} _pin - connection pin
        */
        FigmaLed(uint8_t _pin);  // constructor

        /*!
        * Change the current LED value, works both for analog and digital pins
        * @method
        * @param {number} value - 0 to 255, for digital 0 or 1, for analog 0 to 255
        */
        void value(uint8_t _value);

        /*!
        * Switch on the LED
        * @method
        */
        void on();

        /*!
        * Switch off the LED
        * @method
        */
        void off();

        /*!
        * Switch off the LED
        * @method
        */
        void blink(uint16_t _time);
    
    protected:
        uint8_t pin;
        uint8_t value;
        uint16_t time;
        void init();
        void update();
};

/*!
 * FigmaLed class
 */
class FigmaLedPWM {
    public:
        /*!
        * FigmaLedPWM Datatype declaration Class Constructor
        * @class
        * @param {number} _pin - connection pin
        */
        FigmaLedPWM(uint8_t _pin, uint8_t _value);  // constructor

        /*!
        * Change the current LED value, works both for analog and digital pins
        * @method
        * @param {number} value - 0 to 255, for digital 0 or 1, for analog 0 to 255
        */
        void value(uint8_t _value);

        /*!
        * Switch on the LED
        * @method
        */
        void on();

        /*!
        * Switch off the LED
        * @method
        */
        void off();

    
    protected:
        uint8_t pin;
        uint8_t value;
        uint8_t old_value;
        void init();
        void update();
};

#endif