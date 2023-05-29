#include <Arduino.h>

const int knockPin = 2;
const int ledPin = 13;

unsigned long previousMillis = 0;
const unsigned long interval = 1000;  // Interval in milliseconds

const int pattern_length = 5;  // Length of each knock pattern
const bool pattern1[] = {true, true, true, true, true};
const bool pattern2[] = {1, 1, 0, 1, 1};
const bool pattern3[] = {0, 1, 0, 1, 0};

const bool* patterns[] = {pattern1, pattern2, pattern3};
const int numPatterns = sizeof(patterns) / sizeof(patterns[0]);

bool checkEvent()
{
  return digitalRead(knockPin) == HIGH;
}

bool checkEventForSecond()
{
  unsigned long startMillis = millis();
  bool eventOccurred = false;

  while (millis() - startMillis < interval)
  {
    if (checkEvent())
    {
      eventOccurred = true;
      delay(1000 - (millis() - startMillis));  // Sleeps for the remainder of the time
      break;
    }
  }

  return eventOccurred;
}

void setup()
{
  pinMode(knockPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  Serial.println("\nProgram running...");
  Serial.println("Existing Patterns:");

  for (int i = 0; i < numPatterns; i++) {
    Serial.print("Pattern ");
    Serial.print(i + 1);
    Serial.print(": ");
    
    const bool* currentPattern = patterns[i];
    for (int j = 0; j < pattern_length; j++) {
      Serial.print(currentPattern[j]);
      if (j != pattern_length - 1) {
        Serial.print(", ");
      }
    }
    
    Serial.println();
  }
}

bool matchPattern(const bool* eventList, const bool* pattern)
{
  for (int i = 0; i < pattern_length; i++) {
    if (eventList[i] != pattern[i]) {
      return false;
    }
  }
  return true;
}

void loop()
{
  bool eventHappened = checkEventForSecond();
  Serial.print("\nNo knock detected. ");
  Serial.println(eventHappened);

  if (eventHappened)
  {
    Serial.println("\n\nRecording started!");
    bool eventList[pattern_length];
    int eventCount = 0;

    while (eventCount < pattern_length)
    {
      Serial.print("\nChecking...");
      bool isCheckEvent = checkEventForSecond();
      Serial.print("Pattern detected: ");
      Serial.println(isCheckEvent);

      eventList[eventCount] = isCheckEvent;
      eventCount++;
    }

    Serial.println("\nKnock Pattern Detected: ");
    for (int i = 0; i < pattern_length; i++) {
      Serial.print(eventList[i]);
      if (i != pattern_length - 1) {
        Serial.print(", ");
      }
    }

    bool patternMatches = false;
    for (int i = 0; i < numPatterns; i++)
    {
      if (matchPattern(eventList, patterns[i]))
      {
        patternMatches = true;
        break;
      }
    }

    if (patternMatches)
    {
      Serial.println("\nPattern matches!");
      digitalWrite(ledPin, HIGH);
      delay(2000);
      digitalWrite(ledPin, LOW);
    }
    else
    {
      Serial.println("\nPattern doesn't match!");
      digitalWrite(ledPin, LOW);
    }
  }
}
