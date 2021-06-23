#ifndef STRIP_H
#define STRIP_H

#include <FastLED.h>

class Strip {

    public:
        enum Type {

            kFront,
            kBack,
            kTop,
            kLeft,
            kRight
        };

        Strip(const int pinToSet, const int numLEDsToSet, Type typeToSet) {

            m_pin = pinToSet;
            m_numLEDs = numLEDsToSet;
            m_type = typeToSet;
            leds = new CRGB[m_numLEDs];
        }

        int GetPin() {

            return m_pin;
        }

        int GetNumLEDs() {

            return m_numLEDs;
        }

        CRGB* leds;

    private:
        int m_pin;
        int m_numLEDs;
        Type m_type;
};

#endif