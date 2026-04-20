/*
 * File:   main.c
 * Author: Sarvenaz
 *
 * Created on April 20, 2026, 2:04 PM
 */


#include "xc.h"
#include <stdlib.h>
#include "xlcd.h"

#pragma config FOSC= INTOSCIO_EC
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config MCLRE=ON
#pragma config PBADEN=OFF

#define _XTAL_FREQ 8000000UL

int main(void) {
    unsigned int b;
    float data=12.798;
    char str[5];
    
    OSCCONbits.IRCF=0b111;
    while(OSCCONbits.IOFS==0);
}
