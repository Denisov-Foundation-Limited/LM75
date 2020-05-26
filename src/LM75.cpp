/*
* LM75.cpp - Library to get time from LM75B
* Created by Manjunath CV. April 04 2019, 07:00 PM
* Released into the public domain.
*/

#include <Arduino.h>
#include <Wire.h>
#include <LM75.h>

LM75::LM75()
{	Wire.begin();
    _address = LM75_DFLT_ADDR;
	Wire.endTransmission();
}

LM75::LM75(uint8_t address)
{
	Wire.begin();
    _address = address;
	Wire.endTransmission();
}

float LM75::getTemperature(void)
{
    int8_t temp_msb, temp_lsb;
    float temp;

    Wire.beginTransmission(_address);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(_address, 2);
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

    Wire.beginTransmission(_address);
    Wire.write(0x03);
    Wire.endTransmission();
    Wire.requestFrom(_address, 2);
    temp_msb = Wire.read();
    temp_lsb = Wire.read();

    temp_lsb = temp_lsb >> 7;
    temp = temp_msb + (temp_lsb * 0.5);

    return (temp);
}
/*
	round up to be tested
*/

void LM75::setMinTemperature(float temp)
{
    int8_t temp_msb, temp_lsb;

    temp_msb = round(temp);

    if((temp-temp_msb) >= 0.5)
        temp_lsb = 0x80;
    else
        temp_lsb = 0x00;

    Wire.beginTransmission(_address);
    Wire.write(0x03);
    Wire.write(temp_msb);
    Wire.write(temp_lsb);
    Wire.endTransmission();
}


float LM75::getMaxTemperature(void)
{
    int8_t temp_msb, temp_lsb;
    float temp;

    Wire.beginTransmission(_address);
    Wire.write(0x02);
    Wire.endTransmission();
    Wire.requestFrom(_address, 2);
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

    Wire.beginTransmission(_address);
    Wire.write(0x02);
    Wire.write(temp_msb);
    Wire.write(temp_lsb);
    Wire.endTransmission();
}


void LM75::turnUp()
{
	uint8_t data;

    Wire.beginTransmission(_address);
    Wire.write(0x01);
    Wire.endTransmission();
    Wire.requestFrom(_address, 1);
    data = Wire.read();

	bitClear(data,0);
	
	Wire.beginTransmission(_address);
    Wire.write(0x01);
	Wire.write(data);
    Wire.endTransmission();
}

void LM75::shutDown()
{
	uint8_t data;

    Wire.beginTransmission(_address);
    Wire.write(0x01);
    Wire.endTransmission();
    Wire.requestFrom(_address, 1);
    data = Wire.read();

	bitSet(data,0);
	
	Wire.beginTransmission(_address);
    Wire.write(0x01);
	Wire.write(data);
    Wire.endTransmission();
}

void LM75::setOperationMode(bool mode)
{
	uint8_t data;
	
	Wire.beginTransmission(_address);
    Wire.write(0x01);
    Wire.endTransmission();
    Wire.requestFrom(_address, 1);
    data = Wire.read();
	
	if (mode == COMPARATOR)
	{
		bitClear(data,1);
	}
	else
	{
		bitSet(data,1);
	}
	Wire.beginTransmission(_address);
    Wire.write(0x01);
	Wire.write(data);
    Wire.endTransmission();
}

bool LM75::getOperationMode()
{
	uint8_t data;
	
	Wire.beginTransmission(_address);
    Wire.write(0x01);
    Wire.endTransmission();
    Wire.requestFrom(_address, 1);
    data = Wire.read();
	
	bitRead(data,1);
}

void LM75::setPolarity(bool polarity)
{
	uint8_t data;
	
	Wire.beginTransmission(_address);
    Wire.write(0x01);
    Wire.endTransmission();
    Wire.requestFrom(_address, 1);
    data = Wire.read();
	
	if (polarity == LOW)
	{
		bitClear(data,2);
	}
	else
	{
		bitSet(data,2);
	}
	Wire.beginTransmission(_address);
    Wire.write(0x01);
	Wire.write(data);
    Wire.endTransmission();
    
}

bool LM75::getPolarity()
{
	uint8_t data;
	Wire.beginTransmission(_address);
    Wire.write(0x01);
    Wire.endTransmission();
    Wire.requestFrom(_address, 1);
    data = Wire.read();
	data = bitRead(data,2);
	
	return(data);
}

void LM75::setFaultQueue(uint8_t value)
{
	uint8_t data;
	
	Wire.beginTransmission(_address);
    Wire.write(0x01);
    Wire.endTransmission();
    Wire.requestFrom(_address, 1);
    data = Wire.read();
    
    switch(value)
    {
		case 1:
			bitClear(data,3);
			bitClear(data,4);
			break;
		case 2:
			bitSet(data,3);
			bitClear(data,4);
			break;
		case 4:
			bitClear(data,3);
			bitSet(data,4);
			break;
		case 8:
			bitSet(data,3);
			bitSet(data,4);
			break;
		default:
			bitClear(data,3);
			bitClear(data,4);
			break;
	}
	Wire.beginTransmission(_address);
    Wire.write(0x01);
	Wire.write(data);
    Wire.endTransmission();	
}

uint8_t LM75::getFaultQueue(void)
{
	uint8_t data;	
	Wire.beginTransmission(_address);
    Wire.write(0x01);
    Wire.endTransmission();
    Wire.requestFrom(_address, 1);
    data = Wire.read();
    
    data = data >> 3;
    switch(data)
    {
		case 0:
			return 1;
			break;
		case 1:
			return 2;
			break;
		case 2:
			return 4;
			break;
		case 3:
			return 8;
			break;
		default:
			return 1;
			break;
	}
	return data;
}




