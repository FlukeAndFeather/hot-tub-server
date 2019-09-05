#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define INPUT_SZ 10

// DS18B20 data line on pin 4
#define TS_PIN 4
OneWire ts_onewire(TS_PIN);
DallasTemperature ts_dallas(&ts_onewire);

void setup() {
  // Connect to Serial
  Serial.begin(9600);
  while (!Serial);

  // Start Dallas temperature library
  ts_dallas.begin();
}

void loop() {
  char input[INPUT_SZ + 1], command[INPUT_SZ + 1], arg[INPUT_SZ + 1];
  char input_sep[] = ":";
  
  // Check for input
  if (Serial.available() > 0) {
    readInput(input, command, arg, input_sep);
    if (strcmp(command, "TS") == 0) {
      float result = readTs();
      Serial.print("TS:");
      Serial.println(result);
    }
  }
}

void readInput(char* input, char* comm, char* arg, char* sep) {
  byte size = Serial.readBytes(input, INPUT_SZ);
  // Add a terminal 0 to complete the string
  input[size] = 0;

  // Split input into command and argument
  char *pch = strtok(input, sep);
  strcpy(comm, pch);
  pch = strtok(NULL, sep);
  strcpy(arg, pch);
}

float readTs() {
  ts_dallas.requestTemperatures();
  return ts_dallas.getTempCByIndex(0);
}
