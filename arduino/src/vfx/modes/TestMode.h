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
        }

        void step() {

            Vehicle::GetInstance().Clear();
            Location* l = Vehicle::GetInstance().GetFullLocation(m_step);
            Vehicle::GetInstance().GetStrips()[l->strip]->leds[l->led] = CHSV(0, 255, 255);
            if (m_step > Vehicle::GetInstance().GetTotal() - 1) {

                m_step = 0;
            }
        }

        void reset() {}

    private:
        int m_step;
};

#endif