/*!
  @file ML042FigmaLib.h

  @mainpage ML042 Figma Library

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

#ifndef ML042FigmaLib_h
#define ML042FigmaLib_h

#include <Arduino.h>    ///< include arduino.h

/*
 * FigmaButton class
 */
class FigmaButton {
    public:
        FigmaButton(uint8_t _pin, char _key);    // constructor 1
        FigmaButton(uint8_t _pin);  // constructor 2

        bool off();
        bool pressed();
        bool on();
        bool released();
        char key();
        void update();

    protected:
        uint8_t pin;
        char key_item;
        bool value;
        bool old_value;
        uint8_t status; // 0: off, 1: pressed (rising edge), 2: on, 3: released (falling edge)
        void read();
        void init();
};

/*
 * FigmaPot class
 */
class FigmaPot {
    public:
        FigmaPot(uint8_t _pin, uint8_t _positions, uint16_t _spread);  // constructor 1
        FigmaPot(uint8_t _pin); // constructor 2

        uint16_t getValue();
        void addPosition(uint8_t _position, uint16_t _value, char _key);
        bool changed();
        char key();

    protected:
        uint8_t pin;
        uint16_t value;
        uint16_t spread;
        uint8_t positions;
        uint16_t positions_values[20];
        char positions_keys[20];
        uint8_t current_position;
        uint8_t old_position;
        bool position_changed;

        void update();
        void read();
        void init();
};


/*
 * FigmaLightSensor
 */
class FigmaLightSensor {
    public:
        FigmaLightSensor(uint8_t _pin);  // constructor

        void triggerThreshold(uint16_t _threshold, uint16_t _spread, char _keyAbove, char _keyBelow);
        void update();
        bool changed();
        uint16_t getValue();
        char key();
        

    protected:
        uint8_t pin;
        uint16_t value;
        uint16_t spread;
        uint16_t threshold;
        char keyAbove;
        char keyBelow;
        char current_key;
        char old_key;

        void init();

};

/*
 * FigmaSwitch class
 */
class FigmaSwitch {
    public:
        FigmaSwitch(uint8_t _pin, char _key0, char _key1);  // constructor 1
        FigmaSwitch(uint8_t _pin);  // constructor 2

        bool position();
        bool changed();
        char key();
        void update();
    
    protected:
        uint8_t pin;
        char key0;
        char key1;
        bool value;
        bool old_value;
        bool changed_flag;

        void read();
        void init();
};

/*
 * FigmaLed class
 */
class FigmaLed {
    public:
        FigmaLed(uint8_t _pin);  // constructor

        void set(bool _value);
        void on();
        void off();
        void toggle();
    
    protected:
        uint8_t pin;
        bool value;
        void init();
        void update();
};

/*
 * FigmaLed class
 */
class FigmaLedPWM {
    public:
        FigmaLedPWM(uint8_t _pin, uint8_t _value, bool _on_at_startup);  // constructor

        void on();
        void on(uint8_t _value);
        void off();
    
    protected:
        uint8_t pin;
        uint8_t value;
        uint8_t old_value;
        bool on_at_startup;
        void init();
        void update();
};

#endif