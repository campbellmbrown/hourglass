#include <Wire.h>
#include <Arduino.h>
#include <U8g2lib.h>

#define TMP102_ADDRESS 0x48   // Default I2C address for TMP102

static U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);  // High speed I2C

void setup(void) {
  Wire.begin();               // Start I2C communication
  u8g2.begin();               // Initialize the display
  Serial.begin(9600);         // For debugging, if needed
}

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

void loop(void) {
  float temperature = readTemperatureTMP102();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB12_tr);

  if (!isnan(temperature)) {
    // Prepare the temperature string to display
    char tempString[16];
    Serial.println(temperature);
    int tempInt = (int)temperature;
    int tempDec = (int)((temperature - tempInt) * 100);
    snprintf(tempString, sizeof(tempString), "Temp: %d.%02d C", tempInt, tempDec);
    Serial.println(tempString);

    u8g2.drawStr(0, 20, tempString);    // Display temperature string
  } else {
    u8g2.drawStr(0, 20, "Sensor Error"); // Show error if reading failed
  }

  u8g2.sendBuffer();                    // Transfer memory to the display
  delay(1000);                          // Update once per second
}