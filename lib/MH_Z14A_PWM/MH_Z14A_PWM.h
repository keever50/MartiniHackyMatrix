#ifndef _MH_Z14A_PWM_H
#define _MH_Z14A_PWM_H
#include <Arduino.h>



#define MH_Z14A_PWM_PIN    0
#define MH_Z14A_PWM_INTERVAL    5

class MH_Z14A_PWM
{
public:
    MH_Z14A_PWM( int t );
    uint16_t read();

private:
    int _TH = 0;
    int _TL = 0;
    int _value = 0;
    int _next_read = 0;
};


#endif 