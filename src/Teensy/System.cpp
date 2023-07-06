#include "System.h"

System::System() {
    m_locked = false;
    m_totalLEDs = 0;
    m_location = new Location;
    for (int i = 0; i < K_NUM_STRIP_TYPES; i++) {

        m_stripsSorted[i] = new std::vector<Strip*>;
    }
}

bool System::AddConfiguration(std::vector<Strip*>* strips) {

    if (m_locked) return false;
    m_locked = true;

    m_strips = strips;
    for (int i = 0; i < (int)m_strips->size(); i++) {

        m_stripsSorted[(*m_strips)[i]->GetType()]->push_back((*m_strips)[i]);

        m_totalLEDs += (*m_strips)[i]->GetNumLEDs();
        switch ((*m_strips)[i]->GetPin()) {

            case 2:
                FastLED.addLeds<WS2812B, 2, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 3:
                FastLED.addLeds<WS2812B, 3, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 4:
                FastLED.addLeds<WS2812B, 4, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 5:
                FastLED.addLeds<WS2812B, 5, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 6:
                FastLED.addLeds<WS2812B, 6, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 7:
                FastLED.addLeds<WS2812B, 7, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 8:
                FastLED.addLeds<WS2812B, 8, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 9:
                FastLED.addLeds<WS2812B, 9, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 10:
                FastLED.addLeds<WS2812B, 10, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 11:
                FastLED.addLeds<WS2812B, 11, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 12:
                FastLED.addLeds<WS2812B, 12, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 13:
                FastLED.addLeds<WS2812B, 13, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 14:
                FastLED.addLeds<WS2812B, 14, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 15:
                FastLED.addLeds<WS2812B, 15, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 16:
                FastLED.addLeds<WS2812B, 16, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 17:
                FastLED.addLeds<WS2812B, 17, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 18:
                FastLED.addLeds<WS2812B, 18, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 19:
                FastLED.addLeds<WS2812B, 19, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 20:
                FastLED.addLeds<WS2812B, 20, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 21:
                FastLED.addLeds<WS2812B, 21, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 22:
                FastLED.addLeds<WS2812B, 22, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 23:
                FastLED.addLeds<WS2812B, 23, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 24:
                FastLED.addLeds<WS2812B, 24, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 25:
                FastLED.addLeds<WS2812B, 25, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 26:
                FastLED.addLeds<WS2812B, 26, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 27:
                FastLED.addLeds<WS2812B, 27, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 28:
                FastLED.addLeds<WS2812B, 28, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 29:
                FastLED.addLeds<WS2812B, 29, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 30:
                FastLED.addLeds<WS2812B, 30, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 31:
                FastLED.addLeds<WS2812B, 31, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 32:
                FastLED.addLeds<WS2812B, 32, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 33:
                FastLED.addLeds<WS2812B, 33, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 34:
                FastLED.addLeds<WS2812B, 34, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 35:
                FastLED.addLeds<WS2812B, 35, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 36:
                FastLED.addLeds<WS2812B, 36, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 37:
                FastLED.addLeds<WS2812B, 37, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 38:
                FastLED.addLeds<WS2812B, 38, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            case 39:
                FastLED.addLeds<WS2812B, 39, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                break;
            default:
                //TODO: This is not the way.
                exit(-1);
                break;
        }
    }

    return true;
}

Location* System::GetFullLocation(int index) {

    if (index < 0 || index >= m_totalLEDs) return nullptr;

    int runningIndex = 0;
    for (m_location->strip = 0; m_location->strip < (int)m_strips->size(); m_location->strip++) {
        if (runningIndex + (*m_strips)[m_location->strip]->GetNumLEDs() > index) {

            m_location->led = index - runningIndex;
            return m_location;
        }
        runningIndex += (*m_strips)[m_location->strip]->GetNumLEDs();
    }
    return nullptr;
}

void System::Filter(std::vector<Strip*>* dest, Strip::Type type) {

    dest->clear();
    for (int i = 0; i < (int)m_strips->size(); i++) {

        if ((*m_strips)[i]->GetType() == type) {

            dest->push_back((*m_strips)[i]);
        }
    }
}

void System::UniformSet(int index, uint8_t h, uint8_t s, uint8_t v) {
    for (int i = 0; i < (int)m_strips->size(); i++) {
        Strip* strip = (*m_strips)[i];

        if (index < strip->GetNumLEDs()) {
            strip->leds[i] = CHSV(h, s, v);
        }
    }
}

void System::ApplyReverse() {

    for (int i = 0; i < (int)m_strips->size(); i++) {

        Strip* strip = (*m_strips)[i];
        if (strip->IsReversed()) {

            for (int i = 0; i < strip->GetNumLEDs(); i++) {

                strip->tmp[i] = strip->leds[strip->GetNumLEDs() - 1 - i];
                for (int k = 0; k < strip->GetNumLEDs(); k++) {

                    strip->leds[i] = strip->tmp[i];
                }
            }
        }
    }
}