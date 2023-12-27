/*
  @file ML042_Figma_Lib_LightSensor_demo.ino

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

FigmaLightSensor sensor(13);

byte old_key = ' ';

void setup() {
    Serial.begin(115200);

    sensor.triggerThreshold(512, 100, 'a', 'b');
}

void loop() {

    // read the sensor
    sensor.update();

    Serial.println("Sensor value" + String(sensor.getValue()));

    if(sensor.changed()) {
        byte current_key = sensor.key();

        if(old_key != current_key) {
            Serial.println("New key: " + String(current_key));
            old_key = sensor.key();
        }
    }

    delay(100);
}