/*
  @file ML042_Figma_Lib_Switch_demo.ino

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

// Important! Don't use "switch" as a variable name, because it is already reserved as switch() function
FigmaSwitch rocket_switch(2, 'L', 'R');  // pin, key position 1, key position 2


void setup() {

  Serial.begin(115200);

  Serial.print("Switch initial position: " + String(rocket_switch.position()));
  Serial.println(", key: " + String(rocket_switch.key()));

}

void loop() {

  // Mandatory! Update the switch status at every loop
  rocket_switch.update();

  if(rocket_switch.changed()) {
    Serial.println("\nSwitch changed!");
    Serial.print("Switch position: " + String(rocket_switch.position()));
    Serial.println(", key: " + String(rocket_switch.key()));
  }

  delay(20);

}
