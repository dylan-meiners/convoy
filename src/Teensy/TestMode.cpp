#include "TestMode.h"

TestMode::TestMode() {

    m_step = 0;
    m_forward = true;
    m_timer = new Timer;
    m_timer->SetInterval(0);
    dataLength = 0;
    data = nullptr;
}

bool TestMode::step() {

    if (m_timer->RunInterval()) {

        System::GetInstance().Clear();
        Location* l = System::GetInstance().GetFullLocation(m_step);
        System::GetInstance().GetStrips()[l->strip]->leds[l->led] = CHSV(0, 255, 255);
        if (m_forward) {

            m_step++;
            if (m_step > System::GetInstance().GetTotal() - 1) {

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

void TestMode::reset() {

    m_step = 0;
    m_forward = true;
    m_timer->Restart();
}