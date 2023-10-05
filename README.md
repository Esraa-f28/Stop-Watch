# Stop Watch System

## Introduction

This mini-project presents a comprehensive Stop Watch system using an ATmega32 Microcontroller operating at 1MHz. It includes Timer configuration, display multiplexing, and user-friendly control functionalities for reset, pause, and resume. The system showcases the persistence of vision technique for seamless display across six Common Anode 7-segment displays.

## Specifications

### Microcontroller
- Utilizes the ATmega32 Microcontroller operating at 1MHz.

### Timer Configuration
- Configures Timer1 in ATmega32 with CTC (Clear Timer on Compare Match) mode to count the Stop Watch time.

### Display
- Utilizes six Common Anode 7-segment displays for time display.

### Display Multiplexing
- Connects the six 7-segment displays using multiplexing techniques.
- A 7447 decoder is employed for all 7-segments, with each 7-segment enabled/disabled using an NPN BJT transistor connected to one of the MCU pins.

### Persistence of Vision
- Implements multiplexing to display one 7-segment at a time, leveraging the persistence of vision to create a continuous display effect.

### Connections
- Connects the 7447 decoder's 4 pins to the first 4 pins in PORTC.

### Control Pins
- Utilizes the first 6 pins in PORTA as enable/disable pins for the six 7-segments.

### Automatic Start
- The Stop Watch counting starts automatically when power is connected to the MCU.

### Reset Functionality
- Configures External Interrupt INT0 with a falling edge trigger.
- Connects a push button with an internal pull-up resistor.
- When a falling edge is detected, the Stop Watch time is reset.

### Pause Functionality
- Configures External Interrupt INT1 with a rising edge trigger.
- Connects a push button with an external pull-down resistor.
- When a rising edge is detected, the Stop Watch time is paused.

### Resume Functionality
- Configures External Interrupt INT2 with a falling edge trigger.
- Connects a push button with an internal pull-up resistor.
- When a falling edge is detected, the Stop Watch time is resumed.

## Drivers and Components
- GPIO Driver
- Timer Driver
- External Interrupts Driver
- 7-Segment Display

## Hardware Used
- Microcontroller: ATmega32

## Usage
- This project offers a practical implementation of a stopwatch with multiplexed 7-segment displays controlled by external interrupts for reset, pause, and resume functions.

## Schematic
 
