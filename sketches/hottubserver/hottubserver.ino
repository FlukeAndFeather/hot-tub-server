#include <Arduino.h>

#define INPUT_SZ 10

void setup() {
  // Connect to Serial
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  char input[INPUT_SZ + 1], *comm, *arg;
  
  // Check for input
  if (Serial.available() > 0) {
    byte size = Serial.readBytes(input, INPUT_SZ);
    // Add a terminal 0 to complete the string
    input[size] = 0;
    Serial.println(input);
  }
}
  /*
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
/*
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
*/
