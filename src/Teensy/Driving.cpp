#include "Driving.h"

Driving::Driving() {

    data = nullptr;
    m_ramp = 0;
    m_leftWasOn = false;
    m_rightWasOn = false;
    m_runningWasOn = false;
    m_leftOffHits = 0;
    m_rightOffHits = 0;
    m_runningOffHits = 0;
    m_flashersTimer = new Timer;
    m_leftTimer = new Timer;
    m_rightTimer = new Timer;
}

bool Driving::step() {

    // TODO: for now, only use the first back strip
    std::vector<Strip*>* backStrips = System::GetInstance().GetStripsByType(Strip::Type::kBack);
    Strip* backStrip = (*backStrips)[0];

    bool brake = digitalRead(K_PIN_LIGHT_BRAKE);
    bool reverse = digitalRead(K_PIN_LIGHT_REVERSE);

    bool rawLeft = digitalRead(K_PIN_LIGHT_BLINKER_LEFT);
    bool rawRight = digitalRead(K_PIN_LIGHT_BLINKER_RIGHT);
    bool rawRunning = digitalRead(K_PIN_RUNNING_LIGHTS);
    // These values will be defaulted to correct
    bool left = rawLeft;
    bool right = rawRight;
    bool running = rawRunning;

    // If light claims to be off and it was on before
    if (!rawLeft && m_leftWasOn) {

        // If the number of hits has passed the tolerance
        if (m_leftOffHits >= K_MODE_DRIVING_BLINKER_HITS - 1) {

            // It is (probably) off
            left = false;
            // Reset hit count
            m_leftOffHits = 0;
        }
        else {

            // Flag a hit
            m_leftOffHits++;
            // Assume still correct
            left = true;
        }
    }

    // If light claims to be off and it was on before
    if (!rawRight && m_rightWasOn) {

        // If the number of hits has passed the tolerance
        if (m_rightOffHits >= K_MODE_DRIVING_BLINKER_HITS - 1) {

            // It is (probably) off
            right = false;
            // Reset hit count
            m_rightOffHits = 0;
        }
        else {

            // Flag a hit
            m_rightOffHits++;
            // Assume still correct
            right = true;
        }
    }

    // If light claims to be off and it was on before
    if (!rawRunning && m_runningWasOn) {

        // If the number of hits has passed the tolerance
        if (m_runningOffHits >= K_MODE_DRIVING_BLINKER_HITS - 1) {

            // It is (probably) off
            running = false;
            // Reset hit count
            m_runningOffHits = 0;
        }
        else {

            // Flag a hit
            m_runningOffHits++;
            // Assume still correct
            running = true;
        }
    }

    if (rawLeft) {

        // Reset hit count
        m_leftOffHits = 0;
    }
    if (rawRight) {

        // Reset hit count
        m_rightOffHits = 0;
    }
    if (rawRunning) {

        // Reset hit count
        m_runningOffHits = 0;
    }


    // digitalWrite(LED_BUILTIN, rawRight);
    // Serial.print(rawLeft); Serial.print(" "); Serial.println(left);
    // Serial.print(rawLeft); Serial.print(" "); Serial.print(rawRight);
    // Serial.print("    ");
    // Serial.print(left); Serial.print(" "); Serial.print(right);
    // reverse > blinkers > brakes

    /*if (right && left) {

        backStrip->SetAllHSV(
            K_COLOR_HSV_H_RED,
            K_COLOR_HSV_S_RED,
            K_COLOR_HSV_V_RED
        );
    }
    else {

        backStrip->Clear();
    }*/

    std::vector<Strip*>* runningStrips;
    runningStrips = System::GetInstance().GetStripsByType(Strip::Type::kLeft);
    for (int i = 0; i < (int)runningStrips->size(); i++) {

        if (running) {

            (*runningStrips)[i]->SetAllHSV(
                K_COLOR_HSV_H_AMBER,
                K_COLOR_HSV_S_AMBER,
                K_COLOR_HSV_V_AMBER
            );
        }
        else {

            (*runningStrips)[i]->SetAllHSV(
                K_COLOR_HSV_H_OFF,
                K_COLOR_HSV_S_OFF,
                K_COLOR_HSV_V_OFF
            );
        }
    }
    runningStrips = System::GetInstance().GetStripsByType(Strip::Type::kRight);
    for (int i = 0; i < (int)runningStrips->size(); i++) {

        if (running) {

            (*runningStrips)[i]->SetAllHSV(
                K_COLOR_HSV_H_AMBER,
                K_COLOR_HSV_S_AMBER,
                K_COLOR_HSV_V_AMBER
            );
        }
        else {

            (*runningStrips)[i]->SetAllHSV(
                K_COLOR_HSV_H_OFF,
                K_COLOR_HSV_S_OFF,
                K_COLOR_HSV_V_OFF
            );
        }
    }

    if (right && left) {

        ModeManager::GetMode(ModeManager::Mode_t::kWarning)->step();
        m_flashersTimer->Restart();
        digitalWrite(K_PIN_BACKRACK_LIGHT, HIGH);
    }
    // If the flashers could still be on
    else if (!m_flashersTimer->WhenElapsed((int)K_MS_PER_BLINK + K_MS_FLASHERS_TIMEOUT)) {

        ModeManager::GetMode(ModeManager::Mode_t::kWarning)->step();
        digitalWrite(K_PIN_BACKRACK_LIGHT, HIGH);
    }
    else {

        digitalWrite(K_PIN_BACKRACK_LIGHT, LOW);

        if (left) {

            m_leftTimer->Restart();

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
                m_ramp += m_ramp >= backStrip->GetNumLEDs() / 2 - 1 ? 0 : 2;
            }

            // Set the ramp indicies to on
            backStrip->leds[backStrip->GetNumLEDs() / 2 - m_ramp] = CHSV(
                K_COLOR_HSV_H_AMBER,
                K_COLOR_HSV_S_AMBER,
                K_COLOR_HSV_V_AMBER
            );
            backStrip->leds[backStrip->GetNumLEDs() / 2 - m_ramp + 1] = CHSV(
                K_COLOR_HSV_H_AMBER,
                K_COLOR_HSV_S_AMBER,
                K_COLOR_HSV_V_AMBER
            );
        }
        // If the left blinker is off, clear the left side of the strip
        else {

            for (int i = backStrip->GetNumLEDs() / 2 - 1; i >= 0; i--) {

                backStrip->leds[i] = CHSV(
                    K_COLOR_HSV_H_OFF,
                    K_COLOR_HSV_S_OFF,
                    K_COLOR_HSV_V_OFF
                );
            }
        }

        if (right) {

            m_rightTimer->Restart();

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
                m_ramp += m_ramp >= backStrip->GetNumLEDs() / 2 - 1 ? 0 : 2;
            }

            // Set the ramp indicies to on
            backStrip->leds[backStrip->GetNumLEDs() / 2 - 1 + m_ramp] = CHSV(
                K_COLOR_HSV_H_AMBER,
                K_COLOR_HSV_S_AMBER,
                K_COLOR_HSV_V_AMBER
            );
            backStrip->leds[backStrip->GetNumLEDs() / 2 - 1 + m_ramp + 1] = CHSV(
                K_COLOR_HSV_H_AMBER,
                K_COLOR_HSV_S_AMBER,
                K_COLOR_HSV_V_AMBER
            );
        }
        // If the right blinker is off, clear the right side of the strip
        else {

            for (int i = backStrip->GetNumLEDs() / 2; i < backStrip->GetNumLEDs(); i++) {

                backStrip->leds[i] = CHSV(
                    K_COLOR_HSV_H_OFF,
                    K_COLOR_HSV_S_OFF,
                    K_COLOR_HSV_V_OFF
                );
            }
        }

        m_leftWasOn = left;
        m_rightWasOn = right;
        m_runningWasOn = running;
    }

    if (brake) {

        if (!left && m_leftTimer->WhenElapsed((int)K_MS_PER_BLINK + K_MS_FLASHERS_TIMEOUT)) {

            for (int i = 0; i < backStrip->GetNumLEDs() / 2; i++) {

                backStrip->leds[i] = CHSV(
                    K_COLOR_HSV_H_RED,
                    K_COLOR_HSV_S_RED,
                    K_COLOR_HSV_V_RED
                );
            }
        }
        if (!right && m_rightTimer->WhenElapsed((int)K_MS_PER_BLINK + K_MS_FLASHERS_TIMEOUT)) {

            for (int i = backStrip->GetNumLEDs() / 2; i < backStrip->GetNumLEDs(); i++) {

                backStrip->leds[i] = CHSV(
                    K_COLOR_HSV_H_RED,
                    K_COLOR_HSV_S_RED,
                    K_COLOR_HSV_V_RED
                );
            }
        }
    }

    if (!(right && left) && m_flashersTimer->WhenElapsed((int)K_MS_PER_BLINK + K_MS_FLASHERS_TIMEOUT)) {

        if (reverse) {

            System::GetInstance().SetAllHSV(
                K_COLOR_HSV_H_WHITE,
                K_COLOR_HSV_S_WHITE,
                K_COLOR_HSV_V_WHITE
            );
        }
    }
    return false;
}