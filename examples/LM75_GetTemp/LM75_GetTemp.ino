#include <Wire.h>

int8_t temp_msb, temp_lsb;
float Temp;

void setup() {
  
    Serial.begin(9600);
    Serial.println("Hello");
    Wire.begin(); 
}

void loop() {

    Wire.beginTransmission(0x48);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(0x48, 2);
    temp_msb = Wire.read();
    temp_lsb = Wire.read();

    temp_lsb = temp_lsb >> 5;
    Temp = temp_msb + (temp_lsb * 0.125);

     Serial.println(Temp);
     Serial.println("C");
     
    
    //Serial.println(temp_msb,BIN);
    //Serial.println(temp_lsb,BIN);

  delay(2000);

}
