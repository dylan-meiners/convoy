#ifndef FLOWUNIFORM_H
#define FLOWUNIFORM_H

/**
 * TODO
 * (1) Add functionality for reverse direction
 * (2) Change from random decay on each step to random decay particles
 * (3) Add functionality for velocity ramping
 */

#include "Mode.h"
#include "System.h"
#include "Timer.h"
#include "ks.h"

class FlowUniform : public Mode {

    public:
        FlowUniform(System::Direction direction = System::Direction::kForward);

        bool step();

        void reset();

    private:
        int m_flowLength;
        double m_speed;
        CHSV m_color;

        void parse();

        void ResetHead() {

            m_head = m_dir == System::Direction::kForward ? 0 : System::GetInstance().GetStrips()[0]->GetNumLEDs();
        }

        void RandomFadeToBlack();

        System::Direction m_dir;
        int m_head;

        uint8_t* m_fade;
        Timer* m_timer;
        Timer* m_fadeTimer;
};

#endif