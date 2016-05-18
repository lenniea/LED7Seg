#ifndef LED_7_SEG_H_FILE
#define LED_7_SEG_H_FILE
///
/// @author Lennie Araki
/// @copyright   (C) 2016 Lennie Araki.  All rights reserved.
///
/// @mainpage
///
/// LED7Seg is an Arduino library for single or multi-digit
/// 7-segment LED displays.
///
/// Includes <a href="examples.html">examples</a> which demonstrates the functionality of
/// the library.
///
/// @example LEDDemo.ino
/// @example showRaw.ino
/// @example showText.ino
/// @example showHex.ino
/// @example showDecimal.ino
///

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
//#include "WProgram.h"
    #define PROGMEM
    #define pgm_read_byte_near(x)   (*(uint8_t*) (x))
#endif

#ifdef _MSC_VER
    typedef signed __int8 int8_t;
    typedef signed __int16 int16_t;
    typedef unsigned __int8 uint8_t;
    typedef unsigned __int16 uint16_t;
#else
    #include <stdint.h>
#endif

/*! 
 *  @defgroup Types Type definitions
 *  @brief Types
 */

/*!
 *  @ingroup Types  LED segment constants
 *  @brief LED segment
 */
#if defined(ARDUINO)
enum led_seg : uint8_t
#else
enum led_seg
#endif
{
    SEG_NONE=0x00,          /*!< No segments */
    SEG_A=0x01,             /*!< Segment A */
    SEG_B=0x02,             /*!< Segment B */
    SEG_C=0x04,             /*!< Segment C */
    SEG_D=0x08,             /*!< Segment D */
    SEG_E=0x10,             /*!< Segment E */
    SEG_F=0x20,             /*!< Segment F */
    SEG_G=0x40,             /*!< Segment G */
    SEG_DP=0x80,            /*!< Decimal Point */
    SEGMENTS=8,             /*!< Number of segments (A-F+DP) */
	
    LED_BLANK=0,                                                    /*!< Font char  ' ' */
    LED_EXCLAM=                              SEG_B|       SEG_DP,   /*!< Font char  '!' */
    LED_DQUOTE=       SEG_F|                 SEG_B,                 /*!< Font char  '"' */
    LED_POUND=  SEG_G|                              SEG_A,          /*!< Font char  '#' */
    LED_DOLLAR= SEG_G|            SEG_D|            SEG_A,          /*!< Font char  '$' */
    LED_PERCENT=SEG_G|      SEG_E|           SEG_B|       SEG_DP,   /*!< Font char  '%%' */
    LED_AMPER=  SEG_G|                 SEG_C|SEG_B,                 /*!< Font char  '&' */
    LED_SQUOTE=       SEG_F,                                        /*!< Font char  ''' */
    LED_LPAREN=       SEG_F|SEG_E|SEG_D|            SEG_A,          /*!< Font char  '(' */
    LED_RPAREN=                   SEG_D|SEG_C|SEG_B|SEG_A,          /*!< Font char  ')' */
    LED_ASTER=  SEG_G|SEG_F|SEG_E|      SEG_C|SEG_B,                /*!< Font char  '*' */
    LED_PLUS=   SEG_G|SEG_F|SEG_E,                                  /*!< Font char  '+' */
    LED_COMMA=              SEG_E,                                  /*!< Font char  ',' */
    LED_MINUS=  SEG_G,                                              /*!< Font char  '-' */
    LED_PERIOD=                                          SEG_DP,    /*!< Font char  '.' */
    LED_SLASH=  SEG_G|      SEG_E|            SEG_B,                /*!< Font char  '/' */

    LED_0=      SEG_F|SEG_E|SEG_D|SEG_C|SEG_B|SEG_A,                /*!< Font char  '0' */
    LED_1=                        SEG_C|SEG_B,                      /*!< Font char  '1' */
    LED_2=      SEG_G|      SEG_E|SEG_D      |SEG_B|SEG_A,          /*!< Font char  '2' */
    LED_3=      SEG_G|            SEG_D|SEG_C|SEG_B|SEG_A,          /*!< Font char  '3' */
    LED_4=      SEG_G|SEG_F            |SEG_C|SEG_B,                /*!< Font char  '4' */
    LED_5=      SEG_G|SEG_F      |SEG_D|SEG_C      |SEG_A,          /*!< Font char  '5' */
    LED_6=      SEG_G|SEG_F|SEG_E|SEG_D|SEG_C      |SEG_A,          /*!< Font char  '6' */
    LED_7=                        SEG_C|SEG_B|SEG_A,                /*!< Font char  '7' */
    LED_8=      SEG_G|SEG_F|SEG_E|SEG_D|SEG_C|SEG_B|SEG_A,          /*!< Font char  '8' */
    LED_9=      SEG_G|SEG_F|      SEG_D|SEG_C|SEG_B|SEG_A,          /*!< Font char  '9' */
    LED_COLON=  SEG_G|            SEG_D,                            /*!< Font char  ':' */
    LED_SEMI=   SEG_G|            SEG_D|                  SEG_DP,   /*!< Font char  ';' */
    LED_LESS=   SEG_G|SEG_F|                        SEG_A,          /*!< Font char  '<' */
    LED_EQUAL=  SEG_G|                              SEG_A,          /*!< Font char  '=' */
    LED_GREAT=  SEG_G|                        SEG_B|SEG_A,          /*!< Font char  '>' */
    LED_QUEST=  SEG_G|      SEG_E|            SEG_B|SEG_A|SEG_DP,   /*!< Font char  '?' */

    LED_ATSIGN= SEG_G|      SEG_E|SEG_D|SEG_C|SEG_B|SEG_A|SEG_DP,    /*!< Font char  '@' */
    LED_A=      SEG_G|SEG_F|SEG_E      |SEG_C|SEG_B|SEG_A,           /*!< Font char  'A' */
    LED_B=      SEG_G|SEG_F|SEG_E|SEG_D|SEG_C,                       /*!< Font char  'B' */
    LED_C=      SEG_F|SEG_E|SEG_D|                  SEG_A,           /*!< Font char  'C' */
    LED_D=      SEG_G|      SEG_E|SEG_D|SEG_C|SEG_B,                 /*!< Font char  'D' */
    LED_E=      SEG_G|SEG_F|SEG_E|SEG_D|            SEG_A,           /*!< Font char  'E' */
    LED_F=      SEG_G|SEG_F|SEG_E|                  SEG_A,           /*!< Font char  'F' */
    LED_G=            SEG_F|SEG_E|SEG_D|SEG_C      |SEG_A,           /*!< Font char  'G' */
    LED_H=      SEG_G|SEG_F|SEG_E|      SEG_C|SEG_B,                 /*!< Font char  'H' */
    LED_I=            SEG_F|SEG_E,                                   /*!< Font char  'I' */
    LED_J=                  SEG_E|SEG_D|SEG_C|SEG_B,                 /*!< Font char  'J' */
    LED_K=      SEG_G|SEG_F|SEG_E|      SEG_C      |SEG_A,           /*!< Font char  'K' */
    LED_L=            SEG_F|SEG_E|SEG_D,                             /*!< Font char  'L' */
    LED_M=            SEG_F|SEG_E|      SEG_C|SEG_B|SEG_A,           /*!< Font char  'M' */
    LED_N=            SEG_F|SEG_E|      SEG_C|SEG_B|SEG_A,           /*!< Font char  'N' */
    LED_O=            SEG_F|SEG_E|SEG_D|SEG_C|SEG_B|SEG_A,           /*!< Font char  '0' */
    LED_P=      SEG_G|SEG_F|SEG_E|            SEG_B|SEG_A,           /*!< Font char  'P' */
    LED_Q=            SEG_F|SEG_E|SEG_D|SEG_C|SEG_B|SEG_A|SEG_DP,    /*!< Font char  'Q' */
    LED_R=            SEG_F|SEG_E                  |SEG_A,           /*!< Font char  'R' */
    LED_S=      SEG_G|SEG_F      |SEG_D|SEG_C      |SEG_A,           /*!< Font char  'S' */
    LED_T=      SEG_G|SEG_F|SEG_E|SEG_D,                             /*!< Font char  'T' */
    LED_U=            SEG_F|SEG_E|SEG_D|SEG_C|SEG_B      |SEG_DP,    /*!< Font char  'U' */
    LED_V=            SEG_F|SEG_E|SEG_D|SEG_C|SEG_B,                 /*!< Font char  'V' */
    LED_W=            SEG_F|SEG_E|SEG_D|SEG_C|SEG_B,                 /*!< Font char  'W' */
    LED_X=      SEG_G|SEG_F|SEG_E|      SEG_C|SEG_B,                 /*!< Font char  'X' */
    LED_Y=      SEG_G|SEG_F|      SEG_D|SEG_C|SEG_B,                 /*!< Font char  'Y' */
    LED_Z=      SEG_G|      SEG_E|SEG_D      |SEG_B|SEG_A,           /*!< Font char  'Z' */
    LED_LBRACK=       SEG_F|SEG_E|SEG_D|            SEG_A,           /*!< Font char  '[' */
    LED_BSLASH= SEG_G|SEG_F|            SEG_C,                       /*!< Font char  '\\' */
    LED_RBRACK=                   SEG_D|SEG_C|SEG_B|SEG_A,           /*!< Font char  ']' */
    LED_CARET=        SEG_F|                  SEG_B|SEG_A,           /*!< Font char  '^' */
    LED_UNDER=                    SEG_D,                             /*!< Font char  '_' */

    LED_ACCENT=                               SEG_B,                 /*!< Font char  '`' */
    LED_a=      SEG_G|      SEG_E|SEG_D|SEG_C|SEG_B|SEG_A,           /*!< Font char  'a' */
    LED_b=      SEG_G|SEG_F|SEG_E|SEG_D|SEG_C,                       /*!< Font char  'b' */
    LED_c=      SEG_G|      SEG_E|SEG_D,                             /*!< Font char  'c' */
    LED_d=      SEG_G|      SEG_E|SEG_D|SEG_C|SEG_B,                 /*!< Font char  'd' */
    LED_e=      SEG_G|SEG_F|SEG_E|SEG_D|      SEG_B|SEG_A,           /*!< Font char  'e' */
    LED_f=      SEG_G|SEG_F|SEG_E|                  SEG_A,           /*!< Font char  'f' */
    LED_g=      SEG_G|SEG_F|      SEG_D|SEG_C|SEG_B|SEG_A,           /*!< Font char  'g' */
    LED_h=      SEG_G|SEG_F|SEG_E|      SEG_C,                       /*!< Font char  'h' */
    LED_i=                  SEG_E,                                   /*!< Font char  'i' */
    LED_j=                        SEG_D|SEG_C|SEG_B,                 /*!< Font char  'j' */
    LED_k=      SEG_G|SEG_F|SEG_E|      SEG_C      |SEG_A,           /*!< Font char  'k' */
    LED_l=            SEG_F|SEG_E,                                   /*!< Font char  'l' */
    LED_m=      SEG_G|      SEG_E|      SEG_C,                       /*!< Font char  'm' */
    LED_n=      SEG_G|      SEG_E|      SEG_C,                       /*!< Font char  'n' */
    LED_o=      SEG_G|      SEG_E|SEG_D|SEG_C,                       /*!< Font char  'o' */
    LED_p=      SEG_G|SEG_F|SEG_E|            SEG_B|SEG_A,           /*!< Font char  'p' */
    LED_q=      SEG_G|SEG_F|            SEG_C|SEG_B|SEG_A|SEG_DP,    /*!< Font char  'q' */
    LED_r=      SEG_G|      SEG_E,                                   /*!< Font char  'r' */
    LED_s=      SEG_G|SEG_F      |SEG_D|SEG_C      |SEG_A,           /*!< Font char  's' */
    LED_t=      SEG_G|SEG_F|SEG_E|SEG_D,                             /*!< Font char  't' */
    LED_u=                  SEG_E|SEG_D|SEG_C            |SEG_DP,    /*!< Font char  'u' */
    LED_v=                  SEG_E|SEG_D|SEG_C,                       /*!< Font char  'v' */
    LED_w=                  SEG_E|SEG_D|SEG_C,                       /*!< Font char  'w' */
    LED_x=      SEG_G|SEG_F|SEG_E|      SEG_C|SEG_B,                 /*!< Font char  'x' */
    LED_y=      SEG_G|SEG_F|      SEG_D|SEG_C|SEG_B,                 /*!< Font char  'y' */
    LED_z=      SEG_G|      SEG_E|SEG_D      |SEG_B|SEG_A,           /*!< Font char  'z' */
    LED_LBRACE= SEG_G|                  SEG_C|SEG_B,                 /*!< Font char  '{' */
    LED_VERTBAR=      SEG_F|SEG_E,                                   /*!< Font char  '|' */
    LED_RBRACE= SEG_G|SEG_F|SEG_E,                                   /*!< Font char  '}' */
    LED_TILDE=  SEG_G|SEG_F|                  SEG_B,                 /*!< Font char  '~' */
    LED_DEGREE= SEG_G|SEG_F|                  SEG_B|SEG_A            /*!< Font char Degree */
};

extern const PROGMEM enum led_seg LED_AsciiFont[96];
extern const PROGMEM enum led_seg LED_HexFont[16];

/*!
 *  @defgroup Macros #define Macros
 *  @brief Macros
 */
 
/*!
 *  @ingroup Macros
 *  Macro to get LED mask bits for character c in a font table.
 *  @brief Get Font Mask
 *  @param font   Font table
 *  @param c      Character index (0-based)
 *  @return mask  LED mask bits
 */
#define LED_GET_FONT(font,c)	((enum led_seg)(((c) < sizeof(font)) ? pgm_read_byte_near(font + (c)) : (c)))

/*!
 *  @ingroup Types  LED digit constants
 *  @brief LED dig
 */
#if defined(ARDUINO)
enum led_dig : uint8_t
#else
enum led_dig
#endif
{
    DIG_NONE=0x00,           /*!< No digits */
    DIG_0=0x01,              /*!< 1st Digit */
    DIG_1=0x02,              /*!< 2nd Digit */
    DIG_2=0x04,              /*!< 3rd Digit */
    DIG_3=0x08,              /*!< 4th Digit */
    DIG_4=0x10,              /*!< 5th Digit */
    DIG_5=0x20,              /*!< 6th Digit */
    DIG_6=0x40,              /*!< 7th Digit */
    DIG_7=0x80,              /*!< 8th Digit */
    MAX_DIGITS=8             /*!< Maximum number of digits */
};

/*!
 *  @ingroup Types  LED configuration constants
 *  @brief LED config
 */
#if defined(_ARUDINO)
enum led_config : uint8_t
#else
enum led_config
#endif
{
    SEG_INVERT=0x01,         //!< Bit mask for SEG_INVERT
    DIG_INVERT=0x02,         //!< Bit mask for DIG_INVERT

    // Use defines to link the hardware configurations to the correct numbers
    COMMON_ANODE=SEG_INVERT,          //!< Config for Common Anode LED display
    COMMON_CATHODE=DIG_INVERT         //!< Config for Common Cathode LED display
};
    
///
/// LED 7-Segment Display Driver library for Arduino
///
///        --A--
///     F |     | B
///        --G--
///     E |     | C
///        --D--
///
/// CAUTION: use series resistors in series with the segment pins to 
/// limit the current to the LED.  Using the output pin voltage, LED
/// forward current calculate the value for the resistor using the 
/// following website:
///
/// http://led.linear1.org/1led.wiz
///
/// Typical values for series resistor for 5V outputs are: 330 ohms = 10mA,
/// 220 ohms = 15 mA, 150 ohms = 20 mA.
///
/// If the total current exceeds the maximum source or sink current of
/// any pin (approx 100mA see datasheet for details) use a PNP or NPN 
/// transistor to prevent damage to the ATMega microprocessor.
///
/// @brief LED 7-Segment library
///
class SevSeg
{
public:
    // Constructor
    SevSeg();
protected:
    uint8_t m_config;              //!< Config byte: bit 0=SEG_INVERT, bit 1=DIG_INVERT
    uint8_t m_digits;              //!< Number of digits (e.g. sizeof(m_digitPin)
    uint8_t m_index;               //!< Index of digit to multiplex
    unsigned long m_last;          //!< Timestamp of last refresh/update
    
    enum led_seg m_buf[MAX_DIGITS]; //!< Buffer of segments to display
    const uint8_t* m_pins;         //!< Digit pin array

public:
    void begin(enum led_config conf, uint8_t digits, const uint8_t* pin);
    void setSegments(enum led_seg mask);
    void setDigits(enum led_dig mask);
    void refreshDigits(void);
    void refreshSegments(void);
    void showHex(unsigned long num);
    void showNumber(unsigned long num, uint8_t dp, enum led_seg fill = SEG_NONE);
    void showDecimal(signed long i, uint8_t dp);
    void showText(const char* str);
    void showRaw(const enum led_seg* buf);
};

#endif
