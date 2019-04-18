/*
* LM75.cpp - Library to get time from LM75B
* Created by Manjunath CV. April 04 2019, 07:00 PM
* Released into the public domain.
*/

///#include <math.h>
#include <Arduino.h>
#include <Wire.h>
#include <LM75.h>

LM75::LM75()
{
  Wire.begin(); // join i2c bus
  Wire.beginTransmission(0x48);
  status = Wire.endTransmission();
  //Serial.println("Debug : In Constructor!");
}

LM75::LM75(uint8_t address)
{
  lm75_addr = address;

  Wire.begin(); // join i2c bus
  Wire.beginTransmission(address);
  status = Wire.endTransmission();

  //Serial.println(lm75_addr);
  //Serial.println("Debug : In Constructor!");
  //return (Wire.endTransmission() == 0 ?  true : false);
}

float LM75::getTemperature(void)
{
    int8_t temp_msb, temp_lsb;
    float temp;

    Wire.beginTransmission(lm75_addr);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(lm75_addr, 2);
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

    Wire.beginTransmission(lm75_addr);
    Wire.write(0x03);
    Wire.endTransmission();
    Wire.requestFrom(lm75_addr, 2);
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

    Wire.beginTransmission(lm75_addr);
    Wire.write(0x03);
    Wire.write(temp_msb);
    Wire.write(temp_lsb);
    Wire.endTransmission();
}


float LM75::getMaxTemperature(void)
{
    int8_t temp_msb, temp_lsb;
    float temp;

    Wire.beginTransmission(lm75_addr);
    Wire.write(0x02);
    Wire.endTransmission();
    Wire.requestFrom(lm75_addr, 2);
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

    Wire.beginTransmission(lm75_addr);
    Wire.write(0x02);
    Wire.write(temp_msb);
    Wire.write(temp_lsb);
    Wire.endTransmission();
}
