#ifndef RAINBOWWAVEUNIFORM_H
#define RAINBOWWAVEUNIFORM_H

#include "FastLED.h"

#include <vector>
#include "Mode.h"
#include "System.h"
#include "ks.h"

class RainbowWaveUniform : public Mode {

    public:
        RainbowWaveUniform();

        bool step();

        void reset();

    private:
        double m_waveSpeedScalar;

        void parse();

        double m_waveCounter;
};

#endif