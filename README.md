# Secure-Gate-Pro---Intelligent_Multi-Level_Biometric_Access_Control_And_Intrusion_Prevention_System
SecureGate Pro is an LPC2148-based biometric security system that provides multi-level authentication using User ID, password, and fingerprint verification. It supports fingerprint enrollment, deletion, password management, EEPROM-based user storage, and motor-controlled door access with UART-based security logging to prevent unauthorized entry.

# 1. Overview

SecureGate Pro is an embedded biometric security system developed using an ARM7 LPC21xx microcontroller. It provides multi-level authentication by combining user ID verification, password authentication, and fingerprint recognition before granting access to a secured area.

The system uses an R305 fingerprint sensor for biometric identification, a 4×4 matrix keypad for user input, and an LCD for displaying system messages. User information and password data are stored in an external I2C EEPROM. After successful authentication, a motor-driven mechanism opens the door. The system also maintains UART-based access logs to record authentication events, access permissions, and door operations.

An administrator can access a dedicated menu to manage passwords and fingerprint records.

# 2. Objectives

- Develop a secure embedded access control system using an ARM7 microcontroller.
- Implement multi-level authentication using user ID, password, and fingerprint verification.
- Store user information and password data in external EEPROM.
- Provide fingerprint enrollment, identification, and deletion facilities.
- Control door opening and closing through a motor interface.
- Display authentication status and system messages using an LCD.
- Maintain serial logs of successful and unsuccessful access attempts.
- Provide administrator functionality for password and fingerprint management.

# 3. Hardware Requirements

| S.No | Component | Purpose |
|---|---|---|
| 1 | LPC21xx ARM7 Development Board | Main controller |
| 2 | R305 Fingerprint Sensor | Fingerprint enrollment and verification |
| 3 | 16×2 LCD | Display system messages |
| 4 | 4×4 Matrix Keypad | User ID and password input |
| 5 | I2C EEPROM (24Cxx compatible) | Store user information and password |
| 6 | Motor / DC Motor Mechanism | Door opening and closing |
| 7 | Motor Driver Circuit | Drive the door motor |
| 8 | External Switch | Door closing control |
| 9 | Power Supply | Power the controller and peripherals |
| 10 | UART-to-USB Interface | Serial monitoring and debugging |

**Note:** The motor driver, motor supply voltage, and exact EEPROM part number should be selected according to the actual hardware kit.

# 4. System Block Diagram

<img width="435" height="271" alt="image" src="https://github.com/user-attachments/assets/1e808d5c-c2b4-4021-9805-5f962b921eed" />


## 5. Pin Configuration

The following pin assignments are derived from the project source code and header-file definitions.

### 5.1 LCD Connections

| LCD Signal | LPC21xx Pin | Description |
|---|---|---|
| Data D0–D7 | P0.16–P0.23 | 8-bit LCD data |
| RS | P0.12 | Register Select |
| EN | P0.13 | Enable signal |
| RW | Not separately controlled in code | LCD write operation |

### 5.2 Keypad Connections

| Keypad Signal | LPC21xx Pin |
|---|---|
| Row 1 | P1.16 |
| Row 2 | P1.17 |
| Row 3 | P1.18 |
| Row 4 | P1.19 |
| Column 1 | P1.20 |
| Column 2 | P1.21 |
| Column 3 | P1.22 |
| Column 4 | P1.23 |

### 5.3 Fingerprint Sensor (R305)

| Sensor Signal | LPC21xx Pin | Function |
|---|---|---|
| TX | P0.9 (RXD1) | Sensor-to-controller communication |
| RX | P0.8 (TXD1) | Controller-to-sensor communication |
| VCC | As per sensor specification | Power supply |
| GND | GND | Common ground |

Communication is established through UART1 at 9600 baud, using 8 data bits, no parity, and 1 stop bit.

### 5.4 EEPROM (I2C)

| Signal | LPC21xx Pin | Function |
|---|---|---|
| SDA | P0.3 (SDA0) | Serial data |
| SCL | P0.2 (SCL0) | Serial clock |
| Device Address | 0x50 | EEPROM slave address |

### 5.5 Motor Driver Connections

| Signal | LPC21xx Pin | Description |
|---|---|---|
| Motor Input 1 | P1.24 | Motor direction control |
| Motor Input 2 | P1.25 | Motor direction control |
| Enable | P1.28 | Motor driver enable |

### 5.6 Additional Connections

| Signal | LPC21xx Pin | Function |
|---|---|---|
| UART0 TXD | P0.0 | Serial log transmission |
| UART0 RXD | P0.1 | Serial reception |
| Door Switch | P0.5 | Door closing control |
| External Interrupt 2 | P0.7 | Administrator menu activation |

**Note:** Verify the physical board wiring and peripheral pin multiplexing before implementation. Power and ground connections are not included in the signal pin tables.

## 6. System Architecture

The system follows a modular embedded architecture consisting of the following layers.

### 6.1 Input Layer
- 4×4 matrix keypad for user ID and password entry.
- R305 fingerprint sensor for biometric input.
- External interrupt for administrator menu activation.
- Door control switch for closing operation.

### 6.2 Processing Layer
- LPC21xx ARM7 microcontroller.
- Authentication and access verification logic.
- Fingerprint enrollment and identification commands.
- Password comparison and user record management.
- Motor control and event handling.

### 6.3 Storage Layer
- External I2C EEPROM.
- Stores registered user IDs, password information, and user count.
- Fingerprint templates are managed by the R305 sensor's internal memory.

### 6.4 Output Layer
- LCD displays authentication and door status.
- Motor driver operates the door mechanism.
- UART0 sends access and system event logs to a serial terminal.

## 7. System Working

1. **System Initialization:** The LPC21xx controller initializes UART0, UART1, I2C, LCD, keypad, and external interrupt peripherals.

2. **User ID Verification:** The user enters a four-digit ID using the keypad. The controller checks the entered ID against the registered user information stored in EEPROM.

3. **Password Authentication:** If the user ID is valid, the system requests a four-digit password and compares it with the stored password.

4. **Fingerprint Verification:** After successful password verification, the system asks the user to place their finger on the R305 fingerprint sensor.

5. **Access Decision:** The fingerprint sensor captures the fingerprint and searches its stored templates. If a match is found, the system grants access.

6. **Door Operation:** The controller activates the motor driver to open the door. The LCD displays the door status.

7. **Door Closing:** The user operates the external switch to initiate the door-closing operation. The controller activates the motor in the reverse direction.

8. **Event Logging:** UART0 records user authentication, access granted or denied, fingerprint status, and door operation events.

9. **Administrator Mode:** An external interrupt activates the administrator menu, allowing password updates and fingerprint enrollment, searching, and deletion.

## 8. Project Workflow

```text
             POWER ON
                 |
                 v
       Initialize LPC21xx MCU
                 |
                 v
     Initialize UART, I2C, LCD,
       Keypad and Interrupt
                 |
                 v
       Read Registered User Count
                 |
                 v
        Enter Four-Digit User ID
                 |
                 v
          Is User ID Valid?
             /       \
           NO         YES
           |           |
           v           v
      Access Denied  Enter Password
           |           |
           |           v
           |      Password Correct?
           |         /      \
           |       NO        YES
           |       |          |
           |       v          v
           |   Access Denied  Scan Fingerprint
           |                    |
           |                    v
           |             Fingerprint Match?
           |                /       \
           |              NO         YES
           |              |           |
           |              v           v
           |         Access Denied  Access Granted
           |                            |
           |                            v
           |                        Open Door
           |                            |
           |                            v
           |                      Wait for Switch
           |                            |
           |                            v
           |                        Close Door
           |                            |
           +----------------------------+
                        |
                        v
                   Event Logging
```

**Administrator Workflow:**

```text
External Interrupt 2
        |
        v
Administrator Menu
        |
        +----------------------+
        |          |           |
        v          v           v
    Edit       Manage       Exit
   Password  Fingerprints    |
        |          |          |
        v          v          v
  Verify Old   Enroll /     Return to
  Password     Search /     Main Mode
        |       Delete
        v
  Update Password
```

## 9. Development Tools & Environment

### Programming Language
- Embedded C

### Microcontroller
- LPC21xx ARM7 family

### Communication Protocols
- UART – Fingerprint sensor communication and serial logging.
- I2C – External EEPROM communication.
- GPIO – Keypad, LCD, and motor control.
- External Interrupt – Administrator menu activation.

### Software Modules

| Source File | Responsibility |
|---|---|
| projectmain.c | Main application and authentication logic |
| R305.c | Fingerprint enrollment and identification |
| device.c | Motor-based door control |
| uart0.c | Serial monitoring and event logging |
| uart1.c | Fingerprint sensor UART communication |
| i2c.c | I2C communication |
| i2c_eeprom.c | EEPROM read and write operations |
| kpm2.c | Keypad scanning and password input |
| lcd.c | LCD initialization and display functions |
| ext_int.c | External interrupt handling |
| delay.c | Software delay functions |

### Development Environment
- LPC21xx-compatible Embedded C compiler and toolchain.
- ARM development board and hardware debugging setup.
- Serial terminal for UART log monitoring.
- LCD, keypad, fingerprint sensor, EEPROM, and motor interface hardware.

## 10. Future Enhancements

- Add RFID or NFC authentication as an additional security layer.
- Integrate Wi-Fi or Ethernet for remote access monitoring.
- Develop a web-based dashboard for real-time access logs.
- Add mobile notifications for unauthorized access attempts.
- Implement a configurable account lockout and delay mechanism after repeated failed authentication.
- Use encrypted credential storage and secure password management.
- Add door-position sensors to detect forced entry and verify actual door status.
- Introduce battery backup and power-failure alerts.
- Implement administrator authentication and role-based access control.
- Add cloud-based user management and access history.

## 11. Applications

- Office and corporate building security.
- Laboratories and research facilities.
- Restricted-access rooms.
- Industrial security systems.
- Educational institutions.
- Server rooms and equipment storage areas.

## 12. Conclusion

SecureGate Pro demonstrates an embedded multi-level biometric access control solution using an ARM7 microcontroller. By combining user ID, password, and fingerprint authentication with EEPROM storage, motorized door control, and UART event logging, the project provides a structured approach to secure access management. Its modular design also allows future integration of network connectivity, remote monitoring, and advanced security features.

**Project Category:** Embedded Systems / ARM7 / Biometric Security

**Controller:** LPC21xx ARM7

**Programming Language:** Embedded C

**Communication:** UART, I2C, GPIO

## Developed by
Yeluguri Priyanka

Project: SecureGate Pro - Intelligent Multi-Level Biometric Access Control and Intrusion Prevention System
