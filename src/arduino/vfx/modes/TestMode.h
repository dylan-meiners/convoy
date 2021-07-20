#ifndef TESTMODE_H
#define TESTMODE_H

#include <FastLED.h>
#include <ArduinoSTL.h>
#include <vector>
#include "../Mode.h"
#include "../../Vehicle.h"
#include "../../Timer.h"

class TestMode : public Mode {

    public:
        TestMode() {

            m_step = 0;
            m_forward = true;
            m_timer = new Timer;
            m_timer->SetInterval(0);
            dataLength = 0;
            data = nullptr;
        }

        bool _step() {

            if (m_timer->RunInterval()) {
            
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
            return false;
        }

        void reset() {

            m_step = 0;
            m_forward = true;
            m_timer->Restart();
        }

    private:
        void _parse() {}

        int m_step;
        bool m_forward;
        Timer* m_timer;
};

#endif