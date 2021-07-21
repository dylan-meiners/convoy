#include <Arduino.h>
#include <FastLED.h>
#include <ArduinoSTL.h>
#include <vector>

#include "Vehicle.h"
#include "Strip.h"
#include "ks.h"
#include "vfx/modes/TestMode.h"
#include "vfx/modes/RainbowWave.h"
#include "vfx/modes/GreenPulse.h"
#include "vfx/modes/Flow.h"

Strip* stripFront   = new Strip(K_PIN_STRIP_FRONT,  K_NUM_LEDS_STRIP_FRONT, Strip::Type::kFront);
// Strip* stripRight   = new Strip(K_PIN_STRIP_RIGHT,  K_NUM_LEDS_STRIP_RIGHT, Strip::Type::kRight);
// Strip* stripLeft    = new Strip(K_PIN_STRIP_LEFT,   K_NUM_LEDS_STRIP_LEFT,  Strip::Type::kLeft);
// Strip* stripBack    = new Strip(K_PIN_STRIP_BACK,   K_NUM_LEDS_STRIP_BACK,  Strip::Type::kBack);
std::vector<Strip*> strips;

Mode* modes[] = {
    new TestMode(),
    new RainbowWave(),
    new GreenPulse(),
    new Flow()
};

enum E_Mode {
    kTestMode,
    kRainbowWave,
    kGreenPulse,
    kFlow
};

E_Mode activeMode, oldMode;

void processSerial();
void switchMode(E_Mode, bool force = false);
void playQuickMode(E_Mode);
void ClearSerial();

void setup() {

    Serial.begin(9600);
    Serial.setTimeout(1000);
    ClearSerial();

    randomSeed(analogRead(0));
    
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    strips.push_back(stripFront);
    // strips.push_back(stripRight);
    // strips.push_back(stripLeft);
    // strips.push_back(stripBack);
    Vehicle::GetInstance().AddConfiguration(&strips);

    switchMode(kFlow, true);
    playQuickMode(kGreenPulse);

    FastLED.clear();
    FastLED.setBrightness(255);
    FastLED.show();
}

void loop() {

    processSerial();

    if(modes[activeMode]->step()) {

        // Do not use switchMode(E_Mode) because it will reset the mode. If
        // step returns true, then it is returning from a quick effect so,
        // strictly resume the previous mode.
        activeMode = oldMode;
    }

    Vehicle::GetInstance().MoveHSVToRGB();
    FastLED.show();
}

void processSerial() {

    static uint8_t* data = new uint8_t[256];
    static uint8_t* tmp = new uint8_t;

    int avail = Serial.available();
    if (avail > 0) {

        if (avail > 1) {

            // TODO: log("Data request check has more than one byte available (%d); reading first available and discarding the rest", avail, Logger::LogLevel::Info)    
        }
        if (Serial.read() == INCOMING_DATA_REQUEST) {
            
            Serial.write(ACK);
            int numRecvd = Serial.readBytes(tmp, 1);
            if (numRecvd == 1) {

                int mode = *tmp;
                numRecvd = Serial.readBytes(data, modes[mode]->dataLength);
                if (numRecvd != modes[mode]->dataLength) {

                    // TODO: log("Did not receive all data; %d attempted --> %d actual", toRead, numRecvd, Logger::LogLevel::Error)
                }
                else {

                    // TODO: This could fail miserably in so many ways and cause absolute death to the system, but it's ok
                    if (modes[mode]->dataLength > 0) {
                        
                        memcpy(modes[mode]->data, data, modes[mode]->dataLength);
                        modes[mode]->parse();
                    }
                }
                switchMode((E_Mode)mode);
                ClearSerial();
            }
        }
    }
}

void switchMode(E_Mode modeToSwtichTo, bool force = false) {

    if (force || activeMode != modeToSwtichTo) {

        activeMode = modeToSwtichTo;
        modes[activeMode]->reset();
    }
}

void playQuickMode(E_Mode modeToPlay) {

    oldMode = activeMode;
    switchMode(modeToPlay);
}

void ClearSerial() {

    while (Serial.available() > 0) { Serial.read(); }
}