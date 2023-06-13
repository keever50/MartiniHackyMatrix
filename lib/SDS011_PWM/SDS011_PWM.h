#ifndef _SDS011_H
#define _SDS011_H
#include <Arduino.h>


#define SDS011_PWR_PIN          27
#define SDS011_PWM_PIN          1
#define SDS011_PWM_INTERVAL     600
#define SDS011_PWM_STARTUP_TIME 20

class SDS011_PWM
{
public:
    SDS011_PWM( int t );
    unsigned long read();

private:
    unsigned long  _TH = 0;
    unsigned long  _TL = 0;
    unsigned long  _value = 0;
    unsigned long  _next_read = 0;
};


#endif 