#include <Arduino.h>
#include <Keyboard.h>

const int BUTTON_PIN = 9;
const int LED_PIN = 17;

const int CHAR_DELAY_MS = 10;
const int CHARS_PER_LINE = 104;
const int CHAR_A = 97;
const int CHAR_Z = 122;

int ledState = 0;
int character = CHAR_A;
int charCount = 0;

void setup() {
    pinMode(BUTTON_PIN, INPUT);
    digitalWrite(BUTTON_PIN, HIGH);
    pinMode(LED_PIN, OUTPUT);
    Keyboard.begin();
}

void loop() {
    if (digitalRead(BUTTON_PIN) == 0) {
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
        digitalWrite(LED_PIN, ledState);
        ledState = !ledState;
    }
}
