#include <Arduino.h>
#include <FastLED.h>
#include <ArduinoSTL.h>
#include <vector>

#include "Vehicle.h"
#include "Strip.h"
#include "ks.h"
#include "Timer.h"
#include "vfx/ModeManager.h"
#include "vfx/modes/TestMode.h"
#include "vfx/modes/RainbowWave.h"
#include "vfx/modes/GreenPulse.h"
#include "vfx/modes/Flow.h"
#include "vfx/modes/Driving.h"
#include "vfx/modes/Warning.h"
#include "vfx/modes/RainbowWaveUniform.h"
#include "vfx/modes/FlowUniform.h"

// Strip* stripFront   = new Strip(K_PIN_STRIP_FRONT,  K_NUM_LEDS_STRIP_FRONT, Strip::Type::kFront, false);
// Strip* stripRight   = new Strip(K_PIN_STRIP_RIGHT,  K_NUM_LEDS_STRIP_RIGHT, Strip::Type::kRight, false);
// Strip* stripLeft    = new Strip(K_PIN_STRIP_LEFT,   K_NUM_LEDS_STRIP_LEFT,  Strip::Type::kLeft, true);
// Strip* stripBack    = new Strip(K_PIN_STRIP_BACK,   K_NUM_LEDS_STRIP_BACK,  Strip::Type::kBack, true);

Strip* one          = new Strip(K_PIN_STRIP_ONE,    K_NUM_LEDS_STRIP_ONE,   Strip::Type::kFront, false);
Strip* two          = new Strip(K_PIN_STRIP_TWO,    K_NUM_LEDS_STRIP_TWO,   Strip::Type::kFront, false);
Strip* three        = new Strip(K_PIN_STRIP_THREE, K_NUM_LEDS_STRIP_THREE,  Strip::Type::kFront, false);
std::vector<Strip*> strips;

// Timer* switcher = new Timer;
// std::vector<ModeManager::Mode_t> loopModes;
// std::vector<ModeManager::Mode_t>::iterator currentLoopMode;
Timer* testTimer = new Timer;

void processSerial();
void ClearSerial();

void setup() {

    Serial.begin(9600);
    Serial.setTimeout(1000);
    ClearSerial();

    randomSeed(analogRead(0));
    
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    
    pinMode(K_PIN_STRIP_ONE,    OUTPUT);
    pinMode(K_PIN_STRIP_TWO,    OUTPUT);
    pinMode(K_PIN_STRIP_THREE,  OUTPUT);

    // pinMode(K_PIN_LIGHT_BRAKE, INPUT);
    // pinMode(K_PIN_RUNNING_LIGHTS, INPUT);
    // pinMode(K_PIN_LIGHT_BLINKER_LEFT, INPUT);
    // pinMode(K_PIN_LIGHT_BLINKER_RIGHT, INPUT);
    // pinMode(K_PIN_LIGHT_REVERSE, INPUT);

    // strips.push_back(stripFront);
    strips.push_back(one);
    strips.push_back(two);
    strips.push_back(three);
    Vehicle::GetInstance().AddConfiguration(&strips);

    // std::vector<Mode*> modes;
    // modes.push_back(new TestMode());
    // modes.push_back(new RainbowWave()); 
    // modes.push_back(new GreenPulse());
    // modes.push_back(new Flow());
    // modes.push_back(new Driving());
    // modes.push_back(new Warning());
    // modes.push_back(new RainbowWaveUniform());
    // modes.push_back(new FlowUniform());
    // ModeManager::GetInstance().AddModes(modes);
    // ModeManager::GetInstance().SwitchMode(ModeManager::Mode_t::kTestMode, true);
    // ModeManager::GetInstance().PlayQuickMode(ModeManager::Mode_t::kGreenPulse);

    FastLED.clear(true);
    // FastLED.setBrightness(255);
    FastLED.show();

    // loopModes.push_back(ModeManager::Mode_t::kRainbowWaveUniform);
    // loopModes.push_back(ModeManager::Mode_t::kFlowUniform);
    // currentLoopMode = loopModes.begin();
    // switcher->SetInterval(5 * 60 * 1000);
    // switcher->Restart();

    testTimer->SetInterval(250);
    testTimer->Restart();
}

void loop() {

    // processSerial();

    // if (switcher->RunInterval()) {

        // if (++currentLoopMode == loopModes.end()) {

            // currentLoopMode = loopModes.begin();
        // }
        // ModeManager::GetInstance().SwitchMode(*currentLoopMode);
    // }
    // digitalWrite(LED_BUILTIN, Vehicle::GetInstance().GetTotal() != 900);

    // ModeManager::GetInstance().Step();
    // Vehicle::GetInstance().ApplyReverse();
    // Vehicle::GetInstance().MoveHSVToRGB();
    FastLED.show();
    // delay(2);

    if (testTimer->RunInterval()) {
        
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
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

/*CRGB ledd[300];
CRGB lede[300];
CRGB ledf[300];

void setup() {

    FastLED.addLeds<WS2812B, 2, GRB>(ledd, 300);
    FastLED.addLeds<WS2812B, 3, GRB>(lede, 300);
    FastLED.addLeds<WS2812B, 4, GRB>(ledf, 300);
    FastLED.clear(true);
}

void loop() {

    for (int i = 0; i < 300; i++) {

        ledd[i] = CHSV(200, 255, 255);
        lede[i] = CHSV(200, 255, 255);
        ledf[i] = CHSV(200, 255, 255);
    }
    FastLED.show();
}
*/