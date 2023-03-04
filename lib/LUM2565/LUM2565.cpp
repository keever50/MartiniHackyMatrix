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
    pinMode(_LUM2565_RD_PIN, INPUT);

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


    int line_select = (127-x)/16;
    if(line_select<0){line_select=0;}
    if(line_select>7){line_select=7;}

    int bit_select = (x%16);
    int row = 15-y;
    if(row<0){row=0;}
    if(row>15){row=15;}

    uint16_t line1 = buffer[line_select][row];
    uint16_t line2 = buffer[8+line_select][row];   

    if(color==0){

        line1 = line1 &~( 1 << bit_select );  
        line2 = line2 &~( 1 << bit_select );  
    }
    if(color==1)
    {
        line1 = line1 | ( 1 << bit_select );  
        line2 = line2 &~( 1 << bit_select );  
    }
    if(color==2)
    {
        line1 = line1 &~( 1 << bit_select );  
        line2 = line2 | ( 1 << bit_select );  
    }
    if(color==3)
    {
        line1 = line1 | ( 1 << bit_select );  
        line2 = line2 | ( 1 << bit_select );  
    }    

    buffer[line_select][row] = line1;
    buffer[8+line_select][row] = line2;    
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
    digitalWrite(_LUM2565_AE_PIN, HIGH);
    digitalWrite(_LUM2565_WE_PIN, HIGH);
    //Write//
    digitalWrite(_LUM2565_WE_PIN, LOW);
    digitalWrite(_LUM2565_AE_PIN, LOW);
}

void LUM2565::show()
{
    SPI.beginTransaction(SPISettings(7000000, MSBFIRST, SPI_MODE0));
    for(int y=0; y<16; y++)
    {
        //select address
        _set_address(y);

        for(int x=0; x<8; x++)
        {
            SPI.transfer16(buffer[x][y]);
        }
        for(int x=0; x<8; x++)
        {
            SPI.transfer16(buffer[8+x][y]);
        }
        _write();
    }
    _set_address(0);

    SPI.endTransaction();
}