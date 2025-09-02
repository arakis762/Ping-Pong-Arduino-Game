# 🏓 Arduino Ping-Pong Game

This is a simple **Ping Pong game** built with Arduino and a 128×64 OLED display.  
One paddle is controlled by the player using two buttons, while the other paddle is programmed to always follow the ball — meaning it never loses!  

---

## ⚡ Features
- Player paddle controlled with **Up/Down buttons**  
- Opponent paddle always tracks the ball (no AI, it’s unbeatable)  
- Ball bounces realistically off walls and paddles  
- Automatic reset when a point is scored  

---

## 🛠️ Hardware Requirements
- Arduino Nano (other Arduino models can be used)  
- SSH1106 (128×64 OLED display)   
- 2 push buttons (12x12x1mm) (for UP and DOWN movement)  
- Breadboard & jumper wires
- IC205 switch (on off switch) (other types can be used)
- MakerFocus 4pcs 952540 3.7V 1000mAh (other power sources that fits can also be used)

---

## 🔌 Wiring
- **OLED Display:** connected via I2C (SDA, SCL)  
- **Buttons:** connected to pins `2` (Up) and `3` (Down)

---

## 📂 Files
- `pingpongarduino.ino` → Main Arduino code for the game  

---

## ▶️ How to Play
1. Connect the circuit and upload the sketch to your Arduino.  
2. Use the **Up** and **Down** buttons to move your paddle.  
3. Try to hit the ball — but beware, the programmed paddle never misses!  

---

## 📸 Demo
coming...

---

## 🚀 Future Improvements
- Add scoring system  
- Make the CPU paddle “human-like” (so it can lose sometimes)  
- Add sound effects with a buzzer  

---

## 📜 License
This project is open-source under the [MIT License](LICENSE).  
Feel free to improve and share! 🎉