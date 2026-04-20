/* 
 * File:   xlcd.h
 * Author: Sarve
 *
 * Created on April 20, 2026, 1:46 PM
 */

#ifndef XLCD_H
#define XLCD_H

// LCD Pin Configuration
#define XLCD_DATAPORT       PORTD
#define XLCD_TRIS_DATAPORT  TRISD
#define XLCD_CONTROLPORT    PORTB
#define XLCD_TRIS_CONTROLPORT TRISB

#define XLCD_RS             RB2
#define XLCD_RW             RB3  
#define XLCD_ENABLE         RB4

// LCD Commands
#define LINE_ONE            0x80
#define LINE_TWO            0xC0
#define LINE_THREE          0x94
#define LINE_FOUR           0xD4

#define BLINK_CURSOR_ON     0x0F
#define BLINK_CURSOR_OFF    0x0E
#define BLINK_ON            0x0F
#define BLINK_OFF           0x0E
#define CURSOR_ON           0x0E
#define CURSOR_OFF          0x0C
#define DISPLAY_ON          0x0C
#define DISPLAY_OFF         0x08
#define CLEAR_SCREEN        0x01
#define RETURN_HOME         0x02

#define FOUR_BIT            0x28
#define EIGHT_BIT           0x38
#define LINES_5X7           0x28

// Function prototypes
void OpenXLCD(unsigned char);
void putcXLCD(char);
void putsXLCD(char *);
void WriteCmdXLCD(unsigned char);
void BusyXLCD(void);
void DelayFor18TCY(void);
void DelayPORXLCD(void);
void DelayXLCD(void);

#endif