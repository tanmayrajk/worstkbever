#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Bounce2.h>
#include <vector>
using namespace std;

#define SPACE_BTN 25
#define SUBMIT_BTN 27
#define POTENTIOMETER 26

#define RST_PIN 4
#define CE_PIN 5
#define DC_PIN 16
#define DIN_PIN 23
#define CLK_PIN 18

Bounce spaceDebouncer = Bounce();
Bounce submitDebouncer = Bounce();

Adafruit_PCD8544 display(CLK_PIN, DIN_PIN, DC_PIN, CE_PIN, RST_PIN);

char lettersArr[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ',', '.', '?', '!'};
float length = sizeof(lettersArr) / sizeof(lettersArr[0]);
char letter = lettersArr[0];

vector<float> rangeVec;

void setup() {
  pinMode(SPACE_BTN, INPUT_PULLUP);
  pinMode(SUBMIT_BTN, INPUT_PULLUP);
  pinMode(POTENTIOMETER, INPUT);
  Serial.begin(115200);

  spaceDebouncer.attach(SPACE_BTN);
  submitDebouncer.attach(SUBMIT_BTN);
  spaceDebouncer.interval(50);
  submitDebouncer.interval(50);

  display.begin();
  display.setContrast(50);
  display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(BLACK);
  display.setCursor(8, 20);
  display.println("Setting Up..");
  display.display();
  
  float offset = 4095/length;
  for (int i = 0; i < length; i++)
  {
    rangeVec.push_back(offset * (i + 1));
  }

  display.clearDisplay();
  display.setCursor(35, 15);
  display.println(letter);
  display.display();
}

void loop() {
  spaceDebouncer.update();
  submitDebouncer.update();

  if (spaceDebouncer.fell()) {
    Serial.println(" ");
  }
  if (submitDebouncer.fell()) {
    Serial.println(letter);
  }

  static float smoothedValue = 0;
  smoothedValue = (0.9 * smoothedValue) + (0.1 * analogRead(POTENTIOMETER));
  float adcValue = smoothedValue;

  for (int i = 0; i < length; i++) {
    if (rangeVec[i] > adcValue) {
      if (letter != lettersArr[i]) {
        letter = lettersArr[i];
        display.clearDisplay();
        display.setCursor(35, 15);
        display.println(letter);
        display.display();
      }
      break;
    }
  }
}