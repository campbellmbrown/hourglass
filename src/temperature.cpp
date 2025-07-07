#include "temperature.hpp"
#include <Wire.h>
#include <Arduino.h>

#define TMP102_ADDRESS 0x48   // Default I2C address for TMP102

float readTemperatureTMP102() {
  Wire.beginTransmission(TMP102_ADDRESS);
  Wire.write(0x00);                 // Point to temperature register
  Wire.endTransmission();

  Wire.requestFrom(TMP102_ADDRESS, 2);   // Request 2 bytes from TMP102
  Serial.print("Wire.available(): ");
  Serial.println(Wire.available());

  if (Wire.available() == 2) {           // Check if 2 bytes were received
    byte msb = Wire.read();              // Read the most significant byte
    byte lsb = Wire.read();              // Read the least significant byte

    // Combine bytes and convert to temperature
    int16_t tempRaw = ((msb << 8) | lsb) >> 4;   // 12-bit temperature
    float temperature = tempRaw * 0.0625;        // TMP102 scale factor


    return temperature;
  } else {
    return NAN;  // Return NaN if reading failed
  }
}
