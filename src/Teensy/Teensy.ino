#include "FastLED.h"

#include <vector>

#include "System.h"
#include "Strip.h"
#include "ks.h"
#include "ModeManager.h"
#include "TestMode.h"
#include "RainbowWave.h"
#include "ColorPulse.h"
#include "Flow.h"
#include "Driving.h"
#include "Warning.h"

// Strip* stripFront   = new Strip(K_PIN_STRIP_FRONT,  K_NUM_LEDS_STRIP_FRONT, Strip::Type::kFront, false);
Strip* stripRight = new Strip(K_PIN_STRIP_RIGHT, K_NUM_LEDS_STRIP_RIGHT, Strip::Type::kRight, false);
Strip* stripLeft = new Strip(K_PIN_STRIP_LEFT, K_NUM_LEDS_STRIP_LEFT, Strip::Type::kLeft, true);
Strip* stripBack = new Strip(K_PIN_STRIP_BACK, K_NUM_LEDS_STRIP_BACK, Strip::Type::kBack, true);
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
    modes.push_back(new ColorPulse());
    modes.push_back(new Flow());
    modes.push_back(new Driving());
    modes.push_back(new Warning());
    ModeManager::AddModes(modes);
    ((ColorPulse*)ModeManager::GetMode(ModeManager::Mode_t::kColorPulse))->SetColor(K_COLOR_HSV_V_GREEN);
    ModeManager::PlayQuickMode(ModeManager::Mode_t::kColorPulse);

    FastLED.clear();
    FastLED.setBrightness(255);
    FastLED.show();
}

void loop() {
    ModeManager::Step();

    // Only check to switch modes if we're not playing a quick modee
    if (!ModeManager::PlayingQuickMode()) {
        processSerial();
    }

    // System::GetInstance().ApplyReverse();
    System::GetInstance().MoveHSVToRGB();
    FastLED.show();
}

void processSerial() {
    static char* data = new char[256];
    static char* tmp = new char;

    int avail = Serial.available();
    if (avail > 0) {
        if (avail > 1) {
            // TODO: log("Data request check has more than one byte available (%d); reading first available and discarding the rest", avail, Logger::LogLevel::Info)    
        }
        if (digitalRead(K_INCOMING_DATA_PIN)) {
            interrupts();
            Serial.write(GO);
            int numRecvd = Serial.readBytes(tmp, 1);
            if (numRecvd == 1) {
                int cmd = *tmp;
                switch (cmd) {
                    case K_CMD_SWITCH_MODE:
                    {
                        numRecvd = Serial.readBytes(tmp, 1);
                        if (numRecvd == 1) {
                            int mode = *tmp;
                            if (mode <= ModeManager::NumModes()) {
                                int dataLength = ModeManager::GetMode((ModeManager::Mode_t)mode)->dataLength;
                                if (dataLength <= 256) {
                                    numRecvd = Serial.readBytes(data, dataLength);
                                    if (numRecvd != dataLength) {
                                        // TODO: log("Did not receive all data; %d attempted --> %d actual", toRead, numRecvd, Logger::LogLevel::Error)
                                        ((ColorPulse*)ModeManager::GetMode(ModeManager::Mode_t::kColorPulse))->SetColor(K_COLOR_HSV_V_RED);
                                        ModeManager::PlayQuickMode(ModeManager::Mode_t::kColorPulse);
                                    }
                                    else {
                                        if (dataLength > 0) {
                                            memcpy(ModeManager::GetMode((ModeManager::Mode_t)mode)->data, data, dataLength);
                                            ModeManager::GetMode((ModeManager::Mode_t)mode)->parse();
                                            ModeManager::SwitchMode((ModeManager::Mode_t)mode);
                                        }
                                    }
                                    ClearSerial();
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }

    noInterrupts();
}

void ClearSerial() {

    while (Serial.available() > 0) { Serial.read(); }
}