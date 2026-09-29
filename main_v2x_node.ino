/*
 * Project: FogGuard - V2X & Radar Collision Avoidance System
 * Hackathon: Smart India Hackathon (SIH)
 * Module: Main ESP32 V2X Processing Node
 * Features: 77GHz Radar Parsing, RTK GNSS, PM Sensor (Fog Index), IMU Anti-Rollover
 */

#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// --- Sensor Configurations ---
TinyGPSPlus gps;
HardwareSerial GNSS_Serial(1);  // RTK GNSS connected to UART1
HardwareSerial Radar_Serial(2); // 77GHz Radar connected to UART2
Adafruit_MPU6050 mpu;

// --- Vehicle & Safety Parameters ---
float currentSpeed = 0.0;       // in km/h
float obstacleDistance = 999.0; // in meters
float baseBrakingDist = 15.0;   // default safe distance in clear weather
int fogSeverityIndex = 1;       // 1 = Clear, 2 = Moderate, 3 = Severe

// --- Pin Definitions ---
const int AUTO_BRAKE_RELAY = 4;
const int HMI_WARNING_LED = 5;
const int V2X_TX_PIN = 12; // Dummy pin for C-V2X Module Trigger

void setup() {
  Serial.begin(115200);
  GNSS_Serial.begin(38400, SERIAL_8N1, 16, 17); 
  Radar_Serial.begin(115200, SERIAL_8N1, 25, 26);
  
  pinMode(AUTO_BRAKE_RELAY, OUTPUT);
  pinMode(HMI_WARNING_LED, OUTPUT);
  digitalWrite(AUTO_BRAKE_RELAY, LOW);

  // Initialize IMU for Anti-Rollover
  if (!mpu.begin()) {
    Serial.println("Failed to find IMU chip!");
  }
  Serial.println("FogGuard System Initialized. Entering Safe Mode.");
}

void loop() {
  updateGNSSData();
  obstacleDistance = readRadarDistance();
  fogSeverityIndex = calculateFogIndex(); // Reads from PM Sensor
  checkRolloverRisk();

  // ---------------------------------------------------------
  // 🧠 CORE LOGIC: ADAPTIVE FOG-RISK ENGINE
  // ---------------------------------------------------------
  
  // Dynamically increase braking distance if visibility is low
  float adaptiveBrakeZone = baseBrakingDist;
  
  if (fogSeverityIndex == 2) {
    adaptiveBrakeZone = baseBrakingDist * 1.5; // 50% larger safety buffer
  } else if (fogSeverityIndex == 3) {
    adaptiveBrakeZone = baseBrakingDist * 2.5; // 150% larger safety buffer (wet/slippery)
  }

  // Collision Avoidance Trigger
  if (obstacleDistance <= adaptiveBrakeZone) {
    triggerCollisionAvoidance();
  } else {
    digitalWrite(HMI_WARNING_LED, LOW);
  }

  delay(50); // 50ms processing loop (Real-time operations)
}

// --- Helper Functions ---

float readRadarDistance() {
  // Parses millimeter-wave data from 77GHz Radar (Simulated for Prototype)
  if (Radar_Serial.available()) {
    // String data = Radar_Serial.readStringUntil('\n');
    // Parse distance from CAN/UART payload
    return random(10, 150); // Placeholder: Returns simulated distance in meters
  }
  return 999.0;
}

int calculateFogIndex() {
  // In reality, this reads data from Sensirion SPS30 I2C sensor
  // Placeholder logic for demonstration
  int pmDensity = analogRead(34); 
  if (pmDensity > 3000) return 3; // Severe Fog/Dust
  if (pmDensity > 1500) return 2; // Moderate Fog
  return 1;                       // Clear
}

void checkRolloverRisk() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  // If truck tilt exceeds 25 degrees, send V2X alert
  if (abs(a.acceleration.x) > 4.5 || abs(a.acceleration.y) > 4.5) {
    Serial.println("CRITICAL: Vehicle Tilt Danger! Rollover Imminent.");
    broadcastV2XWarning("ROLLOVER_RISK");
  }
}

void triggerCollisionAvoidance() {
  Serial.println("WARNING: Obstacle in Adaptive Safety Zone!");
  
  // 1. Alert Driver
  digitalWrite(HMI_WARNING_LED, HIGH);
  
  // 2. Broadcast V2V Warning to trailing vehicles
  broadcastV2XWarning("HARD_BRAKING");
  
  // 3. Apply Auto-Brakes via Relay
  digitalWrite(AUTO_BRAKE_RELAY, HIGH);
  delay(1000); // Brake engage duration
  digitalWrite(AUTO_BRAKE_RELAY, LOW);
}

void broadcastV2XWarning(String alertType) {
  // Transmits payload to C-V2X Gateway
  Serial.print("V2X_TX: ");
  Serial.println(alertType);
}

void updateGNSSData() {
  while (GNSS_Serial.available() > 0) {
    gps.encode(GNSS_Serial.read());
  }
}
