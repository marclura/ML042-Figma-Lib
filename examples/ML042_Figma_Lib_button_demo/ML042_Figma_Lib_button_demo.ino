/*
  @file ML042_Figma_Lib_Button_demo.ino

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

FigmaButton button(2, 'b'); // pin, key

void setup() {
  Serial.begin(115200);
}

void loop() {

  // mandatory! Update the button status
  button.update();
  
  // button off
  if(button.off()) Serial.println("Button off");

  // button pressed
  else if(button.pressed()) {
    Serial.print("Button pressed, key: ");
    Serial.println(button.key());
  }

  // button on
  else if(button.on()) Serial.println("Button on");

  // button released
  else if(button.released()) Serial.println("Button released");

  // small delay between readings of the button
  delay(100);

}
