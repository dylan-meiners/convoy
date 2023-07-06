#ifndef RAINBOWWAVE_H
#define RAINBOWWAVE_H

#include "FastLED.h"

#include <vector>
#include "Mode.h"
#include "System.h"
#include "ks.h"

class RainbowWave : public Mode {

    public:
        RainbowWave();

        bool step();

        void reset();

    private:
        double m_waveSpeedScalar;

        void parse();

        double m_waveCounter;
};

#endif