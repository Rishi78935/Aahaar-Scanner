#include <Wire.h>
#include <Adafruit_AS7341.h>

Adafruit_AS7341 as7341;

#define SDA_PIN 4
#define SCL_PIN 5

String fruit = "";
String ripeness = "";
bool capturing = false;

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.println();
  Serial.println("AAHAAR DATA COLLECTOR");
  Serial.println("Starting AS7341...");

  if (!as7341.begin()) {
    Serial.println("ERROR: AS7341 NOT DETECTED");
    while (true) {
      delay(1000);
    }
  }

  as7341.setATIME(100);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_128X);

  Serial.println("AS7341 DETECTED");
  Serial.println("ESP32_READY");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("LABEL,")) {
      int firstComma = command.indexOf(',');
      int secondComma = command.indexOf(',', firstComma + 1);

      if (firstComma != -1 && secondComma != -1) {
        fruit = command.substring(firstComma + 1, secondComma);
        ripeness = command.substring(secondComma + 1);

        fruit.trim();
        ripeness.trim();

        Serial.print("LABEL_OK: ");
        Serial.print(fruit);
        Serial.print(" / ");
        Serial.println(ripeness);
      } else {
        Serial.println("ERROR: BAD LABEL FORMAT");
      }
    }
    else if (command.equalsIgnoreCase("START")) {
      if (fruit.length() == 0) {
        Serial.println("ERROR: NO FRUIT LABEL");
      }
      else if (ripeness.length() == 0) {
        Serial.println("ERROR: NO RIPENESS LABEL");
      }
      else {
        capturing = true;
        Serial.println("CAPTURE_STARTED");
      }
    }
    else if (command.equalsIgnoreCase("STOP")) {
      capturing = false;
      Serial.println("CAPTURE_STOPPED");
    }
  }

  if (capturing) {
    uint16_t readings[12];

    if (as7341.readAllChannels(readings)) {
      Serial.print("DATA");

      for (int i = 0; i < 12; i++) {
        Serial.print(",");
        Serial.print(readings[i]);
      }

      Serial.println();
    } else {
      Serial.println("ERROR: AS7341 READ FAILED");
    }

    delay(100);
  }
}
