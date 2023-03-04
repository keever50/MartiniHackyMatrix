#include <Arduino.h>
#include <LUM2565.h>

LUM2565 LUM(16, 64);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  LUM.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  LUM.drawLine(0,0,127,15, 1);
  Serial.println("TEST");
  LUM.show();
  delay(1000);
}