#include "RainbowWave.h"

RainbowWave::RainbowWave() {

    m_waveCounter = 0.0;
    dataLength = K_MODE_DATA_LENGTH_RAINBOW_WAVE;
    data = new char[dataLength];
    m_waveSpeedScalar = K_MODE_RAINBOW_WAVE_SPEED_SCALAR;
}

bool RainbowWave::step() {

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

void RainbowWave::reset() {

    m_waveCounter = 0.0;
}

void RainbowWave::parse() {

    m_waveCounter = data[0] == 1 ? 0.0 : m_waveCounter;
    m_waveSpeedScalar = data[1] / 127.0;
}