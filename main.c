#include <xc.h>
#include <stdio.h>

#pragma config FOSC = INTOSCIO_EC
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config MCLRE = ON
#pragma config PBADEN = OFF

#define _XTAL_FREQ 8000000UL

// LCD Pins
#define LCD_RS  RB2
#define LCD_RW  RB3
#define LCD_EN  RB4
#define LCD_DATA PORTD

void LCD_Delay() { __delay_us(20); }

void LCD_Cmd(unsigned char cmd) {
    TRISD = 0x00; 
    TRISBbits.TRISB2 = 0; 
    TRISBbits.TRISB3 = 0; 
    TRISBbits.TRISB4 = 0;
    
    LCD_RS = 0; LCD_RW = 0;
    LCD_DATA = (LCD_DATA & 0x0F) | (cmd & 0xF0);
    LCD_EN = 1; LCD_Delay(); LCD_EN = 0;
    LCD_DATA = (LCD_DATA & 0x0F) | ((cmd << 4) & 0xF0);
    LCD_EN = 1; LCD_Delay(); LCD_EN = 0;
    __delay_ms(2);
}

void LCD_Char(char data) {
    TRISD = 0x00; 
    TRISBbits.TRISB2 = 0; 
    TRISBbits.TRISB3 = 0; 
    TRISBbits.TRISB4 = 0;
    
    LCD_RS = 1; LCD_RW = 0;
    LCD_DATA = (LCD_DATA & 0x0F) | (data & 0xF0);
    LCD_EN = 1; LCD_Delay(); LCD_EN = 0;
    LCD_DATA = (LCD_DATA & 0x0F) | ((data << 4) & 0xF0);
    LCD_EN = 1; LCD_Delay(); LCD_EN = 0;
}

void LCD_String(char *str) {
    while(*str) LCD_Char(*str++);
}

void LCD_Init() {
    __delay_ms(20);
    LCD_Cmd(0x33); 
    LCD_Cmd(0x32);
    LCD_Cmd(0x28); 
    LCD_Cmd(0x0C); 
    LCD_Cmd(0x06); 
    LCD_Cmd(0x01);
}

// ? Custom integer to string conversion (replaces itoa)
void IntToString(unsigned int num, char *str) {
    unsigned int i = 0;
    unsigned int temp;
    
    if(num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    
    // Convert number to string (reversed)
    while(num > 0) {
        temp = num % 10;
        str[i++] = temp + '0';
        num = num / 10;
    }
    str[i] = '\0';
    
    // Reverse the string
    unsigned int j = 0;
    i--;
    while(j < i) {
        temp = str[j];
        str[j] = str[i];
        str[i] = temp;
        j++;
        i--;
    }
}

void main(void) {
    unsigned int b;
    float data = 12.345;
    char str[6];
    
    // Configure oscillator
    OSCCONbits.IRCF = 0b111;  // 8 MHz
    while(OSCCONbits.IOFS == 0);
    
    // All pins digital
    ADCON1 = 0x0F;
    
    // Initialize LCD
    LCD_Init();
    
    while(1) {
        LCD_Cmd(0x01);  // Clear LCD
        
        // Calculate parts
        unsigned int intPart = (unsigned int)data;
        b = (unsigned int)((data - intPart) * 1000);
        
        // Display "data="
        LCD_String("data=");
        
        // Display integer part
        IntToString(intPart, str);
        LCD_String(str);
        
        // Display decimal point
        LCD_Char('.');
        
        // Display decimal part with leading zeros
        if(b < 100) LCD_Char('0');
        if(b < 10) LCD_Char('0');
        IntToString(b, str);
        LCD_String(str);
        
        // ? Use __delay_ms instead of Delay10KTCYx
        __delay_ms(1000);
    }
}