#include <Arduino.h>
#include <LUM2565.h>

LUM2565 LUM(128, 16);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  LUM.init();
}

int T = 0;
int T_PWM = 0;
void loop() {
  // put your main code here, to run repeatedly:
  LUM.setCursor(0,0);
  LUM.fillScreen(0);

  //LUM.setTextColor(1);
  //LUM.print((int)(millis()/60000)%60);
  //LUM.print(":");
  //LUM.print((int)(millis()/1000)%60);
  //LUM.print(":");
  //LUM.print((millis()%1000));
  
  LUM.drawRect(0,0,10,10,2);
  LUM.drawRect(11,0,10,10,1);


  LUM.drawRect(((millis()/50)%118),0,10,10,3*T_PWM);
  LUM.drawRect(((millis()/60)%118),0,10,10,3);

  T=T+1;
  if(T>10){T=0;}
  if(T>9){T_PWM=1;}else{T_PWM=0;}

  LUM.show();
 // delay(1);
}