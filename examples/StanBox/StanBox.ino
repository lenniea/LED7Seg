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
//
// This example demonstrates the functionality of the LED7Seg library
// optimized for a 3 or 4 digit display.
//  
// It cycles through 4 different modes based on time "counter":
// 
//  0-19.9   Shows graphic segment test (A-F,DP) digit-by-digit
//  20-39.9  Shows scrolling text message
//  40-59.9  Shows encoder as signed X.YY number
//  60-79.9  Shows counter as unsigned hexadecimal number
//  80-99.9  Shows time in as XX.Y seconds
//
#include "LED7Seg.h"

#define LEDFONT

using namespace LED;

SevSeg led7seg;        //Instantiate LED7Seg object
#define LED_DIGITS      4

// Arduino UNO
//const byte ledPins[] = { /*segA-F+DP=*/ 2, 3, 4, 5, 6, 7, 8, 9, /*dig1-4=*/ 10, 11, 12, 13};

//		  D1  A  F D2 D3  B
//      +--o--o--o--o--o--o--+
//		| D4 D5 D6 D7 D8 D9  |
//		|    Arduino Nano    |
//      | A5 A4 A3 A2 A1 A0  |
//      +--o--o--o--o--o--o--+
//         E  D DP  C  G D4
const byte ledPins[] = { /*segA-F+DP=*/ 5, 9, A2, A4, A5, 6, A1, A3, /*dig1-4=*/ 4, 7, 8, A0};

void setup()
{
    led7seg.begin(COMMON_CATHODE, LED_DIGITS, ledPins);
	
    pinMode(A6, INPUT);
    pinMode(A7, INPUT);
    digitalWrite(A6, HIGH);		// Turn on pullup for A6
    digitalWrite(A7, HIGH);		// Turn on pullup for A7
}

uint8_t old_AB;
const int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

/* returns change in encoder state (-1,0,1) */
int8_t read_encoder()
{
	// remember previou state and ORin new state
	old_AB = (old_AB << 2) | (PINC & 0x03); //remember previous state
	return enc_states[old_AB & 0x0f];
}

void loop()
{
	static unsigned long ten_msec = millis();
	static int counter = 0;
	static int encoder = 0;
	
//	int pot = analogRead(0);
	encoder += read_encoder();

	if (millis() >= ten_msec) {
		ten_msec += 100;
		++counter;
		if (counter < 200)
		{
			int segment = counter & 7;
			int digit = (counter / 8) % LED_DIGITS;
			for (byte d = 0; d < LED_DIGITS; ++d)
			{
				byte raw[LED_DIGITS];
				raw[d] = (d == digit) ?
					((SEG_B << segment) - 1) : SEG_NONE;
				led7seg.showRaw(raw);
			}
		}
#ifdef LEDFONT
		else if (counter < 400)
		{
			static const char banner[] = "The Quick Brown Fox Jumped Over The Lazy Dogs 0123456789.";
			const int scroll = ((counter - 200) >> 1) %  (sizeof(banner) - LED_DIGITS);
			led7seg.showText(banner + scroll);
		}
#endif
		else if (counter < 600)
		{
			// Display encoder value as signed -x.yy
			led7seg.showDecimal(encoder >> 2, 2);
		}
		else if (counter < 800)
		{
			// Display counter in hex dddd
			led7seg.showHex(counter);
		}
		else if (counter < 1000)
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
//	led7seg.refreshDigits(); // Refresh/multiplex display
	led7seg.refreshSegments(); // Refresh/multiplex display
}
