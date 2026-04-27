## Overview
This project demonstrates how to interface a 16x2 LCD (LM016L) with PIC18F4550 microcontroller in 4-bit mode. The code is written in C using MPLAB X IDE and XC8 compiler.

## Hardware Requirements

- PIC18F4550 Microcontroller

- 16x2 LCD Display (LM016L or compatible)

- 10kΩ Potentiometer (for contrast adjustment)

- 5V Power Supply

 - Breadboard and Jumper Wires

## wiring Diagram
PIC18F4550                    LCD LM016L
┌──────────┐                  ┌──────────┐
│    RB5   ├──────────────────┤ RS (Pin4)│
│    RB4   ├──────────────────┤ E  (Pin6)│
│    RB3   ├──────────────────┤ D7 (Pin14)│
│    RB2   ├──────────────────┤ D6 (Pin13)│
│    RB1   ├──────────────────┤ D5 (Pin12)│
│    RB0   ├──────────────────┤ D4 (Pin11)│
│    GND   ├──────────────────┤ RW (Pin5) │
│    GND   ├──────────────────┤ VSS(Pin1) │
│    +5V   ├──────────────────┤ VDD(Pin2) │
└──────────┘                  └──────────┘
                                    │
                              ┌─────┴─────┐
                              │ 10k POT   │
                              │  VEE(Pin3)│
                              └───────────┘
