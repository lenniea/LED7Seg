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
/*!
 * LED Font Table - 96 printable ASCII character set
 * @brief LED ASCII Font
 */
const PROGMEM enum led_seg LED_AsciiFont[96] =
{
    LED_BLANK,  LED_EXCLAM, LED_DQUOTE, LED_POUND,  LED_DOLLAR,  LED_PERCENT,LED_AMPER,  LED_SQUOTE,
    LED_LPAREN, LED_RPAREN, LED_ASTER,  LED_PLUS,   LED_COMMA,   LED_MINUS,  LED_PERIOD, LED_SLASH,

    LED_0,      LED_1,      LED_2,      LED_3,      LED_4,      LED_5,      LED_6,      LED_7,
    LED_8,      LED_9,      LED_COLON,  LED_SEMI,   LED_LESS,	LED_EQUAL,  LED_GREAT,  LED_QUEST,
	
	LED_ATSIGN,  LED_A,     LED_B,      LED_C,      LED_D,      LED_E,      LED_F,      LED_G,
    LED_H,      LED_I,      LED_J,      LED_K,      LED_L,      LED_M,      LED_N,      LED_O,
	
	LED_P,      LED_Q,      LED_R,      LED_S,      LED_T,      LED_U,      LED_V,      LED_W,
	LED_X,      LED_Y,      LED_Z,      LED_LBRACK, LED_BSLASH, LED_RBRACK, LED_CARET,  LED_UNDER,
	
	LED_ACCENT, LED_a,      LED_b,      LED_c,      LED_d,      LED_e,      LED_f,      LED_g,
	LED_h,      LED_i,      LED_j,      LED_k,      LED_l,      LED_m,      LED_n,      LED_o,
	
	LED_p,      LED_q,      LED_r,      LED_s,      LED_t,      LED_u,      LED_v,      LED_w,
	LED_x,      LED_y,      LED_z,      LED_LBRACE, LED_VERTBAR,LED_RBRACE, LED_TILDE,  LED_DEGREE
};

/*!
 *  LED Font Table for hexadecimal digits (0-F: no offset)
 *  @brief LED Hex font
 */
const PROGMEM enum led_seg LED_HexFont[16] =
{
    LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7,
    LED_8, LED_9, LED_A, LED_B, LED_C, LED_D, LED_E, LED_F
};
