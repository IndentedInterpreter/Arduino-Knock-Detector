#include <Arduino.h>

unsigned long previousMillis = 0;
const unsigned long interval = 1000;  // Interval in milliseconds
bool event_pattern[] = {true, true, false, false, true};
const int pattern_length = sizeof(event_pattern) / sizeof(event_pattern[0]);

bool checkEvent()
{
  // Replace this with your own logic to check if the event occurred
  // For demonstration purposes, let's assume the event occurs based on a condition
  // Implement your condition using digitalRead(), analogRead(), or any other relevant Arduino functions
  // Return true if the event occurred, false otherwise
  return digitalRead(SOME_PIN) == HIGH;  // Replace SOME_PIN with the pin you want to monitor
}

bool checkEventForSecond()
{
  unsigned long currentMillis = millis();
  bool eventOccurred = false;
  int x = 0;

  while (millis() - currentMillis < interval)
  {
    x++;
    if (checkEvent())
    {
      Serial.print("Iterations: ");
      Serial.print(x);
      Serial.print(" Time spent: ");
      Serial.println(millis() - currentMillis);
      eventOccurred = true;
      delay(interval - (millis() - currentMillis));  // Sleeps for the remainder of the time
      break;
    }
  }

  return eventOccurred;
}

void setup()
{
  Serial.begin(9600);
  pinMode(SOME_PIN, INPUT);  // Replace SOME_PIN with the pin you want to monitor
}

void loop()
{
  bool eventHappened = checkEventForSecond();
  Serial.print("Event happened: ");
  Serial.println(eventHappened);

  if (eventHappened)
  {
    bool eventList[pattern_length];
    int eventCount = 0;

    while (eventCount < pattern_length)
    {
      bool isCheckEvent = checkEventForSecond();
      Serial.print("Check Event happened: ");
      Serial.println(isCheckEvent);

      if (isCheckEvent)
      {
        eventList[eventCount] = isCheckEvent;
        eventCount++;
      }
    }

    Serial.println("Event list:");
    for (int i = 0; i < pattern_length; i++)
    {
      Serial.println(eventList[i]);
    }

    bool patternMatches = true;
    for (int i = 0; i < pattern_length; i++)
    {
      if (eventList[i] != event_pattern[i])
      {
        patternMatches = false;
        break;
      }
    }

    if (patternMatches)
    {
      Serial.println("Pattern matches!");
    }
    else
    {
      Serial.println("Pattern doesn't match!");
    }
    while (true)
    {
      // You can add any additional code or functionality here
    }
  }
}
