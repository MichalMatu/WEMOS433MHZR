/*
  Based on the SendDemo example from the RC Switch library
  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

void setup()
{
  Serial.begin(9600);

  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(5);

  // Optional set pulse length.
  mySwitch.setPulseLength(416);

  // Optional set protocol (default is 1, will work for most outlets)
  mySwitch.setProtocol(2);

  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(15);
}

void loop()
{
  // Binary code - button 3
  mySwitch.send("000101010101000101010101");
  delay(1000);
  mySwitch.send("000101010101000101010100");
  delay(1000);

  // Binary code - button 4
  mySwitch.send("000101010101010001010101");
  delay(1000);
  mySwitch.send("000101010101010001010100");
  delay(1000);
}