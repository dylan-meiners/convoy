#ifndef WARNING_H
#define WARNING_H

#include "Mode.h"
#include "System.h"
#include "Timer.h"
#include "ks.h"

class Warning : public Mode {

    public:
        Warning();

        bool step();

        void reset();
    
    private:
        enum {
            kRight,
            kLeft
        } m_side;

        enum {
            kFirst,
            kSecond
        } m_color;

        void parse() {}

        Timer* m_timer;
        Timer* m_strobeTimer;
};

#endif