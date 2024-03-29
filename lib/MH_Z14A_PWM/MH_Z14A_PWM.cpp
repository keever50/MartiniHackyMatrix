#include <MH_Z14A_PWM.h>
#include <Arduino.h>

MH_Z14A_PWM::MH_Z14A_PWM( unsigned long t )
{
    pinMode(MH_Z14A_PWM_PIN, INPUT);
}


//Blocking
unsigned long MH_Z14A_PWM::read()
{
    if((millis()/1000) >= _next_read)
    {
        //Wait for the signal to come down
        while(digitalRead(MH_Z14A_PWM_PIN) == true){};

        //Wait for signal to come up
        while(digitalRead(MH_Z14A_PWM_PIN) == false){};
        _TH = millis();

        //Wait for the signal to come down 
        while(digitalRead(MH_Z14A_PWM_PIN) == true){};
        _TH = millis() - _TH;
        _TL = millis();

        //Wait for the signal to come up again
        while(digitalRead(MH_Z14A_PWM_PIN) == false){};
        _TL = millis() - _TL;


        //Calculate CO2 concentration 
        _value = 5000*(_TH-2)/(_TH+_TL-4);

        //Scedule next read
        _next_read = (millis()/1000) + MH_Z14A_PWM_INTERVAL;

        return _value;
    }else
    {
        return _value;
    }
}