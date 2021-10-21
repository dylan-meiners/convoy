#ifndef RAINBOWWAVE_H
#define RAINBOWWAVE_H

#include <FastLED.h>
#include <ArduinoSTL.h>
#include <vector>
#include "../Mode.h"
#include "../../System.h"
#include "../../ks.h"

class RainbowWave : public Mode {

    public:
        RainbowWave() {

            m_waveCounter = 0.0;
            dataLength = K_MODE_DATA_LENGTH_RAINBOW_WAVE;
            data = new uint8_t[dataLength];
            m_waveSpeedScalar = K_MODE_RAINBOW_WAVE_SPEED_SCALAR;
        }

        bool step() {
                
            for (int i = 0; i < System::GetInstance().GetTotal(); i++) {
                
                Location* l = System::GetInstance().GetFullLocation(i);
                System::GetInstance().GetStrips()[l->strip]->leds[l->led] = CHSV(
                    fmod((i * 255.0 / (double)System::GetInstance().GetTotal()) + m_waveCounter * m_waveSpeedScalar, 255.0),
                    255,
                    255
                );
            }
            m_waveCounter += (255.0 / (double)System::GetInstance().GetTotal()) * m_waveSpeedScalar;

            return false;
        }

        void reset() {

            m_waveCounter = 0.0;
        }

    private:
        double m_waveSpeedScalar;

        void parse() {

            m_waveCounter = data[0] == 1 ? 0.0 : m_waveCounter;
            m_waveSpeedScalar = data[1] / 127.0;
        }

        double m_waveCounter;
};

#endif