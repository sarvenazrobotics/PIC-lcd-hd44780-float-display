#include <xc.h>

// PIC18F4550 CORRECT Configuration Bits
#pragma config FOSC = INTOSC_HS
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config MCLRE = ON
#pragma config PBADEN = OFF
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config XINST = OFF
#pragma config DEBUG = OFF

#define _XTAL_FREQ 8000000UL

// LCD Pins - YOUR ACTUAL WIRING
#define LCD_RS LATBbits.LATB5    // RS on RB5
#define LCD_EN LATBbits.LATB4    // EN on RB4

// Data pins (4-bit mode) - D4 on RB0, D5 on RB1, D6 on RB2, D7 on RB3
#define LCD_D4 LATBbits.LATB0
#define LCD_D5 LATBbits.LATB1
#define LCD_D6 LATBbits.LATB2
#define LCD_D7 LATBbits.LATB3

void LCD_WriteNibble(unsigned char nibble, unsigned char rs) {
    LCD_RS = rs;
    LCD_D4 = (nibble >> 0) & 1;
    LCD_D5 = (nibble >> 1) & 1;
    LCD_D6 = (nibble >> 2) & 1;
    LCD_D7 = (nibble >> 3) & 1;
    LCD_EN = 1;
    __delay_us(2);
    LCD_EN = 0;
    __delay_us(50);
}

void LCD_Cmd(unsigned char cmd) {
    LCD_WriteNibble(cmd >> 4, 0);   // Send high nibble
    LCD_WriteNibble(cmd & 0x0F, 0); // Send low nibble
    if(cmd == 0x01 || cmd == 0x02) 
        __delay_ms(2);
    else 
        __delay_us(100);
}

void LCD_Char(char data) {
    LCD_WriteNibble(data >> 4, 1);  // Send high nibble
    LCD_WriteNibble(data & 0x0F, 1); // Send low nibble
}

void LCD_String(const char *str) {
    while(*str) 
        LCD_Char(*str++);
}

void LCD_Init(void) {
    __delay_ms(50);
    
    // Initialize to 4-bit mode
    LCD_WriteNibble(0x03, 0); __delay_ms(5);
    LCD_WriteNibble(0x03, 0); __delay_us(200);
    LCD_WriteNibble(0x03, 0); __delay_us(200);
    LCD_WriteNibble(0x02, 0); __delay_us(200);
    
    // Configure LCD
    LCD_Cmd(0x28);  // 4-bit, 2 lines, 5x8 dots
    LCD_Cmd(0x0C);  // Display ON, cursor OFF, blink OFF
    LCD_Cmd(0x06);  // Entry mode: increment, no shift
    LCD_Cmd(0x01);  // Clear display
    __delay_ms(5);
}

void main(void) {
    // Setup internal oscillator to 8MHz
    OSCCONbits.IRCF = 0b111;  // 8MHz
    OSCCONbits.SCS = 0b10;    // Use internal oscillator
    while(!OSCCONbits.IOFS);   // Wait for oscillator stable
    
    // Configure all pins as digital
    ADCON1 = 0x0F;     // Set all ports as digital
    
    // Configure TRIS registers for your pins
    TRISBbits.TRISB5 = 0;  // RB5 as output (RS)
    TRISBbits.TRISB4 = 0;  // RB4 as output (EN)
    TRISBbits.TRISB3 = 0;  // RB3 as output (D7)
    TRISBbits.TRISB2 = 0;  // RB2 as output (D6)
    TRISBbits.TRISB1 = 0;  // RB1 as output (D5)
    TRISBbits.TRISB0 = 0;  // RB0 as output (D4)
    
    // Initialize LCD
    LCD_Init();
    
    // Display message
    LCD_String("HELLO WORLD!");
    
    // Main loop
    while(1) {
        // Your main code here
        __delay_ms(1000);
    }
}