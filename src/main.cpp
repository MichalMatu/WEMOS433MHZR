#include <Arduino.h>
/*
  Simple example for receiving

  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup()
{
  Serial.begin(115200);
  mySwitch.enableReceive(5); 
}

void loop()
{
  if (mySwitch.available())
  {

    Serial.print("Received ");
    Serial.print(mySwitch.getReceivedValue());
    Serial.print(" / ");
    Serial.print(mySwitch.getReceivedBitlength());
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println(mySwitch.getReceivedProtocol());
    Serial.print("Raw data: ");
    for (int i = 0; i < mySwitch.getReceivedBitlength(); i++)
    {
      Serial.print(mySwitch.getReceivedRawdata()[i]);
    }
    Serial.println();

    mySwitch.resetAvailable();
  }
}