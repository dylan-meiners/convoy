#ifndef TESTMODE_H
#define TESTMODE_H

#include <FastLED.h>
#include <ArduinoSTL.h>
#include <vector>
#include "../Mode.h"
#include "../../Vehicle.h"

class TestMode : public Mode {

    public:
        TestMode() {

            m_step = 0;
            m_forward = true;
            m_timer = 0;
        }

        void step() {

            long now = millis();
            if (now - m_timer >= 0) {
                
                m_timer = now;
                Vehicle::GetInstance().Clear();
                Location* l = Vehicle::GetInstance().GetFullLocation(m_step);
                Vehicle::GetInstance().GetStrips()[l->strip]->leds[l->led] = CHSV(0, 255, 255);
                if (m_forward) {

                    m_step++;
                    if (m_step > Vehicle::GetInstance().GetTotal() - 1) {

                        m_forward = false;
                        m_step -= 2;
                    }
                }
                else {

                    m_step--;
                    if (m_step < 0) {

                        m_forward = true;
                        m_step = 1;
                    }
                }
            }
        }

        void reset() {

            m_step = 0;
            m_forward = true;
            m_timer = millis();
        }

    private:
        int m_step;
        bool m_forward;
        long m_timer;
};

#endif