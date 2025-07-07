#include <Wire.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include "src/temperature.hpp"

static U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);  // High speed I2C

void setup(void) {
  Wire.begin();               // Start I2C communication
  u8g2.begin();               // Initialize the display
  Serial.begin(9600);         // For debugging, if needed
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
