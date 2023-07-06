#ifndef COLORPULSE_H
#define COLORPULSE_H

#include "Mode.h"
#include "System.h"
#include "ks.h"
#include "Timer.h"

class ColorPulse : public Mode {

    public:
        ColorPulse();

        bool step();

        void reset();

        void SetColor(uint8_t color) {
            m_color = color;
        }

    private:
        void Set(bool on = true) {

            System::GetInstance().SetAllHSV(K_COLOR_HSV_H_GREEN, K_COLOR_HSV_S_GREEN, on ? K_COLOR_HSV_V_GREEN : 0);
        }

        enum Status {
            kFirstOn,
            kFirstOff,
            kSecondOn,
            kSecondOff
        };

        void parse();

        Timer* m_timer;
        Status m_status;

        uint8_t m_color;
};

#endif