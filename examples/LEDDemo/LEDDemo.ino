//
// LED7Seg Demo Example
//
// Copyright (C) 2016 Lennie Araki. All rights reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// This example demonstrates the functionality of the LED7Seg library
// optimized for a 3 or 4 digit display.
//  
// code: 2528 bytes
// data: 110 bytes
//
// It cycles through 5 different modes based on time "counter":
// 
//  0-6.3    Shows graphic segment test (A-F,DP) digit-by-digit
//  6.4-19.9 Shows scrolling text message
//  20-29.9  Shows counter as unsigned hexadecimal number
//  30-39.9  Shows counter as signed X.YY number
//  40-49.9  Shows time in as XX.Y seconds
//
#include "LED7Seg.h"

SevSeg led7seg;        //Instantiate LED7Seg object
#define LED_DIGITS      4

//        D1  A  F D2 D3  B
//      +--o--o--o--o--o--o--+
//      | D4 D5 D6 D7 D8 D9  |
//      |    Arduino Nano    |
//      | A5 A4 A3 A2 A1 A0  |
//      +--o--o--o--o--o--o--+
//         E  D DP  C  G D4
const byte ledPins[] = { /*segA-F+DP=*/ 5, 9, A2, A4, A5, 6, A1, A3, /*dig1-4=*/ 4, 7, 8, A0};

void setup()
{
    led7seg.begin(COMMON_CATHODE, LED_DIGITS, ledPins);
}

void loop()
{
    static unsigned long ten_msec = millis();
    static int counter = 0;
    
    if (millis() >= ten_msec) {
        ten_msec += 100;
        ++counter;
        if (counter < 64)
        {
            int8_t segment = counter & 7;
            int8_t digit = (counter / 8) % LED_DIGITS;
            for (uint8_t d = 0; d < LED_DIGITS; ++d)
            {
                enum led_seg raw[LED_DIGITS];
                raw[d] = (enum led_seg)((d == digit) ?
                    ((SEG_B << segment) - 1) : SEG_NONE);
                led7seg.showRaw(raw);
            }
        }
        else if (counter < 200)
        {
            static const char banner[] = "The Quick Brown Fox Jumped Over The Lazy Dogs 0123456789.";
            const int scroll = ((counter - 64) >> 1) %  (sizeof(banner) - LED_DIGITS);
            led7seg.showText(banner + scroll);
        }
        else if (counter < 300)
        {
            // Display counter in hex dddd
            led7seg.showHex(counter);
        }
        else if (counter < 400)
        {
            const int num = counter - 350;
            // Display encoder value as signed -x.yy
            led7seg.showDecimal(num, 2);
        }
        else if (counter < 500)
        {
            // Display counter as unsigned xxx.y
            led7seg.showNumber(counter, 1);
        }
        else
        {
            // Reset to 0 after 100 seconds
            counter = 0;
        }
    }
//  led7seg.refreshDigits(); // Refresh/multiplex display
    led7seg.refreshSegments(); // Refresh/multiplex display
}
