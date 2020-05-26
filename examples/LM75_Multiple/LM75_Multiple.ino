#include <LM75.h>

float Temp0Value,Temp1Value,Temp2Value;

void setup()
{  
  
    Serial.begin(9600);
    Serial.println("Hello");

    LM75 Temp0(0x48);
    LM75 Temp1(0x4C);
    LM75 Temp2(0x4E);  

    Temp0Value = Temp0.getTemperature();
    Temp1Value = Temp1.getTemperature();
    Temp2Value = Temp2.getTemperature();

    Serial.print("Temp0 : ");
    Serial.println(Temp0Value);
    Serial.print("Temp1 : ");
    Serial.println(Temp1Value);
    Serial.print("Temp2 : ");
    Serial.println(Temp2Value);

    delay(750);      
  
}

void loop()
{
  
  
}
/*

    maxTemp = Temp0.getMaxTemperature();
    minTemp = Temp0.getMinTemperature();

    Serial.print("Min Temp : ");
    Serial.println(minTemp);
    Serial.print("Max Temp : ");
    Serial.println(maxTemp);
*/
