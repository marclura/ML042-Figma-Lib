/*
  @file ML042_Figma_Lib_potentiometer_demo.ino

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

#include <ML042_Figma_Lib.h>

FigmaPot pot_mapped(13, 4, 200);  // constructor 1, mapped potentiometer: pin, positions, spread
FigmaPot pot_simple(2);  // constructor 2, simple pot without any key functions

char pot_mapped_last_position = '-';

void setup() {

  Serial.begin(115200);

  // Mapped potentimeter: add the positions
  pot_mapped.addPosition(1, 512, 'A');
  pot_mapped.addPosition(2, 1536, 'B');
  pot_mapped.addPosition(3, 2560, 'C');
  pot_mapped.addPosition(4, 3583, 'D');

}


void loop() {

  Serial.println("\n-------------------------");

  // Simple potentiometer
  Serial.println("Simple pot value: " + String(pot_simple.getValue()));

  // Mapped potentiometer
  Serial.println("Mapped pot value: " + String(pot_mapped.getValue()));
  if(pot_mapped.positionChanged()) {
    Serial.print("-> New position: ");
    pot_mapped_last_position = pot_mapped.key();
    Serial.println(pot_mapped_last_position);
    delay(3000);
  } else {
    Serial.println("Old position: " + String(pot_mapped_last_position));
  }
  
  delay(100);

}