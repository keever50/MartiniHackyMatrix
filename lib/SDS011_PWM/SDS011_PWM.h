#ifndef _SDS011_H
#define _SDS011_H
#include <Arduino.h>


#define SDS011_PWR_PIN          27
#define SDS011_PWM_PIN          1
#define SDS011_PWM_INTERVAL     120
#define SDS011_PWM_STARTUP_TIME 10

class SDS011_PWM
{
public:
    SDS011_PWM( int t );
    float read();

private:
    float _TH = 0;
    float _TL = 0;
    float _value = 0;
    float _next_read = 0;
};


#endif 