#include <Arduino.h>
#include <FastLED.h>
#include <ArduinoSTL.h>
#include <vector>

#include "System.h"
#include "Strip.h"
#include "ks.h"
#include "vfx/ModeManager.h"
#include "vfx/modes/TestMode.h"
#include "vfx/modes/RainbowWave.h"
#include "vfx/modes/GreenPulse.h"
#include "vfx/modes/Flow.h"
#include "vfx/modes/Driving.h"
#include "vfx/modes/Warning.h"

// Strip* stripFront   = new Strip(K_PIN_STRIP_FRONT,  K_NUM_LEDS_STRIP_FRONT, Strip::Type::kFront, false);
Strip* stripRight   = new Strip(K_PIN_STRIP_RIGHT,  K_NUM_LEDS_STRIP_RIGHT, Strip::Type::kRight,    false);
Strip* stripLeft    = new Strip(K_PIN_STRIP_LEFT,   K_NUM_LEDS_STRIP_LEFT,  Strip::Type::kLeft,     true);
Strip* stripBack    = new Strip(K_PIN_STRIP_BACK,   K_NUM_LEDS_STRIP_BACK,  Strip::Type::kBack,     true);
std::vector<Strip*> strips;

void processSerial();
void ClearSerial();

void setup() {

    Serial.begin(9600);
    Serial.setTimeout(1000);
    ClearSerial();

    randomSeed(analogRead(0));
    
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(K_PIN_STRIP_FRONT, OUTPUT);
    pinMode(K_PIN_STRIP_RIGHT, OUTPUT);
    pinMode(K_PIN_STRIP_BACK, OUTPUT);
    pinMode(K_PIN_STRIP_LEFT, OUTPUT);
    pinMode(K_PIN_BACKRACK_LIGHT, OUTPUT);

    pinMode(K_PIN_LIGHT_BRAKE, INPUT);
    pinMode(K_PIN_RUNNING_LIGHTS, INPUT);
    pinMode(K_PIN_LIGHT_BLINKER_LEFT, INPUT);
    pinMode(K_PIN_LIGHT_BLINKER_RIGHT, INPUT);
    pinMode(K_PIN_LIGHT_REVERSE, INPUT);

    // strips.push_back(stripFront);
    strips.push_back(stripRight);
    strips.push_back(stripLeft);
    strips.push_back(stripBack);
    System::GetInstance().AddConfiguration(&strips);

    std::vector<Mode*> modes;
    modes.push_back(new TestMode());
    modes.push_back(new RainbowWave());
    modes.push_back(new GreenPulse());
    modes.push_back(new Flow());
    modes.push_back(new Driving());
    modes.push_back(new Warning());
    ModeManager::GetInstance().AddModes(modes);
    ModeManager::GetInstance().SwitchMode(ModeManager::Mode_t::kDriving, true);
    ModeManager::GetInstance().PlayQuickMode(ModeManager::Mode_t::kGreenPulse);

    FastLED.clear();
    FastLED.setBrightness(255);
    FastLED.show();
}

void loop() {

    // processSerial();

    ModeManager::GetInstance().Step();
    // System::GetInstance().ApplyReverse();
    System::GetInstance().MoveHSVToRGB();
    FastLED.show();
    // delay(2);

    // Serial.println(digitalRead(K_PIN_LIGHT_BLINKER_LEFT));
    // delay(10);
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
                int dataLength = ModeManager::GetInstance().GetMode((ModeManager::Mode_t)mode)->dataLength;
                numRecvd = Serial.readBytes(data, dataLength);
                if (numRecvd != dataLength) {

                    // TODO: log("Did not receive all data; %d attempted --> %d actual", toRead, numRecvd, Logger::LogLevel::Error)
                }
                else {

                    // TODO: This could fail miserably in so many ways and cause absolute death to the system, but it's ok
                    if (dataLength > 0) {
                        
                        memcpy(ModeManager::GetInstance().GetMode((ModeManager::Mode_t)mode)->data, data, dataLength);
                        ModeManager::GetInstance().GetMode((ModeManager::Mode_t)mode)->parse();
                    }
                }
                ModeManager::GetInstance().SwitchMode((ModeManager::Mode_t)mode);
                ClearSerial();
            }
        }
    }
}

void ClearSerial() {

    while (Serial.available() > 0) { Serial.read(); }
}