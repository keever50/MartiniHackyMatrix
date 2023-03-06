
#include <Arduino.h>
#include <LUM2565.h>
#include <MH_Z14A_PWM.h>
#include <SDS011_PWM.h>
#include <TimeLib.h>
#include <DHT.h>

#define DISP_CLOCK_WIDTH   48
#define DISP_CO2_WIDTH     4*6

LUM2565 LUM(128, 16);
MH_Z14A_PWM CO2( 1 );
SDS011_PWM PM25( 1 );
DHT DHT_sensor(2,22);


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

void print4Digit(int n )
{
  if(n<10)
  {
    LUM.print("000");
    LUM.print(n);
    return;
  }

  if(n<100)
  {
    LUM.print("00");
    LUM.print(n);
    return;
  }

  if(n<1000)
  {
    LUM.print("0");
    LUM.print(n);
    return;
  }

}


void drawVerticalMeterBar( int x, int y, int length, int thickness, int n, float min, float max )
{

  float v = (((float)n-min) / (max-min));
  v = 1-v;
  for(int l = 0; l<length; l++)
  {
    float mix = (float)l/((float)length-1);
    if(mix>=v)
    {
      
      for(int expand = 0; expand < thickness; expand++)
      {
        if(n<max){
          LUM.drawPixelMix(x+expand,y+l, 1, 2, mix);
        }else
        {
          LUM.drawPixel(x+expand,y+l, 1 );  
        }
        
      }
    }

    
  }
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  LUM.init();
  DHT_sensor.begin();
}

int CO2_value = 0;
int PM25_value = 0;
int temp_value = 0;
int humid_value = 0;

void loop() {
  // put your main code here, to run repeatedly:
  //
  LUM.pwm_update();

  LUM.fillScreen(0);
  
  //TIME
  LUM.setCursor(0,0);
  LUM.setTextColor(1);
  printTimeDigit((int)(millis()/3600000)%60);  
  LUM.print(":");  
  printTimeDigit((int)(millis()/60000)%60);
  LUM.print(":");
  printTimeDigit((int)(millis()/1000)%60);

  //CO2
  LUM.setCursor(DISP_CLOCK_WIDTH+6,0);
  LUM.print("CO2");
  LUM.setCursor(DISP_CLOCK_WIDTH+6,8);
  print4Digit(CO2_value);
  drawVerticalMeterBar(DISP_CLOCK_WIDTH+2, 0, 16, 3, CO2_value, 450, 1500 );

  //DUST
  LUM.setCursor(DISP_CLOCK_WIDTH+DISP_CO2_WIDTH+12,0);
  LUM.print("PM2.5");
  LUM.setCursor(DISP_CLOCK_WIDTH+DISP_CO2_WIDTH+12,8);
  print4Digit(PM25_value);
  drawVerticalMeterBar(DISP_CLOCK_WIDTH+DISP_CO2_WIDTH+8, 0, 16, 3, PM25_value, 0, 250 );

  //T/H
  LUM.setCursor(0,8);
  LUM.print(" T");
  printTimeDigit(temp_value);
  LUM.print(" H");
  printTimeDigit(humid_value);
  drawVerticalMeterBar(2, 8, 8, 3, temp_value, 0, 30 );
  drawVerticalMeterBar(22+4, 8, 8, 3, humid_value, 0, 70 );

  LUM.show();
  
 // delay(1);
}



void loop1()
{
  CO2_value = CO2.read();
  PM25_value = (int)PM25.read();
  temp_value = DHT_sensor.readTemperature();
  humid_value = DHT_sensor.readHumidity();

  delay(1000);

}