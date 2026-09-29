# FogGuard-MineSafety
Ensuring zero-accident fleet operations in zero-visibility mining environments (fog/dust) with Adaptive Radar, CM-level GNSS, and C-V2X technology


# 🚜 FogGuard: Advanced V2X & Radar-Based Collision Avoidance for Open-Cast Mines

[![Smart India Hackathon](https://img.shields.io/badge/SIH-Project-blue.svg)](#)
[![Hardware](https://img.shields.io/badge/Hardware-ESP32%20%7C%2077GHz%20Radar%20%7C%20RTK%20GNSS-orange)](#)
[![Protocol](https://img.shields.io/badge/Network-C--V2X%20%7C%20UWB-success)](#)
[![Status](https://img.shields.io/badge/Status-Industrial%20Prototype-brightgreen)](#)

> **Ensuring zero-accident fleet operations in zero-visibility mining environments (fog/dust) with Adaptive Radar, CM-level GNSS, and C-V2X technology.**

---

## 🛑 The Problem
Open-cast iron ore mines are extreme environments. Heavy Earth Moving Machinery (HEMM) operating on steep, uneven haul roads frequently encounter **zero-visibility conditions** due to dense morning fog and continuous dust clouds. Traditional optical sensors (Cameras/LiDAR) fail in these conditions, leading to fatal vehicle-to-vehicle collisions, edge-drops, and worker accidents.

## 💡 The Solution: FogGuard Ecosystem
FogGuard is not just a sensor; it is a **reactive, V2X-enabled ecosystem** designed specifically for harsh mining conditions. By fusing 77GHz 4D Imaging Radar (which easily penetrates thick fog and dust) with Centimeter-level RTK GNSS, the system provides infallible collision avoidance, dynamic safety zones, and a live digital twin for the control room.

---

## ✨ Key Advanced Features

* 🌫️ **Adaptive Fog-Risk Engine:** An onboard PM (Visibility) sensor dynamically calculates a real-time 'Fog Severity Index'. As visibility drops, the system automatically extends the auto-braking distance to compensate for wet/slippery terrain.
* 🛰️ **Dynamic Geo-Fencing & Speed Limiting:** Uses RTK GNSS to restrict HEMM speeds automatically when entering high-risk zones (e.g., steep curves, dumping edges) and prevents fatal reverse-dumping edge-drops.
* ⚖️ **Anti-Rollover & Tilt Prevention:** Utilizes a 3-axis IMU to monitor vehicle tilt angles on uneven mine roads, alerting drivers instantly before a rollover occurs.
* 📡 **Reactive V2X Mapping (Crowdsourced Safety):** If a vehicle's suspension dips abnormally in soft/sinking ground, the IMU detects it, GNSS tags the location, and C-V2X warns the entire fleet to change lanes instantly.
* 👷 **UWB Worker Safety Tags:** Ground workers wear UWB haptic tags that vibrate intensely when a heavy vehicle approaches, ensuring safety even in high-noise zones (drilling/blasting) and radar blind spots.

---

## 🛠️ Industrial Hardware Architecture

To ensure 100% reliability in harsh open-cast environments, the system utilizes commercial-grade components:

1. **Obstacle Detection:** `77 GHz Automotive 4D Radar` (150-300m range, unaffected by fog/dust).
2. **Precision Positioning:** `u-blox ZED-F9P RTK GNSS` (Centimeter-level accuracy).
3. **Communication:** `C-V2X / Industrial Gateway` (Ultra-low latency, decentralized V2V data sharing).
4. **Environment Sensing:** `Sensirion SPS30-class PM Sensor` (Fog & Dust density).
5. **Edge Processing:** `Automotive-Grade MCU (AEC-Q100)` (High heat and vibration tolerance).
6. **Worker Tracking:** `Ultra-Wideband (UWB) Anchor Network & Wearables`.

---

## 🛡️ Fail-Safes & Environmental Robustness (Why it won't fail)

We engineered FogGuard anticipating the harshest mining realities:
* **Dust Immunity:** All processing units and sensors are housed in **IP69K Ruggedized Enclosures**. Radar radomes are equipped with pneumatic air-jets (tapped from the truck's compressor) to prevent mud accumulation.
* **GPS-Denied Zones (Deep Pits):** If RTK GNSS signal drops due to steep pit walls (multipath/drift), the system seamlessly switches to **Dead Reckoning via High-Grade INS (Inertial Navigation System)** to maintain positional awareness.
* **UWB NLoS (Non-Line-of-Sight):** A self-healing mesh topology ensures that if an anchor is physically damaged by a rockfall, data routes through adjacent active nodes.

---

## 🖥️ Live Digital Twin (Control Room)
All telemetry data (Brake events, Fog Index, GNSS coordinates, Road Heatmaps) is transmitted to the control room, creating a live 3D Digital Twin of the mining operation for the fleet manager.

---

## 🚀 Setup & Demonstration (SIH Prototype)
*(Note: This section contains instructions for reproducing the ESP32/Arduino prototype built for the hackathon pitch.)*

1. Clone the repository: `git clone https://github.com/aditya-esys/FogGuard-MineSafety.git`
2. Install necessary libraries in Arduino IDE (e.g., `TinyGPS++`, `ESP32-CAN`, `Adafruit_Sensor`).
3. Connect the Dev-Board as per the `circuit_diagram.pdf` in the `/docs` folder.
4. Upload `main_v2x_node.ino` to the primary vehicle unit.

---
*Built with ⚙️ for Smart India Hackathon*

<img width="4032" height="2268" alt="6342" src="https://github.com/user-attachments/assets/b3a5dd66-a317-47dc-9439-fd653c71f0c1" />
<img width="4032" height="2268" alt="jpgy 6337" src="https://github.com/user-attachments/assets/87a3e64e-623e-4d28-bb48-a994dfdd0edf" />
<img width="4032" height="2268" alt="jpg 6335" src="https://github.com/user-attachments/assets/e29591c6-c310-4ab1-bf63-f7f2579d5e73" />





