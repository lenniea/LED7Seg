//
// Robotics PWM Motor Controller
//
// Copyright (C) 2016-2020 Lennie Araki. All rights reserved
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
// This example creates a PWM output on pin D10 compatible with Talon, TalonSRX 
// and SparkMax FRC motor controllers
//
// User input is set using a quadrature rotary encoder on D2-D3 and pushbutton
// on D0.
//
// Values are output on the 4-digit 7-segment LED display.
//
// Power is -1.00..+1.00 corresponding to:
//     1.0 msec (full rev)
//     1.5 msec (stop)
//     2.0 msec (full fwd)
//
#include "LED7Seg.h"
#include <Servo.h>

#define LEDFONT

#define MODE_PIN        0     // RXD
#define ENC_PIN         2     // Pins D2 & D3
#define PWM_OUT         10

#define MIN_POWER       -100  // -100%
#define MAX_POWER       +100  // +100%

SevSeg led7seg;        //Instantiate LED7Seg object
#define LED_DIGITS      4

Servo pwmOut;

//           BUT     GND ENA ENB                         PWM
//            |       |   |   |                           |
//            |       |   |   |  D1   A   F  D2  D3   B   |
//      +-o---o---o---o---o---o---o---o---o---o---o---o---o---o---o-+
//	    |TX0 RX1 RST GND D2  D3| D4  D5  D6  D7  D8  D9| D10 D11 D12|
//	    |                      |     Arduino Nano      |            |
//      |VIN GND RST 5V  A7  A6| A5  A4  A3  A2  A1  A0|REF 3V3 D13 |
//      +-o---o---o---o---o---o---o---o---o---o---o---o---o---o---o-+
//        |   |       |   |   |  E   D  DP   C   G  D4
//        |   +--POT--+   |   |
//        |   |   A       |   |
//       20K 10K  +-------+   |
//        |   |               |
//        +---+---------------+
const byte ledPins[] = { /*segA-F+DP=*/ 5, 9, A2, A4, A5, 6, A1, A3, /*dig1-4=*/ 4, 7, 8, A0};

void setup()
{
    Serial.begin(57600);
    pinMode(MODE_PIN, INPUT_PULLUP);

    analogReference(DEFAULT);
    led7seg.begin(COMMON_CATHODE, LED_DIGITS, ledPins);
	  pinMode(LED_BUILTIN, OUTPUT);
    pinMode(A6, INPUT_PULLUP);
    pinMode(A7, INPUT_PULLUP);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    digitalWrite(2, HIGH);    // Turn on pullup for D2
    digitalWrite(3, HIGH);    // Turn on pullup for D3

    pwmOut.attach(PWM_OUT);
}

uint8_t old_AB;
const int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

/* returns change in encoder state (-1,0,1) */
int8_t read_encoder()
{
	// remember previous state and ORin new state
  uint8_t enc_bits = (PIND >> ENC_PIN) & 0x03;
	old_AB = (old_AB << 2) | enc_bits; //remember previous state
	return enc_states[old_AB & 0x0f];
}

int counter = 0;
int16_t analogin = 0;

static unsigned long ten_msec = millis();

void splash()
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

uint8_t dispMode = 0;

void loop()
{
	static int encoder = 0;
	
	encoder += read_encoder();
  // Cap value to -100..+100 (logical range)
  if (encoder < MIN_POWER * 4) {
    encoder = MIN_POWER * 4;
  } else if (encoder > MAX_POWER * 4) {
    encoder = MAX_POWER * 4;
  }

  // Blink LED to show activity
  if (counter % 10 < 5) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

	if (millis() >= ten_msec) {
		ten_msec += 100;
		counter = (counter + 1) % 1000;
    analogin = analogRead(7);
   
    static int8_t oldMode = 1;
    int8_t mode_pin = digitalRead(MODE_PIN) ? 1 : 0;
    // Detect falling edge on MODE_PIN
    if ((oldMode ^ mode_pin) && !mode_pin)
    {
       Serial.print("mode=");
       dispMode = (dispMode + 1) % 3;
       Serial.println(dispMode);
       counter = 0;
    }
    oldMode = mode_pin;


    if (dispMode == 0) {
      // Display encoder value as signed -x.yy
      int16_t power = encoder >> 2;
//      int16_t power = counter * 2 - 100;
      led7seg.showDecimal(power, 2);
      //               _______
      // FullRev  ____}       |_________________________|
      //                _______________                  
      // Stop      ____|               |________________|
      //                 _______________________         
      // FullFwd    ____|                       |_______|
      //
      int16_t usec = power * 5 + 1500;
      pwmOut.writeMicroseconds(usec);
    } else if (dispMode == 1) {
      // Display analog input as decimal
      Serial.print("in=");
      Serial.println(analogin);
      led7seg.showDecimal(analogin, 0);
    } else {
      splash();
    }
	}
	led7seg.refreshSegments(); // Refresh/multiplex display
}
