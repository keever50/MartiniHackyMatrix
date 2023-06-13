#include <SDS011_PWM.h>
#include <Arduino.h>

SDS011_PWM::SDS011_PWM( int t )
{
    pinMode(SDS011_PWR_PIN, OUTPUT);
    pinMode(SDS011_PWM_PIN, INPUT);
}


//Blocking
unsigned long SDS011_PWM::read()
{
    if((millis()/1000) >= _next_read)
    {
        //Power up
        digitalWrite(SDS011_PWR_PIN, HIGH);
        delay(SDS011_PWM_STARTUP_TIME*1000);

        //Wait for the signal to come down
        while(digitalRead(SDS011_PWM_PIN) == true){};

        //Wait for signal to come up
        while(digitalRead(SDS011_PWM_PIN) == false){};
        _TH = millis();

        //Wait for the signal to come down 
        while(digitalRead(SDS011_PWM_PIN) == true){};
        _TH = millis() - _TH;
        _TL = millis();

        //Wait for the signal to come up again
        while(digitalRead(SDS011_PWM_PIN) == false){};
        _TL = millis() - _TL;


        //Calculate CO2 concentration 
        _value = 999.0*(_TH)/(_TH+_TL);

        //Scedule next read
        _next_read = (millis()/1000) + SDS011_PWM_INTERVAL;

        //Turn off 
        digitalWrite(SDS011_PWR_PIN, LOW);

        return _value;
    }else
    {
        return _value;
    }
}