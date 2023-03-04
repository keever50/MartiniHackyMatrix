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
  LUM.fillScreen(0);

  
  LUM.print((int)(millis()/60000)%60);
  LUM.print(":");
  LUM.print((int)(millis()/1000)%60);
  LUM.print(":");
  LUM.print((millis()%1000));
  
  Serial.println("TEST");
  LUM.show();
  delay(1);
}