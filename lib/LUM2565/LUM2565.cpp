#include <LUM2565.h>
#include <SPI.h>
#include <Arduino.h>

LUM2565::LUM2565( int16_t w, int16_t h ) : Adafruit_GFX( w, h )
{

}

void LUM2565::init()
{
    pinMode(_LUM2565_AE_PIN, OUTPUT);
    pinMode(_LUM2565_WE_PIN, OUTPUT);
    pinMode(_LUM2565_SE_PIN, OUTPUT);
    pinMode(_LUM2565_AB_PIN, OUTPUT);    
    pinMode(_LUM2565_ENB_PIN, OUTPUT);

    digitalWrite(_LUM2565_ENB_PIN, HIGH);
    digitalWrite(_LUM2565_SE_PIN, LOW);

    //addresses
    pinMode(_LUM2565_A0_PIN, OUTPUT);  
    pinMode(_LUM2565_A1_PIN, OUTPUT);
    pinMode(_LUM2565_A2_PIN, OUTPUT);
    pinMode(_LUM2565_A3_PIN, OUTPUT);

    SPI.setTX(_LUM2565_GR_PIN);
    SPI.setSCK(_LUM2565_CLK_PIN);
    SPI.begin();

}

void LUM2565::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    int line_select = x/16;
    int bit_select = x%16;
    int row = y;
    uint16_t line = buffer[line_select][row];
    bool bit = 1; //(color>100);

    if(bit){
        line = line | 1 << 15-bit_select;
    }
    
    buffer[line_select][row] = line;
}

void LUM2565::_set_address( int addr )
{
    digitalWrite(_LUM2565_A0_PIN, addr & 0b0001);
    digitalWrite(_LUM2565_A1_PIN, addr & 0b0010);
    digitalWrite(_LUM2565_A2_PIN, addr & 0b0100);
    digitalWrite(_LUM2565_A3_PIN, addr & 0b1000);

    Serial.print((bool)(addr & 0b0001));
    Serial.print((bool)(addr & 0b0010));
    Serial.print((bool)(addr & 0b0100));
    Serial.println((bool)(addr & 0b1000));

}

void LUM2565::_write()
{
    delay(10);
    digitalWrite(_LUM2565_AE_PIN, HIGH);
    digitalWrite(_LUM2565_WE_PIN, HIGH);
    delay(10);
    digitalWrite(_LUM2565_WE_PIN, LOW);
    digitalWrite(_LUM2565_AE_PIN, LOW);
}

void LUM2565::show()
{
    for(int y=0; y<16; y++)
    {
        //select address
        _set_address(y);

        for(int x=0; x<8; x++)
        {
            SPI.transfer16(buffer[x][y]);
        }

        _write();
    }
    _set_address(0);
}