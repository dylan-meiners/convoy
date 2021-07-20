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
            ResetHead();
        }

        bool _step() {

            RandomFadeToBlack();

            for (int i = 0; i < m_flowLength; i++) {

                if (m_head + i < Vehicle::GetInstance().GetTotal()) {
                
                    Location* l = Vehicle::GetInstance().GetFullLocation(m_head + i);
                    Vehicle::GetInstance().GetStrips()[l->strip]->leds[l->led] = m_color;
                }
            }

            if (++m_head >= Vehicle::GetInstance().GetTotal()) {

                m_head = 0;
            }
            return false;
        }

        void reset() {

            ResetHead();
        }

        void RandomFadeToBlack() {

            for (int i = 0; i < Vehicle::GetInstance().GetTotal(); i++) {

                Location* l = Vehicle::GetInstance().GetFullLocation(i);
                uint8_t* old = &Vehicle::GetInstance().GetStrips()[l->strip]->leds[l->led].v;
                long rand = random(10);
                if (rand >= 5) {

                    *old -= *old >= 15 ? 15 : *old;
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

};

#endif