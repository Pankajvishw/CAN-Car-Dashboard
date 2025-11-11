# 🚗 CAN-Based Car Dashboard System (3-ECU Communication using CAN Protocol)

This project simulates a **car dashboard system** using the **Controller Area Network (CAN)** protocol with **three ECUs (Electronic Control Units)** — similar to how real automotive systems communicate internally.  
Each ECU performs a dedicated role to collectively represent a functional vehicle dashboard.

---

## 🧩 Project Overview

| ECU | Function | Description |
|-----|-----------|-------------|
| **ECU1** | Speed & Gear ECU | Reads vehicle speed and gear position and transmits over CAN bus. |
| **ECU2** | RPM & Indicator ECU | Reads engine RPM and indicator status (Left, Right, Hazard, Off). |
| **ECU3** | Dashboard ECU | Receives CAN messages and displays Speed, Gear, RPM, and Indicators on CLCD. |

---

## ⚙️ Key Features

- Multi-ECU communication using **CAN Bus Protocol**
- Real-time display of **Speed, Gear, RPM**, and **Indicator Status**
- **Collision alert** when gear is set to collision gear (`Gr`)
- Indicator control with blinking arrows (`<`, `>`)
- Modular design for each ECU
- Built using **PIC18F4580**, **MPLAB X IDE**, and **XC8 Compiler**

---

## 🛠️ Hardware & Software Details

| Component | Description |
|------------|-------------|
| **Microcontroller** | PIC18F4580 (with inbuilt CAN module) |
| **Compiler** | MPLAB XC8 |
| **IDE** | MPLAB X |
| **Display** | 16x2 Character LCD (CLCD) |
| **Communication Protocol** | CAN Bus |
| **Input Devices** | Matrix Keypad (for gear and indicator control) |

---

## ⚡ CAN Message Mapping

| Message ID | Sent From | Description | Data Length |
|-------------|------------|--------------|--------------|
| `SPEED_MSG_ID` | ECU1 | Vehicle speed (km/h) | 3 bytes |
| `GEAR_MSG_ID` | ECU1 | Gear position (1–8) | 1 byte |
| `RPM_MSG_ID` | ECU2 | Engine RPM | 5 bytes |
| `INDICATOR_MSG_ID` | ECU2 | Indicator status (left/right/hazard/off) | 1 byte |

---

## ⚠️ Collision Alert Logic

- When the **gear position is set to 8 (Gr)**, the system detects a potential collision.
- The dashboard (ECU3) clears the display and shows:


- Normal dashboard updates are paused during this state.
- Once the gear is changed back to any normal position, the dashboard display is restored automatically.

---

## 🚦 System Behavior Summary

| Condition | ECU | Behavior |
|------------|-----|-----------|
| Gear Up / Down | ECU1 | Sends updated gear and speed values over CAN |
| Collision Gear (Gr) | ECU1 → ECU3 | Displays collision alert and stops normal updates |
| Indicator Left / Right / Hazard | ECU2 → ECU3 | Updates corresponding indicator symbols on CLCD |
| Speed / RPM | ECU1 & ECU2 → ECU3 | Continuously updated and displayed in real-time |

---

## 🧠 Learning Outcomes

- Understanding **CAN bus communication** in distributed embedded systems  
- Synchronization of multiple ECUs via message-based protocol  
- Real-time data visualization using **Character LCD**  
- Designing modular embedded systems for automotive applications  

---

## 📸 Suggested Images for GitHub

- 🖼️ **CAN network topology** showing ECU1–ECU2–ECU3  
- 💻 **LCD display photo** showing Speed, Gear, and Indicators  
- ⚙️ **Hardware setup photo** (breadboard/PCB connections)

---

## 👤 Author

**Pankaj Kumar**  
Embedded Systems Enthusiast | B.Tech ECE Graduate  
📎 [LinkedIn](https://linkedin.com/in/your-profile)  
💻 [GitHub](https://github.com/your-username)

---

## 🏷️ Tags

`Embedded Systems` `CAN Protocol` `PIC18F4580` `Automotive Electronics` `XC8 Compiler` `MPLAB X` `CLCD` `Microcontroller Programming`

---

## 📜 License

This project is open-source and available under the **MIT License**.
