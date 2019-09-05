// Copied from https://www.tweaking4all.com/hardware/arduino/arduino-ds18b20-temperature-sensor/

#include <Arduino.h>
#include <OneWire.h>

// DS18B20 data line on pin 4
#define SUBTEMP_PIN 4
OneWire ds(SUBTEMP_PIN);

void setup() {
  // Connect to Serial
  Serial.begin(9600);
  while (!Serial);

  pinMode(SUBTEMP_PIN, INPUT);
}

void loop() {
  // Check for input
  
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;

  // Look for a device
  if (!ds.search(addr)) {
    ds.reset_search();
    delay(250);
    return;
  }

  // CRC check to make sure data is valid
  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return;
  }

  // Reset the bus, select the device, and start conversion (what's conversion?)
  ds.reset();
  ds.select(addr);
  ds.write(0x44);
  delay(1000);

  // Read scratchpad
  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);

  /* 
   * Why Reset twice? Why do we write 0x44 and 0xBE? Why the delay? 
   */

  // Read 9 bytes
  for (i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  // Convert data to actual temperature
  int16_t raw = (data[1] << 8) | data[0];
  // cfg has something to do with resolution, don't know what it stands for
  byte cfg = (data[4] & 0x60);
  if (cfg == 0x00) raw = raw & ~7;
  else if (cfg == 0x20) raw = raw & ~3;
  else if (cfg == 0x40) raw = raw & ~1;

  celsius = (float)raw / 16.0;
  Serial.println(celsius);
}
