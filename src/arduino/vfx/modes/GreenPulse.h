#ifndef GREENPULSE_H
#define GREENPULSE_H

#include "../Mode.h"
#include "../../System.h"
#include "../../ks.h"
#include "../../Timer.h"

class GreenPulse : public Mode {

    public:
        GreenPulse() {

            m_timer = new Timer;
            m_status = kFirstOn;
            dataLength = K_MODE_DATA_LENGTH_GREEN_PULSE;
            data = nullptr;
        }

        bool step() {
            
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

        void reset() {

            m_status = kFirstOn;
            m_timer->Restart();
        }
        
        void parse() {}

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

        Timer* m_timer;
        Status m_status;
};

#endif