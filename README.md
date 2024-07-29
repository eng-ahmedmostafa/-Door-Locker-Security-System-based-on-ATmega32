### Door Locker Security System based on ATmega32

#### **Objective:**
Develop a door locker security system using two ATmega32 microcontrollers to unlock a door with a password, designed with a layered architecture.

#### **System Overview:**
The system consists of two main components:
1. **HMI_ECU (Human Machine Interface ECU)**: Manages user interaction with a 2x16 LCD and a 4x4 keypad.
2. **Control_ECU**: Handles password processing, door control using a DC motor, alarm activation via a buzzer, and data storage in EEPROM.

#### **Key Features:**
1. **Password Setup and Confirmation**: 
   - User enters a 5-digit password twice for confirmation.
   - HMI_ECU sends the passwords to Control_ECU via UART for verification and storage in EEPROM.
2. **Password Verification**:
   - User inputs the password to unlock the door or change the password.
   - Password verification is done by Control_ECU.
   - Incorrect passwords prompt re-entry, with the system locking after three consecutive failures and activating a buzzer.
3. **Door Operation**:
   - On correct password entry, the DC motor rotates to unlock and lock the door with status messages displayed on the LCD.

#### **Hardware Components:**
- **ATmega32 Microcontrollers**: Two units operating at 8 MHz.
- **2x16 LCD**: Displays messages and prompts.
- **4x4 Keypad**: User input for passwords.
- **DC Motor**: Controls the door locking mechanism.
- **EEPROM**: Stores the system password.
- **Buzzer**: Alerts on incorrect password attempts.

#### **Software Components:**
1. **GPIO Driver**: Manages input/output operations for both ECUs.
2. **ICU Driver**: Configures and handles interrupts.
3. **LCD Driver**: Interfaces with the LCD for displaying messages.
4. **Keypad Driver**: Reads user inputs from the keypad.
5. **DC Motor Driver**: Controls motor operations for door locking.
6. **EEPROM Driver**: Manages password storage and retrieval.
7. **I2C Driver**: Facilitates communication between Control_ECU and EEPROM.
8. **UART Driver**: Enables communication between HMI_ECU and Control_ECU.
9. **Timer Driver**: Manages timing functions for motor operations and display messages.
10. **Buzzer Driver**: Controls the buzzer for alert signals.

#### **System Sequence:**
1. **Password Creation**:
   - User enters and confirms a 5-digit password.
   - Passwords are sent to Control_ECU for verification and storage.
2. **Main Options**:
   - User selects between unlocking the door or changing the password.
3. **Open Door**:
   - User enters the password.
   - Correct password triggers door unlocking and subsequent locking, with motor control and LCD messages.
4. **Change Password**:
   - User enters the current password.
   - On correct entry, the user is prompted to set a new password.
5. **Error Handling**:
   - Incorrect password entry allows two more attempts.
   - Three consecutive failures trigger the buzzer and lock the system for one minute.

#### **Driver Requirements:**
1. **GPIO Driver**: Used in both ECUs.
2. **LCD Driver**: Connects to HMI_ECU, supports 2x16 LCD in 8-bit or 4-bit mode.
3. **Keypad Driver**: Connects to HMI_ECU.
4. **DC Motor Driver**: Connects to Control_ECU, uses Timer0 PWM for speed control.
5. **EEPROM Driver**: External, connects to Control_ECU via I2C.
6. **I2C Driver**: Used in Control_ECU for EEPROM communication.
7. **UART Driver**: Used for ECU-to-ECU communication.
8. **Timer Driver**: Used in both ECUs for timing operations.
9. **Buzzer Driver**: Connects to Control_ECU for alert signals.

This system ensures secure and user-friendly door access control with a robust layered architecture and modular driver implementation.
