#ifndef VEHICLE_H
#define VEHICLE_H

#include <FastLED.h>
#include "ArduinoSTL.h"
#include <vector>
#include "Strip.h"
#include "ks.h"

typedef struct {
    int strip;
    int led;
} Location;

class Vehicle {

    public:
        Vehicle() {

            m_locked = false;
            m_totalLEDs = 0;
            m_location = new Location;
            for (int i = 0; i < K_NUM_STRIP_TYPES; i++) {

                m_stripsSorted[i] = new std::vector<Strip*>;
            }
        }

        static Vehicle& GetInstance() {

            static Vehicle* the_one_and_only = new Vehicle();
            return *the_one_and_only;
        }

        bool AddConfiguration(std::vector<Strip*>* strips) {

            if (m_locked) return false;
            m_locked = true;

            m_strips = strips;
            for (int i = 0; i < m_strips->size(); i++) {

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
                    case 40:
                        FastLED.addLeds<WS2812B, 40, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 41:
                        FastLED.addLeds<WS2812B, 41, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 42:
                        FastLED.addLeds<WS2812B, 42, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 43:
                        FastLED.addLeds<WS2812B, 43, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 44:
                        FastLED.addLeds<WS2812B, 44, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 45:
                        FastLED.addLeds<WS2812B, 45, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 46:
                        FastLED.addLeds<WS2812B, 46, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 47:
                        FastLED.addLeds<WS2812B, 47, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 48:
                        FastLED.addLeds<WS2812B, 48, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 49:
                        FastLED.addLeds<WS2812B, 49, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 50:
                        FastLED.addLeds<WS2812B, 50, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 51:
                        FastLED.addLeds<WS2812B, 51, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 52:
                        FastLED.addLeds<WS2812B, 52, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 53:
                        FastLED.addLeds<WS2812B, 53, GRB>((*m_strips)[i]->GetRGBArray(), (*m_strips)[i]->GetNumLEDs());
                        break;
                    default:
                        //TODO: This is not the way.
                        exit(-1);
                        break;
                }
            }

            return true;
        }

        std::vector<Strip*>& GetStrips() {

            return (*m_strips);
        }

        std::vector<Strip*>* GetStripsByType(Strip::Type type) {

            return m_stripsSorted[type];
        }

        int GetTotal() {

            return m_totalLEDs;
        }

        void MoveHSVToRGB() {

            for (int i = 0; i < m_strips->size(); i++) {

                (*m_strips)[i]->MoveHSVToRGB();
            }
        }

        Location* GetFullLocation(int index) {

            if (index < 0 || index >= m_totalLEDs) return nullptr;

            int runningIndex = 0;
            for (m_location->strip = 0; m_location->strip < m_strips->size(); m_location->strip++) {
                if (runningIndex + (*m_strips)[m_location->strip]->GetNumLEDs() > index) {

                    m_location->led = index - runningIndex;
                    return m_location;
                }
                runningIndex += (*m_strips)[m_location->strip]->GetNumLEDs();
            }
            return nullptr;
        }

        void Filter(std::vector<Strip*>* dest, Strip::Type type) {

            dest->clear();
            for (int i = 0; i < m_strips->size(); i++) {

                if ((*m_strips)[i]->GetType() == type) {

                    dest->push_back((*m_strips)[i]);
                }
            }
        }

        void Clear() {

            for (int i = 0; i < m_strips->size(); i++) {

                for (int j = 0; j < (*m_strips)[i]->GetNumLEDs(); j++) {

                    (*m_strips)[i]->leds[j] = CHSV(0, 0, 0);
                }
            }
        }

        void SetAllHSV(uint8_t h, uint8_t s, uint8_t v) {

            for (int i = 0; i < m_strips->size(); i++) {

                (*m_strips)[i]->SetAllHSV(h, s, v);
            }
        }

        enum Direction {
            kForward,
            kReversed
        };

    private:
        Vehicle(const Vehicle&) = delete;
        Vehicle& operator=(const Vehicle&) = delete;
        Vehicle(Vehicle&&) = delete;
        Vehicle& operator=(Vehicle&&) = delete;

        bool m_locked;
        int m_totalLEDs;
        std::vector<Strip*>* m_strips;
        std::vector<std::vector<Strip*>*> m_stripsSorted;
        Location* m_location;
};

#endif