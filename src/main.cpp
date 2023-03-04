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
  //
  //LUM.fillScreen(0);

  //LUM.setTextColor(1);
  //LUM.print((int)(millis()/60000)%60);
  //LUM.print(":");
  //LUM.print((int)(millis()/1000)%60);
  //LUM.print(":");
  //LUM.print((millis()%1000));

  for(int i=0; i<256; i++){
    for(int y = 0; y<16;y++)
    {
      if(T>=(y/2)){T_PWM=0;}else{T_PWM=1;}
      for(int x = 0; x<128;x++)
      {

        LUM.drawPixelF(x,y,1*(1-T_PWM));
        LUM.drawPixelF(128+x,y,1*(T_PWM));
      }
    }

    T=T+1;
    if(T>8){T=0;}

    LUM.setCursor(0,0);
    LUM.setTextColor(0);
    LUM.print((int)(millis()/60000)%60);
    LUM.print(":");
    LUM.print((int)(millis()/1000)%60);
    LUM.print(":");
    LUM.print((millis()%1000));

    LUM.show();
  } 

  
 // delay(1);
}