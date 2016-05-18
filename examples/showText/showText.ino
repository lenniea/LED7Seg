//
// LED7Seg showText Example
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
// This example demonstrates the showText() function of the LED7Seg library.
//
// code: 1820 bytes
// data: 208 bytes
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
		static const char banner[] = "The Quick Brown Fox Jumped Over The Lazy Dogs 0123456789.";
		const int scroll = ((counter - 200) >> 1) %  (sizeof(banner) - LED_DIGITS);
		led7seg.showText(banner + scroll);
    }
//  led7seg.refreshDigits(); // Refresh/multiplex display
    led7seg.refreshSegments(); // Refresh/multiplex display
}
