#ifndef _MH_Z14A_PWM_H
#define _MH_Z14A_PWM_H
#include <Arduino.h>



#define MH_Z14A_PWM_PIN    0
#define MH_Z14A_PWM_INTERVAL    5

class MH_Z14A_PWM
{
public:
    MH_Z14A_PWM( unsigned long t );
    unsigned long read();

private:
    unsigned long  _TH = 0;
    unsigned long  _TL = 0;
    unsigned long  _value = 0;
    unsigned long  _next_read = 0;
};


#endif 