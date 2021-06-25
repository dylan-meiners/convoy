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
            forward = true;
        }

        void step() {

            digitalWrite(LED_BUILTIN, HIGH);
            Vehicle::GetInstance().Clear();
            Location* l = Vehicle::GetInstance().GetFullLocation(m_step);
            Vehicle::GetInstance().GetStrips()[l->strip]->leds[l->led] = CHSV(0, 255, 255);
            if (forward) {

                m_step++;
                if (m_step > Vehicle::GetInstance().GetTotal() - 1) {

                    forward = false;
                    m_step -= 2;
                }
            }
            else {

                m_step--;
                if (m_step < 0) {

                    forward = true;
                    m_step = 1;
                }
            }
        }

        void reset() {

            m_step = 0;
            forward = true;
        }

    private:
        int m_step;
        bool forward;
};

#endif