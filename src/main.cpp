#include <Arduino.h>
#include <Keyboard.h>
#include <spi.h>
#include <TFT.h>
#include <Bounce2.h>

const char A = 'a';
const char Z = 'z';

const int START_BUTTON_PIN = 9;
const int LINES_BUTTON_PIN = 6;
const int CHARS_BUTTON_PIN = 7;
const int RATE_BUTTON_PIN = 8;

const int TFT_CS_PIN = 10;
const int TFT_DC_PIN = A0; // Labelled RS on TFT
const int TFT_RST_PIN = 14;

const int LINES_VALUES[4] = {-1, 1, 2, 4};
const int CHARS_VALUES[5] = {5, 13, 26, 52, 104};
const int RATE_VALUES[5] = {100, 200, 400, 1000, 6000};

const int LINES_ARRAY_LEN = sizeof(LINES_VALUES) / sizeof(LINES_VALUES[0]);
const int CHARS_ARRAY_LEN = sizeof(CHARS_VALUES) / sizeof(CHARS_VALUES[0]);
const int RATE_ARRAY_LEN = sizeof(RATE_VALUES) / sizeof(RATE_VALUES[0]);

const int LABEL_X_OFFSET = 10;
const int VALUE_X_OFFSET = 95;
const int LINES_Y_OFFSET = 35;
const int CHARS_Y_OFFSET = 60;
const int RATE_Y_OFFSET = 85;

char character = A;

int charCount = 0;
int lineCount = 0;
int linesIndex = 0;
int charsIndex = 2;
int rateIndex = 1;

TFT screen = TFT(TFT_CS_PIN, TFT_DC_PIN, TFT_RST_PIN);

Bounce startButton = Bounce();
Bounce linesButton = Bounce();
Bounce charsButton = Bounce();
Bounce rateButton = Bounce();

void displayNumber(int number, int x, int y) {
    char cstr[5];
    screen.text(itoa(number, cstr, 10), x, y);
}

void clearNumber(int number, int x, int y) {
    screen.stroke(ST7735_WHITE);
    displayNumber(number, x, y);
    screen.stroke(ST7735_BLACK);
}

void setLinesValue(int number) {
    displayNumber(number, VALUE_X_OFFSET, LINES_Y_OFFSET);
}

void setCharsValue(int number) {
    displayNumber(number, VALUE_X_OFFSET, CHARS_Y_OFFSET);
}

void setRateValue(int number) {
    displayNumber(number, VALUE_X_OFFSET, RATE_Y_OFFSET);
}

void clearLinesValue(int number) {
    clearNumber(number, VALUE_X_OFFSET, LINES_Y_OFFSET);
}

void clearCharsValue(int number) {
    clearNumber(number, VALUE_X_OFFSET, CHARS_Y_OFFSET);
}

void clearRateValue(int number) {
    clearNumber(number, VALUE_X_OFFSET, RATE_Y_OFFSET);
}

void initializeButton(Bounce *button, int pin) {
    pinMode(pin, INPUT);
    digitalWrite(pin, HIGH);
    button->attach(pin);
    button->interval(5);
}

void handleLinesButton() {
    linesButton.update();
    if (linesButton.fell()) {
        clearLinesValue(LINES_VALUES[linesIndex]);
        linesIndex++;
        if (linesIndex == LINES_ARRAY_LEN) {
            linesIndex = 0;
        }
        setLinesValue(LINES_VALUES[linesIndex]);
    }
}

void handleCharsButton() {
    charsButton.update();
    if (charsButton.fell()) {
        clearCharsValue(CHARS_VALUES[charsIndex]);
        charsIndex++;
        if (charsIndex == CHARS_ARRAY_LEN) {
            charsIndex = 0;
        }
        setCharsValue(CHARS_VALUES[charsIndex]);
    }
}

void handleRateButton() {
    rateButton.update();
    if (rateButton.fell()) {
        clearRateValue(RATE_VALUES[rateIndex]);
        rateIndex++;
        if (rateIndex == RATE_ARRAY_LEN) {
            rateIndex = 0;
        }
        setRateValue(RATE_VALUES[rateIndex]);
    }
}

void initializeScreen() {
    screen.begin();
    screen.background(ST7735_WHITE);
    screen.setTextSize(2);
    screen.stroke(ST7735_BLACK);
    screen.text("Key Typer", 25, 5);
    screen.text("Lines:", LABEL_X_OFFSET, LINES_Y_OFFSET);
    screen.text("Chars:", LABEL_X_OFFSET, CHARS_Y_OFFSET);
    screen.text("Rate:", LABEL_X_OFFSET, RATE_Y_OFFSET);

    setLinesValue(LINES_VALUES[linesIndex]);
    setCharsValue(CHARS_VALUES[charsIndex]);
    setRateValue(RATE_VALUES[rateIndex]);
}

void setup() {
    initializeButton(&startButton, START_BUTTON_PIN);
    initializeButton(&linesButton, LINES_BUTTON_PIN);
    initializeButton(&charsButton, CHARS_BUTTON_PIN);
    initializeButton(&rateButton, RATE_BUTTON_PIN);
    initializeScreen();
    Keyboard.begin();
}

void loop() {
    startButton.update();

    if (startButton.read() == LOW) {
        if (LINES_VALUES[linesIndex] == -1 || lineCount < LINES_VALUES[linesIndex]) {
            if (charCount == CHARS_VALUES[charsIndex]) {
                // Start a new line and start again at letter a
                Keyboard.println();
                character = A;
                charCount = 0;
                lineCount++;
            } else {
                // Write a single character
                Keyboard.write(character++);
                charCount++;
                if (character > Z) {
                    character = A;
                }
            }
        }

        delay(60000 / RATE_VALUES[rateIndex]);
    } else {
        lineCount = 0;
    }

    handleLinesButton();
    handleCharsButton();
    handleRateButton();
}
