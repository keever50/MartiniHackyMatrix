#include <Arduino.h>
#include <LUM2565.h>

LUM2565 LUM(128, 16);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  LUM.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  LUM.setCursor(0,0);
  LUM.drawLine(0,0,127,15, 1);
  LUM.drawLine(0,0,127,0, 1);
  LUM.drawLine(0,0,0,15, 1);

  LUM.println("TEST123");
  LUM.println("BOTTOM TEXT");

  Serial.println("TEST");
  LUM.show();
  delay(1000);
}