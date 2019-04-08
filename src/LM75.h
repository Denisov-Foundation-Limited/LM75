/* ------------------------------------------------------------
 * "THE BEERWARE LICENSE" (Revision 42):
 * <cvmanjoo@gmail.com> wrote this code. As long as you retain this
 * notice, you can do whatever you want with this stuff. If we
 * meet someday, and you think this stuff is worth it, you can
 * buy me a beer in return.
 * ------------------------------------------------------------
 * ------------------------------------------------------------
 * LM75.h - Library to get time from LM75B
 * Created by Manjunath CV. April 04 2019, 07:00 PM
 * Released into the public domain.
 * -----------------------------------------------------------*/

#ifndef LM75_H

#include <Arduino.h>
#include <Wire.h>

#define LM75_ADDR 0x48

class LM75
{
    public:
        bool begin();
        float getTemperature(void);
		float getMaxTemperature(void);
		float getMinTemperature(void);
		void setMaxTemperature(float temp);
		void setMinTemperature(float temp);
        
        void setFaultQueue(uint8_t);
        void setPolarity(bool);
        void operationMode();    
        void turnUp();
        void shutDown();
    //private:
};

/* Instantiate class

static DS3231 RTC;
static DS1307 RTC;
static NVRAM NVRAM;
static PCF8563 RTC;

*/

static LM75 LM75;
#endif   /* LM75_H */

