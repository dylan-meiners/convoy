#ifndef DRIVING_H
#define DRIVING_H

#include "Mode.h"
#include "ModeManager.h"
#include "System.h"
#include "Timer.h"
#include "ks.h"

class Driving : public Mode {

    public:
        Driving();

        bool step();

        void reset() {}

        void parse() {}

    private:
        bool m_leftWasOn;
        bool m_rightWasOn;
        bool m_runningWasOn;
        int m_leftOffHits;
        int m_rightOffHits;
        int m_runningOffHits;
        int m_ramp;
        Timer* m_flashersTimer;
        Timer* m_leftTimer;
        Timer* m_rightTimer;
};

#endif