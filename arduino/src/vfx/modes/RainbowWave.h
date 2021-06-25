#ifndef RAINBOWWAVE_H
#define RAINBOWWAVE_H

#include <FastLED.h>
#include <ArduinoSTL.h>
#include <vector>
#include "../Mode.h"
#include "../../Vehicle.h"
#include "../../ks.h"

class RainbowWave : public Mode {

    public:
        RainbowWave() {

            m_waveCounter = 0.0;
        }

        void step() {
                
            for (int i = 0; i < Vehicle::GetInstance().GetTotal(); i++) {
                
                Location* l = Vehicle::GetInstance().GetFullLocation(i);
                Vehicle::GetInstance().GetStrips()[l->strip]->leds[l->led] = CHSV(
                    fmod((i * 255.0 / (double)Vehicle::GetInstance().GetTotal()) + m_waveCounter * WAVE_SPEED_SCALAR, 255.0),
                    255,
                    255
                );
                delete l;
            }
            m_waveCounter += (255.0 / (double)Vehicle::GetInstance().GetTotal()) * WAVE_SPEED_SCALAR;
        }

        void reset() {

            m_waveCounter = 0.0;
        }

    private:
        double m_waveCounter;
};

#endif