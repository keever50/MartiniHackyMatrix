
#ifndef _LUM2565_H_
#define _LUM2565_H

#include <Adafruit_GFX.h>
#include <SPI.h>

#define _LUM2565_AE_PIN     4
#define _LUM2565_WE_PIN     5
#define _LUM2565_CLK_PIN    6
#define _LUM2565_GR_PIN     7
#define _LUM2565_SE_PIN     8
#define _LUM2565_AB_PIN     9
#define _LUM2565_ENB_PIN    10
#define _LUM2565_RD_PIN     11
#define _LUM2565_A0_PIN     12
#define _LUM2565_A1_PIN     13
#define _LUM2565_A2_PIN     14
#define _LUM2565_A3_PIN     15

#define _LUM2565_PWM_RANGE  8


class LUM2565 : public Adafruit_GFX
{
public:
    LUM2565( int16_t w, int16_t h );

    void init();
    void pwm_update();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void drawPixelF(int16_t x, int16_t y, uint16_t color);
    void drawPixelFD(int16_t x, int16_t y, uint16_t color, uint16_t color2, float mix, uint16_t dim);
    void drawPixelMix( int16_t x, int16_t y, uint16_t color, uint16_t color2, float mix );
    void show();

    uint16_t buffer[16][16];
    int pwm_time;
private:
    void _set_address(int addr );
    void _write();

};

#endif 
