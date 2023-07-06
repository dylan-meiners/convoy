#include "FlowUniform.h"

FlowUniform::FlowUniform(System::Direction direction) {

    m_dir = direction;
    dataLength = K_MODE_DATA_LENGTH_FLOW;
    m_timer = new Timer;
    m_fadeTimer = new Timer;
    data = new char[dataLength];
    m_flowLength = K_MODE_FLOW_LENGTH;
    m_speed = K_MODE_FLOW_SPEED_MS;
    m_color = CHSV(
        K_MODE_FLOW_COLOR_HSV_H,
        K_MODE_FLOW_COLOR_HSV_S,
        K_MODE_FLOW_COLOR_HSV_V
    );
    m_fade = new uint8_t[System::GetInstance().GetStrips()[0]->GetNumLEDs()];
    // memset(m_fade, 0, System::GetInstance().GetStrips()[0]->GetNumLEDs());
    ResetHead();
}

bool FlowUniform::step() {

    RandomFadeToBlack();

    if (m_timer->RunInterval()) {

        if (m_dir == System::Direction::kForward) {

            for (int i = 0; i < m_flowLength; i++) {

                System::GetInstance().UniformSet(m_head + i, m_color.h, m_color.s, m_color.v);
                m_fade[m_head] = random(8) + 1;
            }

            // If we just hit the last led
            if (++m_head + m_flowLength - 1 >= System::GetInstance().GetStrips()[0]->GetNumLEDs()) {

                m_dir = System::Direction::kReversed;
                m_head = System::GetInstance().GetStrips()[0]->GetNumLEDs() - 2;
            }
        }
        else {

            for (int i = 0; i < m_flowLength; i++) {

                System::GetInstance().UniformSet(m_head - i, m_color.h, m_color.s, m_color.v);
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

void FlowUniform::reset() {

    // memset(m_fade, 0, System::GetInstance().GetStrips()[0]->GetNumLEDs());
    ResetHead();
    m_timer->SetInterval(m_speed);
    m_timer->Restart();
    m_fadeTimer->SetIterationInterval(K_MODE_FLOW_FADE_ITER);
}

void FlowUniform::RandomFadeToBlack() {

    for (int i = 0; i < System::GetInstance().GetStrips()[0]->GetNumLEDs(); i++) {

        if (m_fade[i] > 0) {

            if (m_fadeTimer->RunIterationInterval()) {

                for (int j = 0; j < (int)System::GetInstance().GetStrips().size(); j++) {

                    System::GetInstance().GetStrips()[j]->leds[i].h++;
                }
            }
            for (int j = 0; j < (int)System::GetInstance().GetStrips().size(); j++) {

                uint8_t* v = &System::GetInstance().GetStrips()[j]->leds[i].v;
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

void FlowUniform::parse() {

    m_flowLength = data[0];
    m_speed = data[1];
    m_color = CHSV(
        data[2],
        data[3],
        data[4]
    );
}