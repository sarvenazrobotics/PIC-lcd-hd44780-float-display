/*
 * File:   LCD.c
 * Author: Sarvenaz 
 *
 * Created on April 20, 2026, 1:32 PM
 */


#include <xc.h>
#include "xlcd.h"

void DelayFor18TCY(void) { __delay_us(18); }
void DelayPORXLCD(void) { __delay_ms(15); }
void DelayXLCD(void) { __delay_ms(5); }

void BusyXLCD(void) {
    XLCD_TRIS_DATAPORT = 0xFF;
    XLCD_RS = 0;
    XLCD_RW = 1;
    XLCD_ENABLE = 1;
    DelayFor18TCY();
    while(XLCD_DATAPORT & 0x80);
    XLCD_ENABLE = 0;
    XLCD_TRIS_DATAPORT = 0x00;
}

void WriteCmdXLCD(unsigned char cmd) {
    while(BusyXLCD());
    XLCD_RS = 0;
    XLCD_RW = 0;
    XLCD_DATAPORT = (XLCD_DATAPORT & 0x0F) | (cmd & 0xF0);
    XLCD_ENABLE = 1;
    DelayFor18TCY();
    XLCD_ENABLE = 0;
    XLCD_DATAPORT = (XLCD_DATAPORT & 0x0F) | ((cmd << 4) & 0xF0);
    XLCD_ENABLE = 1;
    DelayFor18TCY();
    XLCD_ENABLE = 0;
}

void putcXLCD(char data) {
    while(BusyXLCD());
    XLCD_RS = 1;
    XLCD_RW = 0;
    XLCD_DATAPORT = (XLCD_DATAPORT & 0x0F) | (data & 0xF0);
    XLCD_ENABLE = 1;
    DelayFor18TCY();
    XLCD_ENABLE = 0;
    XLCD_DATAPORT = (XLCD_DATAPORT & 0x0F) | ((data << 4) & 0xF0);
    XLCD_ENABLE = 1;
    DelayFor18TCY();
    XLCD_ENABLE = 0;
}

void putsXLCD(char *str) {
    while(*str) putcXLCD(*str++);
}

void OpenXLCD(unsigned char mode) {
    XLCD_TRIS_DATAPORT = 0x00;
    XLCD_TRIS_CONTROLPORT &= 0x83;
    DelayPORXLCD();
    WriteCmdXLCD(0x33);
    DelayXLCD();
    WriteCmdXLCD(0x32);
    DelayXLCD();
    WriteCmdXLCD(mode);
    WriteCmdXLCD(0x0C);
    WriteCmdXLCD(0x06);
    WriteCmdXLCD(0x01);
    DelayXLCD();
}
