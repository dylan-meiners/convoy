#ifndef FLOW_H
#define FLOW_H

/**
 * TODO
 * (1) Add functionality for reverse direction
 * (2) Change from random decay on each step to random decay particles
 * (3) Add functionality for velocity ramping
 */

#include "../Mode.h"
#include "../../System.h"
#include "../../Timer.h"
#include "../../ks.h"

class Flow : public Mode {

    public:
        Flow(System::Direction direction = System::Direction::kForward) {

            m_dir = direction;
            dataLength = K_MODE_DATA_LENGTH_FLOW;
            m_timer = new Timer;
            m_fadeTimer = new Timer;
            data = new uint8_t[dataLength];
            m_flowLength = K_MODE_FLOW_LENGTH;
            m_speed = K_MODE_FLOW_SPEED_MS;
            m_color = CHSV(
                K_MODE_FLOW_COLOR_HSV_H,
                K_MODE_FLOW_COLOR_HSV_S,
                K_MODE_FLOW_COLOR_HSV_V
            );
            m_fade = new uint8_t[System::GetInstance().GetTotal()];
            memset(m_fade, 0, System::GetInstance().GetTotal());
            ResetHead();
        }

        bool step() {

            RandomFadeToBlack();

            if (m_timer->RunInterval()) {

                if (m_dir == System::Direction::kForward) {
                
                    for (int i = 0; i < m_flowLength; i++) {
                        
                        Location* l = System::GetInstance().GetFullLocation(m_head + i);
                        System::GetInstance().GetStrips()[l->strip]->leds[l->led] = m_color;
                        m_fade[m_head] = random(8) + 1;
                    }

                    // If we just hit the last led
                    if (++m_head + m_flowLength - 1 >= System::GetInstance().GetTotal()) {

                        m_dir = System::Direction::kReversed;
                        m_head = System::GetInstance().GetTotal() - 2;
                    }
                }
                else {

                    for (int i = 0; i < m_flowLength; i++) {
                        
                        Location* l = System::GetInstance().GetFullLocation(m_head - i);
                        System::GetInstance().GetStrips()[l->strip]->leds[l->led] = m_color;
                        m_fade[m_head] = random(8) + 1;
                    }

                    // If we just hit the last led
                    if (--m_head - (m_flowLength - 1) < 0) {

                        m_dir = System::Direction::kForward;
                        m_head = 1;
                    }
                }
            }
            return false;
        }

        void reset() {

            memset(m_fade, 0, System::GetInstance().GetTotal());
            ResetHead();
            m_timer->SetInterval(m_speed);
            m_timer->Restart();
            m_fadeTimer->SetIterationInterval(K_MODE_FLOW_FADE_ITER);
        }

        void RandomFadeToBlack() {

            for (int i = 0; i < System::GetInstance().GetTotal(); i++) {

                if (m_fade[i] > 0) {
                
                    Location* l = System::GetInstance().GetFullLocation(i);
                    if (m_fadeTimer->RunIterationInterval()) {
                        
                        System::GetInstance().GetStrips()[l->strip]->leds[l->led].h++;
                    }
                    uint8_t* v = &System::GetInstance().GetStrips()[l->strip]->leds[l->led].v;
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
        double m_speed;
        CHSV m_color;

        void parse() {

            m_flowLength = data[0];
            m_speed = data[1];
            m_color = CHSV(
                data[2],
                data[3],
                data[4]
            );
        }

        void ResetHead() {

            m_head = m_dir == System::Direction::kForward ? 0 : System::GetInstance().GetTotal();
        }

        System::Direction m_dir;
        int m_head;

        uint8_t* m_fade;
        Timer* m_timer;
        Timer* m_fadeTimer;
};

#endif