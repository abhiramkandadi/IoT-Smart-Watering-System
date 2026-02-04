# ENGR 111: Smart Watering System
An automated irrigation solution developed at **Stevens Institute of Technology**. This project integrates hardware and software to maintain optimal soil moisture levels using a **WeMos D1 R2 (ESP8266)**.

## 🌿 Project Overview
The Smart Watering System is designed to automate plant care by monitoring soil moisture in real-time. When moisture levels drop below a calibrated threshold, the system triggers a water pump via relay logic to deliver precise hydration, preventing both underwatering and soil saturation.

## 🛠️ Technical Specifications
* **Microcontroller**: WeMos D1 R2 (ESP8266).
* **Communication**: Serial data feedback at **115200 baud** for real-time debugging.
* **Programming Language**: C++ (Arduino Framework).
* **Key Components**: 
    * Analog Soil Moisture Sensor.
    * 5V Relay Module & Submersible Water Pump.
    * Ultrasonic Sensor (optional monitoring).

## 💻 System Logic & Execution
The program follows a structured execution flow to ensure hardware stability:
1. **Initialization**: Configures Serial communication at 115200 baud.
2. **Sensing**: Continuously reads analog values from the moisture sensor.
3. **Control**: Compares values against a threshold; if the soil is dry, the relay activates the pump.
4. **Safety Delay**: Incorporates a `delay()` to allow water percolation and prevent rapid power cycling.

## ⚠️ Hardware & Safety Notes
* **Pin Configuration**: Specific pins (like D4/GPIO2) are used for stability to ensure the board boots correctly and allows for successful code uploads.
* **Continuity Testing**: Before powering the system, a continuity test must be performed with the **circuit turned off** to verify connections and prevent multimeter damage.

## 🚀 How to Use
1. Clone the repository: `git clone https://github.com/bobbyshark-exe/Smart-Watering-System.git`.
2. Open the `.ino` sketch in **Arduino IDE v2.3.7**.
3. Set your board to **LOLIN(WEMOS) D1 R2 & mini**.
4. Upload and monitor the output via the Serial Monitor at **115200 baud**.

---
**Developer**: Abhiram Reddy Kandadi
**Major**: Computer Engineering, Stevens Institute of Technology
**GitHub**: [bobbyshark-exe](https://github.com/abhiramkandadi)
