/*
  @file ML042_Figma_Lib_LedPWM_demo.ino

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

#include <ML042FigmaLib.h>

FigmaLedPWM led(23, 128, true); // pin, initial value (0-255), on at startup

void setup() {

  Serial.begin(115200);

  Serial.println("Start...");
  delay(2000);

}

void loop() {

  Serial.println("\n---------------------");

  // LED off
  Serial.println("Led off");
  led.off();
  delay(2000);

  // LED on at new value
  Serial.println("Led on at new value (50)");
  led.on(50);
  delay(2000);

  // LED off
  Serial.println("Led off");
  led.off();
  delay(2000);

  // LED on at previous value
  Serial.println("Led on at previous value (50)");
  led.on();
  delay(2000);

  // LED on at new value
  Serial.println("Led on at new value (255)");
  led.on(255);
  delay(2000);

}
