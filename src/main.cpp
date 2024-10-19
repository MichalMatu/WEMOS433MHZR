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

// Define signals to send
const long signal1 = 906118656;  // First signal
const long signal2 = 1040336384; // Second signal
bool sendingSignal1 = true;      // Flag to determine which signal to send

void setup()
{
  Serial.begin(115200);

  // Initialize transmitter and receiver
  transmitterSwitch.enableTransmit(transmitterPin);
  receiverSwitch.enableReceive(receiverPin);

  // Set the protocol to 2 for the transmitter
  transmitterSwitch.setProtocol(2);

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

  // Sending signals using millis()
  unsigned long currentMillis = millis(); // Get the current time

  if (currentMillis - previousMillis >= interval) // Check if the interval has passed
  {
    previousMillis = currentMillis; // Save the last time you sent the signal

    if (sendingSignal1)
    {
      transmitterSwitch.send(signal1, 32); // Send the first signal
      Serial.println("Signal sent: " + String(signal1));
    }
    else
    {
      transmitterSwitch.send(signal2, 32); // Send the second signal
      Serial.println("Signal sent: " + String(signal2));
    }

    // Toggle between signals
    sendingSignal1 = !sendingSignal1;
  }
}
