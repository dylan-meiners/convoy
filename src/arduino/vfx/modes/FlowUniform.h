#ifndef FLOWUNIFORM_H
#define FLOWUNIFORM_H

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

class FlowUniform : public Mode {

    public:
        FlowUniform(Vehicle::Direction direction = Vehicle::Direction::kForward) {

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
            m_fade = new uint8_t[Vehicle::GetInstance().GetStrips()[0]->GetNumLEDs()];
            // memset(m_fade, 0, Vehicle::GetInstance().GetStrips()[0]->GetNumLEDs());
            ResetHead();
        }

        bool step() {

            RandomFadeToBlack();

            if (m_timer->RunInterval()) {

                if (m_dir == Vehicle::Direction::kForward) {
                
                    for (int i = 0; i < m_flowLength; i++) {
                        
                        Vehicle::GetInstance().UniformSet(m_head + i, m_color.h, m_color.s, m_color.v);
                        m_fade[m_head] = random(8) + 1;
                    }

                    // If we just hit the last led
                    if (++m_head + m_flowLength - 1 >= Vehicle::GetInstance().GetStrips()[0]->GetNumLEDs()) {

                        m_dir = Vehicle::Direction::kReversed;
                        m_head = Vehicle::GetInstance().GetStrips()[0]->GetNumLEDs() - 2;
                    }
                }
                else {

                    for (int i = 0; i < m_flowLength; i++) {
                        
                        Vehicle::GetInstance().UniformSet(m_head - i, m_color.h, m_color.s, m_color.v);
                        m_fade[m_head] = random(8) + 1;
                    }

                    // If we just hit the last led
                    if (--m_head - (m_flowLength - 1) < 0) {

                        m_dir = Vehicle::Direction::kForward;
                        m_head = 1;
                    }
                }
            }
            return false;
        }

        void reset() {

            // memset(m_fade, 0, Vehicle::GetInstance().GetStrips()[0]->GetNumLEDs());
            ResetHead();
            m_timer->SetInterval(m_speed);
            m_timer->Restart();
            m_fadeTimer->SetIterationInterval(K_MODE_FLOW_FADE_ITER);
        }

        void RandomFadeToBlack() {

            for (int i = 0; i < Vehicle::GetInstance().GetStrips()[0]->GetNumLEDs(); i++) {

                if (m_fade[i] > 0) {
                
                    if (m_fadeTimer->RunIterationInterval()) {
                        
                        for (int j = 0; j < Vehicle::GetInstance().GetStrips().size(); j++) {

                            Vehicle::GetInstance().GetStrips()[j]->leds[i].h++;
                        }
                    }
                    for (int j = 0; j < Vehicle::GetInstance().GetStrips().size(); j++) {
                        
                        uint8_t* v = &Vehicle::GetInstance().GetStrips()[j]->leds[i].v;
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

            m_head = m_dir == Vehicle::Direction::kForward ? 0 : Vehicle::GetInstance().GetStrips()[0]->GetNumLEDs();
        }

        Vehicle::Direction m_dir;
        int m_head;

        uint8_t* m_fade;
        Timer* m_timer;
        Timer* m_fadeTimer;
};

#endif