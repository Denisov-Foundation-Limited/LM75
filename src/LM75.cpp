/*
* LM75.cpp - Library to get time from LM75B
* Created by Manjunath CV. April 04 2019, 07:00 PM
* Released into the public domain.
*/

///#include <math.h>
#include <Arduino.h>
#include <Wire.h>
#include <LM75.h>

bool LM75::begin()
{
    Wire.begin(); // join i2c bus
    Wire.beginTransmission (LM75_ADDR);
    return (Wire.endTransmission() == 0 ?  true : false);
}

float LM75::getTemperature(void)
{
    int8_t temp_msb, temp_lsb;
    float temp;

    Wire.beginTransmission(LM75_ADDR);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(LM75_ADDR, 2);
    temp_msb = Wire.read();
    temp_lsb = Wire.read();

    temp_lsb = temp_lsb >> 5;
    
    temp = temp_msb + (temp_lsb * 0.125);

    return (temp);
}


float LM75::getMinTemperature(void)
{
    int8_t temp_msb, temp_lsb;
    float temp;

    Wire.beginTransmission(LM75_ADDR);
    Wire.write(0x03);
    Wire.endTransmission();
    Wire.requestFrom(LM75_ADDR, 2);
    temp_msb = Wire.read();
    temp_lsb = Wire.read();

    temp_lsb = temp_lsb >> 7;
    
    temp = temp_msb + (temp_lsb * 0.5);

    return (temp);
}


void LM75::setMinTemperature(float temp)
{
    int8_t temp_msb, temp_lsb;

    temp_msb = round(temp);
    
    if((temp-temp_msb) >= 0.5)
        temp_lsb = 0x80;  
    else
        temp_lsb = 0x00;
         
    Wire.beginTransmission(LM75_ADDR);
    Wire.write(0x03);
    Wire.write(temp_msb);
    Wire.write(temp_lsb);
    Wire.endTransmission();
}


float LM75::getMaxTemperature(void)
{
    int8_t temp_msb, temp_lsb;
    float temp;

    Wire.beginTransmission(LM75_ADDR);
    Wire.write(0x02);
    Wire.endTransmission();
    Wire.requestFrom(LM75_ADDR, 2);
    temp_msb = Wire.read();
    temp_lsb = Wire.read();

    temp_lsb = temp_lsb >> 7;
    
    temp = temp_msb + (temp_lsb * 0.5);

    return (temp);
}


void LM75::setMaxTemperature(float temp)
{
    int8_t temp_msb, temp_lsb;

    temp_msb = round(temp);
    
    if((temp-temp_msb) >= 0.5)
        temp_lsb = 0x80;
    else
      temp_lsb = 0x00;

    Wire.beginTransmission(LM75_ADDR);
    Wire.write(0x02);
    Wire.write(temp_msb);
    Wire.write(temp_lsb);
    Wire.endTransmission();
}
