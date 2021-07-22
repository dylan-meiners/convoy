#ifndef DRIVING_H
#define DRIVING_H

#include "../Mode.h"
#include "../../Vehicle.h"
#include "../../Timer.h"
#include "../../ks.h"

class Driving : public Mode {

    public:
        Driving() {

            data = nullptr;
            m_ramp = 0;
            m_leftWasOn = false;
            m_rightWasOn = false;
        }

        bool step() {

            static std::vector<Strip*> backStrips;
            // TODO: for now, only use the first back strip
            static Strip* backStrip = backStrips[0];
            Vehicle::GetInstance().Filter(&backStrips, Strip::Type::kBack);
            
            bool brake =    digitalRead(K_PIN_LIGHT_BRAKE);
            bool reverse =  digitalRead(K_PIN_LIGHT_REVERSE);
            bool left =     digitalRead(K_PIN_LIGHT_BLINKER_LEFT);
            bool right =    digitalRead(K_PIN_LIGHT_BLINKER_RIGHT);

            // reverse > blinkers > brakes

            if (brake) {

                for (int i = 0; i < backStrips.size(); i++) {

                    backStrips[i]->SetAllHSV(
                        K_COLOR_HSV_H_RED,
                        K_COLOR_HSV_S_RED,
                        K_COLOR_HSV_V_RED
                    );
                }
            }

            if (right && left) {

                // TODO: Flashers are on; play DC-17
            }
            else {
                
                if (left) {

                    // If left blinker turned on but was off
                    if (!m_leftWasOn) {

                        // Clear ramp, leaving only the first one untouched
                        for (int i = backStrip->GetNumLEDs() / 2 - 1; i > 0; i--) {

                            backStrip->leds[i] = CHSV(
                                K_COLOR_HSV_H_OFF,
                                K_COLOR_HSV_S_OFF,
                                K_COLOR_HSV_V_OFF
                            );
                        }
                        // Reset the ramp to only one led on
                        m_ramp = 1;
                    }
                    // If the left blinker is on, and was on last check (has not reset)
                    else {

                        // Increase ramp count or stop if full
                        m_ramp += m_ramp >= backStrip->GetNumLEDs() / 2 ? 0 : 1;
                    }

                    // Set the ramp index to on
                    backStrip->leds[backStrip->GetNumLEDs() / 2 - m_ramp] = CHSV(
                        K_COLOR_HSV_H_WHITE,
                        K_COLOR_HSV_S_WHITE,
                        K_COLOR_HSV_V_WHITE
                    );
                }
                // If the left blinker is off, clear the left side of the strip
                else {

                    if (!brake) {
                    
                        for (int i = backStrip->GetNumLEDs() / 2 - 1; i >= 0; i--) {

                            backStrip->leds[i] = CHSV(
                                K_COLOR_HSV_H_OFF,
                                K_COLOR_HSV_S_OFF,
                                K_COLOR_HSV_V_OFF
                            );
                        }
                    }
                }

                if (right) {

                    // If right blinker turned on but was offf
                    if (!m_rightWasOn) {

                        // Clear ramp, leaving only the first one untouched
                        for (int i = backStrip->GetNumLEDs() / 2 + 1; i < backStrip->GetNumLEDs(); i++) {

                            backStrip->leds[i] = CHSV(
                                K_COLOR_HSV_H_OFF,
                                K_COLOR_HSV_S_OFF,
                                K_COLOR_HSV_V_OFF
                            );
                        }
                        // Reset the ramp to only one led on
                        m_ramp = 1;
                    }
                    // If the left blinker is on, and was on last check (has not reset)
                    else {

                        // Increase ramp count or stop if full
                        m_ramp += m_ramp == backStrip->GetNumLEDs() / 2 ? 0 : 1;
                    }

                    // Set the ramp index to on
                    backStrip->leds[backStrip->GetNumLEDs() / 2 - 1 + m_ramp] = CHSV(
                        K_COLOR_HSV_H_WHITE,
                        K_COLOR_HSV_S_WHITE,
                        K_COLOR_HSV_V_WHITE
                    );
                }
                // If the right blinker is off, clear the right side of the strip
                else {

                    if (!brake) {
                    
                        for (int i = backStrip->GetNumLEDs() / 2; i < backStrip->GetNumLEDs(); i++) {

                            backStrip->leds[i] = CHSV(
                                K_COLOR_HSV_H_OFF,
                                K_COLOR_HSV_S_OFF,
                                K_COLOR_HSV_V_OFF
                            );
                        }
                    }
                }

                m_leftWasOn = left;
                m_rightWasOn = right;
            }

            if (reverse) {

                for (int i = 0; i < backStrips.size(); i++) {

                    backStrips[i]->SetAllHSV(
                        K_COLOR_HSV_H_WHITE,
                        K_COLOR_HSV_S_WHITE,
                        K_COLOR_HSV_V_WHITE
                    );
                }
            }
            return false;
        }

        void reset() {}

        void parse() {}

    private:
        bool m_leftWasOn;
        bool m_rightWasOn;
        int m_ramp;
};

#endif