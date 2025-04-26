# Door Locker Security System

An embedded **door security system** developed using an **ATmega32 microcontroller**.  
The system securely controls door access through **password authentication** using a **keypad** and displays status via an **LCD**. It also manages door operations with a **DC motor** and implements security features like **alarm activation** after repeated failed attempts.

## Features

- **Password Authentication**: Users must enter the correct password via keypad to unlock the door.
- **Password Storage**: Password is saved permanently using **EEPROM**.
- **Motor Control**: 
  - Opens the door upon correct password entry.
  - Closes the door after a fixed time.
- **Security Alarm**: 
  - Activates a buzzer after consecutive incorrect password attempts.
- **User Feedback**:
  - Status messages displayed on an LCD screen.
  - Keypad entry interface.


## Data Flow

1. User inputs password via keypad.
2. Control ECU verifies password:
   - If correct: activates motor to open the door.
   - If incorrect: counts the failed attempt.
3. After 3 failed attempts, the system activates an alarm.
4. Door automatically closes after opening.


## Requirements

- ATmega32 Microcontroller
- Keypad
- LCD Screen
- DC Motor + Driver Circuit
- Buzzer
- EEPROM
- UART, I2C, and GPIO Drivers




