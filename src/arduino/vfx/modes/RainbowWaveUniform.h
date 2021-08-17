#ifndef RAINBOWWAVEUNIFORM_H
#define RAINBOWWAVEUNIFORM_H

#include <FastLED.h>
#include <ArduinoSTL.h>
#include <vector>
#include "../Mode.h"
#include "../../Vehicle.h"
#include "../../ks.h"

class RainbowWaveUniform : public Mode {

    public:
        RainbowWaveUniform() {

            m_waveCounter = 0.0;
            dataLength = K_MODE_DATA_LENGTH_RAINBOW_WAVE;
            data = new uint8_t[dataLength];
            m_waveSpeedScalar = K_MODE_RAINBOW_WAVE_SPEED_SCALAR;
        }

        bool step() {
            
            for (int i = 0; i < Vehicle::GetInstance().GetStrips().size(); i++) {
                
                Strip* current = Vehicle::GetInstance().GetStrips()[i];
                for (int j = 0; j < current->GetNumLEDs(); j++) {

                    current->leds[j] = CHSV(
                        fmod((j * 255.0 / (double)Vehicle::GetInstance().GetStrips()[0]->GetNumLEDs()) + m_waveCounter * m_waveSpeedScalar, 255.0),
                        255,
                        255
                    );
                }
            }
            m_waveCounter += (255.0 / (double)Vehicle::GetInstance().GetStrips()[0]->GetNumLEDs()) * m_waveSpeedScalar;
            return false;
        }

        void reset() {

            m_waveCounter = 0.0;
        }

    private:
        double m_waveSpeedScalar;

        void parse() {

            m_waveSpeedScalar = data[0] / 255.0;
        }

        double m_waveCounter;
};

#endif