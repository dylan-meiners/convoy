#include <Arduino.h>
#include <FastLED.h>
#include <ArduinoSTL.h>
#include <vector>

#include "Vehicle.h"
#include "Strip.h"
#include "ks.h"
#include "vfx/modes/TestMode.h"

Strip* stripFront   = new Strip(K_PIN_STRIP_FRONT,  K_NUM_LEDS_STRIP_FRONT, Strip::Type::kFront);
//Strip* stripRight   = new Strip(K_PIN_STRIP_RIGHT,  K_NUM_LEDS_STRIP_RIGHT, Strip::Type::kRight);
//Strip* stripLeft    = new Strip(K_PIN_STRIP_LEFT,   K_NUM_LEDS_STRIP_LEFT,  Strip::Type::kLeft);
//Strip* stripBack    = new Strip(K_PIN_STRIP_BACK,   K_NUM_LEDS_STRIP_BACK,  Strip::Type::kBack);
std::vector<Strip*> strips;

Mode* modes[] = {
    new TestMode()
};

enum E_Mode {
    kTestMode
};

E_Mode activeMode;

void switchMode(E_Mode);
void ClearSerial();

CRGB leds[45];

void setup() {
    
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    strips.push_back(stripFront);
    // strips.push_back(stripRight);
    // strips.push_back(stripLeft);
    // strips.push_back(stripBack);
    Vehicle::GetInstance().AddConfiguration(&strips);

    Serial.begin(115200);

    activeMode = kTestMode;
    modes[activeMode]->reset();

    FastLED.clear();
    FastLED.setBrightness(255);
}

void loop() {

    modes[activeMode]->step();
    FastLED.show();
    delay(1);
}

void switchMode(E_Mode modeToSwtichTo) {

    if (activeMode != modeToSwtichTo) {

        activeMode = modeToSwtichTo;
        modes[activeMode]->reset();
    }
}

void ClearSerial() {

    while (Serial.available() > 0) { Serial.read(); }
}