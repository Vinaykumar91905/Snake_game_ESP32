# 🐍 Snake Game on 8x8 LED Matrix (ESP32 + Bluetooth)

A classic Snake game implemented on an ESP32 Devkit V1 using an 8x8 MAX7219 LED matrix and Bluetooth-based controls. The game includes food generation, snake growth, self-collision detection, and buzzer feedback. Fully tested on real hardware.

---

## 🎯 Features

- Snake controlled via Bluetooth commands (U, D, L, R)
- MAX7219 8x8 LED matrix for visual gameplay
- Game restarts on collision with self
- Buzzer beeps on eating food or crashing
- Wrap-around edges (no walls)

---

## 🧰 Hardware Used

- ESP32 Devkit V1  
- MAX7219 8x8 LED Matrix  
- Passive Buzzer  
- Android phone with [Serial Bluetooth Terminal]

---

## 🔌 Pin Connections

| Component     | ESP32 Pin |
|---------------|-----------|
| LED Matrix DIN| GPIO 23   |
| LED Matrix CS | GPIO 5    |
| LED Matrix CLK| GPIO 18   |
| Buzzer (+)    | GPIO 15   |
| GND (All)     | GND       |

---

## 📲 Bluetooth Controls

- Connect via **Serial Bluetooth Terminal**
- Device Name: `ESP32Snake`
- Controls:
  - `U` = Up
  - `D` = Down
  - `L` = Left
  - `R` = Right

---

## ⚙️ Game Logic

- Snake starts with length 3, moves right
- Food spawns randomly (never overlaps snake)
- Snake grows on eating food
- Collision with self resets the game
- `tone()` used for buzzer feedback

---

## 🧪 Tested On

- Real ESP32 hardware (not simulated)
- Live control from Android phone
- Verified matrix, buzzer, Bluetooth, and game logic

---

## 📈 Future Improvements

- Score tracking
- Speed-up with time
- Pause/Resume or restart button
- Two-player or joystick support

---

🎥 [View Demo on Google Drive](https://drive.google.com/file/d/your_file_id/view)


## 🛠️ Setup

```bash
# PlatformIO / Arduino IDE
Framework: Arduino  
Board: ESP32 Devkit V1  
Library: MD_MAX72XX, BluetoothSerial



