#include <Arduino.h>
#include <RCSwitch.h>

RCSwitch transmitterSwitch = RCSwitch(); // Instance for transmitting
RCSwitch receiverSwitch = RCSwitch();    // Instance for receiving

// Pin definitions
const int transmitterPin = 14; // Pin for the transmitter
const int receiverPin = 5;     // Pin for the receiver

// Timing variables
unsigned long previousMillis = 0; // Store the last time the signal was sent
const long interval = 5000;       // Interval to send signal (in milliseconds)

void setup()
{
  Serial.begin(115200);

  // Initialize transmitter and receiver
  transmitterSwitch.enableTransmit(transmitterPin);
  receiverSwitch.enableReceive(receiverPin);

  Serial.println("Transmitter and receiver initialized.");
}

void loop()
{
  // Check for received signal
  if (receiverSwitch.available())
  {
    Serial.print("Received ");
    Serial.print(receiverSwitch.getReceivedValue());
    Serial.print(" / ");
    Serial.print(receiverSwitch.getReceivedBitlength());
    Serial.print(" bit ");
    Serial.print("Protocol: ");
    Serial.println(receiverSwitch.getReceivedProtocol());
    Serial.print("Raw data: ");

    for (int i = 0; i < receiverSwitch.getReceivedBitlength(); i++)
    {
      Serial.print(receiverSwitch.getReceivedRawdata()[i]);
    }
    Serial.println();

    receiverSwitch.resetAvailable(); // Reset the availability
  }

  // Sending a signal every 5 seconds using millis()
  unsigned long currentMillis = millis(); // Get the current time

  if (currentMillis - previousMillis >= interval) // Check if the interval has passed
  {
    previousMillis = currentMillis;    // Save the last time you sent the signal
    transmitterSwitch.send(12345, 24); // Send a value (e.g., 12345) with a bit length (e.g., 24 bits)
    Serial.println("Signal sent!");
  }
}
