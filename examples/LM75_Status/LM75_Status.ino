#include <LM75.h>

LM75 Temp0(0x48);

float maxTemp, minTemp, Temp;

void setup() {
  // put your setup code here, to run once:


  Serial.begin(9600);
  Serial.println("Hello");

  //Temp0.shutDown();
  //Temp0.turnUp();
  //Temp0.setOperationMode(COMPARATOR);
  //Temp0.setPolarity(LOW);

  Temp0.setFaultQueue(1);

  //Temp0.setMinTemperature(20);
  //Temp0.setMaxTemperature(40);

  maxTemp = Temp0.getMaxTemperature();
  minTemp = Temp0.getMinTemperature();

  Serial.print("Min Temp : ");
  Serial.println(minTemp);
  Serial.print("Max Temp : ");
  Serial.println(maxTemp);

  Serial.print("Operation mode : ");
  if (Temp0.getOperationMode() == INTERRUPT)
    Serial.println("Comparator");
  else
    Serial.println("Interrupt");
    
  Serial.print("Polarity : ");
  if (Temp0.getPolarity() == LOW)
    Serial.println("Low");
  else
    Serial.println("High");

   Serial.print("Fault Queue : ");
   Serial.println(Temp0.getFaultQueue());
    
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:

  Temp = Temp0.getTemperature();

  Serial.print("Curr Temp : ");
  Serial.println(Temp);
  delay(1500);

}
