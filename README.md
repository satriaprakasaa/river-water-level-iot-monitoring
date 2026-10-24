# 🌊 Real-Time River Water Level IoT Monitoring System

![Tools](https://img.shields.io/badge/Hardware-ESP32%20%7C%20HC--SR04-green)
![Protocols](https://img.shields.io/badge/Protocol-MQTT%20%7C%20JSON-blue)
![Dashboard](https://img.shields.io/badge/Dashboard-Node--RED%20%7C%20Cyber%20UI-red)

## 📌 Overview
Sistem pemantauan tinggi muka air sungai (*Flood Early Warning System*) berbasis Internet of Things (IoT). Sistem ini mengukur jarak permukaan air menggunakan sensor ultrasonik **HC-SR04** dan mikrokontroler **ESP32** pada titik *IoT Edge*, melakukan kalkulasi ketinggian air riil secara *real-time*, lalu mempublikasikan payload JSON via broker MQTT untuk diproses dan divisualisasikan pada **Node-RED Dashboard** (*Cyber Aqua Monitoring UI*).

---

## 🛠️ Tech Stack & Tools
- **IoT Edge Simulation:** ESP32 & Sensor Ultrasonik HC-SR04 (Wokwi Simulator)
- **Programming & Scripting:** C++ (Arduino Framework) & HTML/CSS/JS (Node-RED Dashboard UI)
- **Communication Protocol:** MQTT (Topic: `project/satria/iot`)
- **Data Payload:** JSON Format (`{"nama":"...", "tinggiAir": float, "jarakSensor": float, "tinggiTotal": int}`)
- **Dashboard Platform:** Node-RED Dashboard 2.0 (Cyber Dark UI Theme)

---

## 📐 Logic & Edge Calculation
Kalkulasi dilakukan secara langsung pada titik *edge* (ESP32) menggunakan rumus:

`tinggiAir = tinggiTotal - jarakSensor`

- **Studi Kasus:**
  - **`tinggiTotal`** = 500 cm *(Kedalaman maksimal pintu sungai)*
  - **`jarakSensor`** = 179 cm *(Jarak pembacaan sensor ultrasonik ke permukaan air)*
  - **`tinggiAir`** = 500 - 179 = **321 cm** (64%) → **Status: WASPADA**

---

## 📷 Project Preview

<table>
  <tr>
    <td align="center"><b>ESP32 Circuit Simulation (Wokwi)</b></td>
    <td align="center"><b>Cyber Aqua Monitoring Dashboard UI</b></td>
  </tr>
  <tr>
    <td align="center">
      <img src="Screenshot%202026-10-24%20165132.png" width="100%" alt="ESP32 Wokwi Simulation">
    </td>
    <td align="center">
      <img src="Screenshot%202026-10-24%20165243.png" width="100%" alt="Node-RED Dashboard">
    </td>
  </tr>
</table>

---

## 📄 JSON Data Structure
Pesan *telemetry* yang dikirimkan ESP32 ke broker MQTT:

```json
{
  "nama": "Pintu Air Satria",
  "tinggiAir": 321.0,
  "jarakSensor": 179.0,
  "tinggiTotal": 500
}
