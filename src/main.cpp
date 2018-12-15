#include <Arduino.h>
#include <Keyboard.h>

// time in milliseconds between each character being written
const int DELAY_MS = 10;
const int LINE_LENGTH = 104;
const char A = 'a';
const char Z = 'z';

const int BUTTON_PIN = 9;

char character = A;
int charCount = 0;

void setup() {
    pinMode(BUTTON_PIN, INPUT);
    digitalWrite(BUTTON_PIN, HIGH);
    Keyboard.begin();
}

void loop() {
    if (digitalRead(BUTTON_PIN) == 0) {
        if (charCount == LINE_LENGTH) {
            // Start a new line and start again at letter a
            Keyboard.println();
            character = A;
            charCount = 0;
        } else {
            // Write a single character
            Keyboard.write(character++);
            charCount++;
            if (character > Z) {
                character = A;
            }
        }

        delay(DELAY_MS);
    }
}
