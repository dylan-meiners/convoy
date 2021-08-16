#ifndef STRIP_H
#define STRIP_H

#include <FastLED.h>
#include "ks.h"

class Strip {

    public:
        enum Type {

            kFront,
            kBack,
            kTop,
            kLeft,
            kRight,
            kNone
        };

        Strip(const int pinToSet, const int numLEDsToSet, Type typeToSet, const int reversed) {

            m_pin = pinToSet;
            m_numLEDs = numLEDsToSet;
            m_type = typeToSet;
            m_rgb = new CRGB[m_numLEDs];
            leds = new CHSV[m_numLEDs];
            tmp = new CHSV[m_numLEDs];
            m_reversed = reversed;
        }

        void MoveHSVToRGB() {

            for (int i = 0; i < m_numLEDs; i++) {

                m_rgb[i] = leds[m_reversed ? m_numLEDs - 1 - i : i];
            }
        }

        int GetPin() {

            return m_pin;
        }

        int GetNumLEDs() {

            return m_numLEDs;
        }

        CRGB* GetRGBArray() {

            return m_rgb;
        }

        bool IsReversed() {

            return m_reversed;
        }

        void SetAllHSV(uint8_t h, uint8_t s, uint8_t v) {

            for (int i = 0; i < m_numLEDs; i++) {

                leds[i] = CHSV(h, s, v);
            }
        }

        void Clear() {

            SetAllHSV(
                K_COLOR_HSV_H_OFF,
                K_COLOR_HSV_S_OFF,
                K_COLOR_HSV_V_OFF
            );
        }

        Type GetType() {

            return m_type;
        }

        CHSV* leds;
        CHSV* tmp;

    private:
        int m_pin;
        int m_numLEDs;
        Type m_type;
        CRGB* m_rgb;
        bool m_reversed;
};

#endif