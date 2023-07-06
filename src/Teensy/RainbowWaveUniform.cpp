#include "RainbowWaveUniform.h"

RainbowWaveUniform::RainbowWaveUniform() {

    m_waveCounter = 0.0;
    dataLength = K_MODE_DATA_LENGTH_RAINBOW_WAVE;
    data = new char[dataLength];
    m_waveSpeedScalar = K_MODE_RAINBOW_WAVE_SPEED_SCALAR;
}

bool RainbowWaveUniform::step() {

    for (int i = 0; i < (int)System::GetInstance().GetStrips().size(); i++) {

        Strip* current = System::GetInstance().GetStrips()[i];
        for (int j = 0; j < current->GetNumLEDs(); j++) {

            current->leds[j] = CHSV(
                fmod((j * 255.0 / (double)System::GetInstance().GetStrips()[0]->GetNumLEDs()) + m_waveCounter * m_waveSpeedScalar, 255.0),
                255,
                255
            );
        }
    }
    m_waveCounter += (255.0 / (double)System::GetInstance().GetStrips()[0]->GetNumLEDs()) * m_waveSpeedScalar;
    return false;
}

void RainbowWaveUniform::reset() {

    m_waveCounter = 0.0;
}

void RainbowWaveUniform::parse() {

    m_waveSpeedScalar = data[0] / 255.0;
}