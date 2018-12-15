#include <Arduino.h>
#include <Keyboard.h>

int buttonPin = 9;
int ledPin = 17;

int charsPerLine = 20;
int charDelayMillis = 50;
int firstCharacter = 97; // letter a

int ledState = 0;
int character = firstCharacter;

void setup()
{
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  pinMode(ledPin, OUTPUT);
  Keyboard.begin();
}

void loop()
{
  if (digitalRead(buttonPin) == 0) {
    if (character == (firstCharacter + charsPerLine)) {
      Keyboard.println();
      character = firstCharacter;
    } else {
      Keyboard.write(character);
      character++;
    }
    delay(charDelayMillis);
    digitalWrite(ledPin, ledState);
    ledState = !ledState;
  }
}
