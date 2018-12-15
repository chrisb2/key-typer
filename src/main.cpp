#include <Arduino.h>
#include <Keyboard.h>

int buttonPin = 9;
int ledPin = 17;

const int CHARS_PER_LINE = 50;
const int CHAR_DELAY_MS = 50;
const int CHAR_A = 97;
const int CHAR_Z = 122;

int ledState = 0;
int character = CHAR_A;
int charCount = 0;

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
        if (charCount == CHARS_PER_LINE) {
            // Start a new line and start again at letter a
            Keyboard.println();
            character = CHAR_A;
            charCount = 0;
        } else {
            // Write a single character
            Keyboard.write(character);
            character++;
            charCount++;
            if (character > CHAR_Z) {
                // Start again at letter a
                character = CHAR_A;
            }
        }

        delay(CHAR_DELAY_MS);
        digitalWrite(ledPin, ledState);
        ledState = !ledState;
    }
}
