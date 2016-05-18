///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
/// http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
#include "LED7Seg.h"

/// Constructor
SevSeg::SevSeg()
{
    m_index = 0;
    m_digits = 0;
}

/// Initialization function
/// @param  conf        Bit mask (Bit0, Bit1..Bit m_digits)
/// @param  digits      Number of digits (typically 1-4)
/// @param  pins        Output pin array
void SevSeg::begin(enum led_config conf, uint8_t digits, const uint8_t* pins)
{
    m_config = conf;
    m_digits = digits;
    m_pins = pins;
    

    // Set all pins as outputs
    for (uint8_t i=0 ; i < SEGMENTS + digits; ++i)
    {
        int pin = m_pins[i];
        pinMode(pin, OUTPUT);
    }

    // Turn all digits off
    setDigits(DIG_NONE);
    // Turn all segments off
    setSegments(SEG_NONE);

    m_last = millis();
}

///
/// Set all LED segment pins based on mask
/// @param  mask    Bit mask (SEG_A,SEG_B,SEG_C,SEG_D,SEG_E,SEG_F,SEG_G,SEG_DP)
///
void SevSeg::setSegments(enum led_seg mask)
{
    if (m_config & SEG_INVERT)
        mask = (enum led_seg)(~mask);
    for (uint8_t i = 0; i < SEGMENTS; ++i)
    {
        boolean pinState = (mask & 0x01);
        int pin = m_pins[i];
        digitalWrite(pin, pinState);
        mask = (enum led_seg) (mask >> 1);
    }
}

///
/// Set LED Digit pins based on mask.
/// @param  mask    Bit mask (DIG_0..DIG_n-1)
///
void SevSeg::setDigits(enum led_dig mask)
{
    if (m_config & DIG_INVERT)
        mask = (enum led_dig)(~mask);
    for (uint8_t i = 0; i < m_digits; ++i)
    {
        boolean pinState = (mask & 0x01);
        int pin = m_pins[i + SEGMENTS];
        digitalWrite(pin, pinState);
        mask = (enum led_dig)(mask >> 1);
    }
}

///
/// Refresh/multiplex all the digits on the LED Display.  Use this method
/// when the current limiting resistors are in series with the segment pins.
///
void SevSeg::refreshDigits()
{
    unsigned long now = millis();
    if (now != m_last)
    {
        m_last = now;
        // Turn off all digits
        setDigits(DIG_NONE);
        // Increment m_index modulo m_digits
        uint8_t index = m_index + 1;
        if (index >= m_digits)
            index = 0;
        m_index = index;
        // Set segments for digit
        setSegments(m_buf[index]);
        // Turn on one digit at a time
        setDigits((enum led_dig)(DIG_0 << index));
    }
}

///
/// Refresh/multiplex all the segments on the LED Display.  Use this method
/// when the current limiting resistors are in series with the digit pins.
///
void SevSeg::refreshSegments()
{
    unsigned long now = millis();
    if (now != m_last)
    {
        enum led_dig digitMask = DIG_NONE;
        enum led_seg segMask;
        
        m_last = now;
        // Turn off all digits
        setDigits(DIG_NONE);
        // Increment m_index modulo m_digits
        uint8_t index = m_index + 1;
        if (index >= SEGMENTS)
            index = 0;
        m_index = index;
        // Turn on one segment at a time
        segMask = (enum led_seg)(SEG_A << index);
        setSegments(segMask);
        // Determines digits containing segment
        for (uint8_t dig = 0; dig < MAX_DIGITS; ++dig)
        {
            if (m_buf[dig] & segMask)
            {
                digitMask =  (enum led_dig)(digitMask | (DIG_0 << dig));
            }
        }
        // Set segment for digit(s)
        setDigits(digitMask);
    }
}

enum led_seg getHexDigit(int num, uint8_t shift)
{
    enum led_seg mask = LED_HexFont[(num >> shift) & 15];
    return mask;
}

///
/// Show number as hexadecimal right justified on the LED display
/// @param num     Number to display
///
void SevSeg::showHex(unsigned long num)
{
    char str[MAX_DIGITS+1];
    str[MAX_DIGITS] = '\0';
    for (uint8_t d = 0; d < m_digits; ++d)
    {
        m_buf[m_digits - 1 - d] = getHexDigit(num, 4 * d);
    }
}

///
/// Show number as unsigned decimal with [optional] decimal point
/// right justified on the LED display.
/// @param num     Number to display
/// @param dp      Number of decimal places (-1 if no decimal point)
/// @param fill    Fill char (' ', '-' or '+')
///
void SevSeg::showNumber(unsigned long num, uint8_t dp, enum led_seg fill/*=SEG_NONE*/)
{
    char str[MAX_DIGITS + 1];
    str[MAX_DIGITS] = '\0';
    uint8_t d = 0;
    while (d < m_digits)
    {
        uint8_t mask = pgm_read_byte_near(LED_HexFont + (num % 10));
        uint8_t index = m_digits - d - 1;
        m_buf[index] = (enum led_seg)((d == dp) ? (mask | SEG_DP) : mask);
        ++d;
        num = num / 10;
        if (num == 0 && d > dp)
        {
            // Fill leading 0s
            while (d < m_digits)
            {
                uint8_t index = m_digits - d - 1;
                m_buf[index] = (enum led_seg)((d == dp) ? (fill | SEG_DP) : fill);
                ++d;
                // Insure only one '-' sign
                if (fill != LED_0)
                {
                    fill = LED_BLANK;
                }
            }
        }
    }
}

///
/// Show number as signed decimal with [optional] decimal point
/// right justified on the LED display.
/// @param num     Number to display
/// @param dp      Decimal Places (-1 if no decimal point)
///
void SevSeg::showDecimal(signed long num, uint8_t dp)
{
    if (num < 0)
    {
        showNumber(-num, dp, LED_MINUS);
    }
    else
    {
        showNumber(num, dp, LED_BLANK);
    }
}

///
/// Show text string as ASCII characters with [optional] decimal
/// point left justified on the LED display.
/// @param str     Text string to display
///
void SevSeg::showText(const char* str)
{
    for (uint8_t d = 0; d < m_digits; ++d)
    {
		const uint8_t c = str[d] - ' ';
        m_buf[d] = LED_GET_FONT(LED_AsciiFont, c);
    }
}

///
/// Show raw segments (A-F + decimal point) left justified on the LED display.
/// Useful for displaying graphics and other special symbols.
/// @param buf     Buffer of segment masks
///
void SevSeg::showRaw(const enum led_seg* buf)
{
    for (uint8_t b = 0; b < m_digits; ++b)
    {
        m_buf[b] = buf[b];
    }
}
