
#include <Arduino.h>
#include <LUM2565.h>
#include <MH_Z14A_PWM.h>
#include <TimeLib.h>

LUM2565 LUM(128, 16);
MH_Z14A_PWM CO2( 1 );


void printTimeDigit(int n )
{
  if(n<10)
  {
    LUM.print("0");
    LUM.print(n);
  }else
  {
    LUM.print(n);
  }

}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  LUM.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  //
  LUM.fillScreen(0);
  
  
  LUM.setCursor(0,0);
  LUM.setTextColor(1);
  printTimeDigit((int)(millis()/3600000)%60);  
  LUM.print(":");  
  printTimeDigit((int)(millis()/60000)%60);
  LUM.print(":");
  printTimeDigit((int)(millis()/1000)%60);

  LUM.setCursor(64,0);
  LUM.print("CO2");
  LUM.setCursor(64,8);
  LUM.print(CO2.read());
  LUM.print("ppm");

  LUM.show();
  
 // delay(1);
}