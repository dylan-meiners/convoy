#ifndef TESTMODE_H
#define TESTMODE_H

#include "FastLED.h"

#include <vector>
#include "Mode.h"
#include "System.h"
#include "Timer.h"

class TestMode : public Mode {

    public:
        TestMode();

        bool step();

        void reset();

    private:
        void parse() {}

        int m_step;
        bool m_forward;
        Timer* m_timer;
};

#endif