#include "ColorPulse.h"

ColorPulse::ColorPulse() {

    m_timer = new Timer;
    m_status = kFirstOn;
    dataLength = K_MODE_DATA_LENGTH_GREEN_PULSE;
    data = new char[K_MODE_DATA_LENGTH_GREEN_PULSE];
    m_color = K_COLOR_HSV_V_RED;
}

bool ColorPulse::step() {

    switch (m_status) {

        case kFirstOn:
            if (m_timer->WhenElapsed(100)) {

                m_status = kFirstOff;
                m_timer->Restart();
            }
            else {

                Set();
            }
            break;
        case kFirstOff:
            if (m_timer->WhenElapsed(100)) {

                m_status = kSecondOn;
                m_timer->Restart();
            }
            else {

                Set(false);
            }
            break;
        case kSecondOn:
            if (m_timer->WhenElapsed(100)) {

                m_status = kSecondOff;
                m_timer->Restart();
            }
            else {

                Set();
            }
            break;
        case kSecondOff:
            if (m_timer->WhenElapsed(100)) {

                return true;
            }
            else {

                Set(false);
            }
            break;
    }
    return false;
}

void ColorPulse::reset() {

    m_status = kFirstOn;
    m_color = K_COLOR_HSV_V_GREEN;
    m_timer->Restart();
}

void ColorPulse::parse() {
    m_color = data[0];
}