#ifndef FLOW_H
#define FLOW_H

/**
 * TODO
 * (1) Add functionality for reverse direction
 * (2) Change from random decay on each step to random decay particles
 * (3) Add functionality for velocity ramping
 */

#include "../Mode.h"
#include "../../Vehicle.h"
#include "../../Timer.h"
#include "../../ks.h"

class Flow : public Mode {

    public:
        Flow(Vehicle::Direction direction = Vehicle::Direction::kForward) {

            m_dir = direction;
            dataLength = K_MODE_DATA_LENGTH_FLOW;
            data = new uint8_t[dataLength];
            m_flowLength = K_MODE_FLOW_LENGTH;
            m_flowPercentPerSecond = K_MODE_FLOW_PERCENT_PER_SECOND;
            m_color = CHSV(
                K_MODE_FLOW_COLOR_HSV_H,
                K_MODE_FLOW_COLOR_HSV_S,
                K_MODE_FLOW_COLOR_HSV_V
            );
            m_fade = new uint8_t[Vehicle::GetInstance().GetTotal()];
            memset(m_fade, 0, Vehicle::GetInstance().GetTotal());
            ResetHead();
        }

        bool _step() {

            RandomFadeToBlack();

            for (int i = 0; i < m_flowLength; i++) {

                if (m_head + i < Vehicle::GetInstance().GetTotal()) {
                
                    Location* l = Vehicle::GetInstance().GetFullLocation(m_head + i);
                    Vehicle::GetInstance().GetStrips()[l->strip]->leds[l->led] = m_color;
                }
                m_fade[m_head] = 15;//random(15) + 15;
            }

            if (++m_head >= Vehicle::GetInstance().GetTotal()) {

                m_head = 0;
            }
            return false;
        }

        void reset() {

            memset(m_fade, 0, Vehicle::GetInstance().GetTotal());
            ResetHead();
        }

        void RandomFadeToBlack() {

            for (int i = 0; i < Vehicle::GetInstance().GetTotal(); i++) {

                if (m_fade[i] > 0) {
                
                    Location* l = Vehicle::GetInstance().GetFullLocation(i);
                    uint8_t* v = &Vehicle::GetInstance().GetStrips()[l->strip]->leds[l->led].v;
                    if (*v < m_fade[i]) {

                        *v = 0;
                        m_fade[i] = 0;
                    }
                    else {
                        
                        *v -= m_fade[i];
                    }
                }
            }
        }

    private:
        int m_flowLength;
        double m_flowPercentPerSecond;
        CHSV m_color;

        void _parse() {

            m_flowLength = data[0];
            m_flowPercentPerSecond = data[1] / 255.0;
            m_color = CHSV(
                data[2],
                data[3],
                data[4]
            );
        }

        void ResetHead() {

            m_head = m_dir == Vehicle::Direction::kForward ? 0 : Vehicle::GetInstance().GetTotal();
        }

        Vehicle::Direction m_dir;
        int m_head;

        uint8_t* m_fade;

};

#endif