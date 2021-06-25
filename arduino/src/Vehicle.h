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

                m_totalLEDs += (*m_strips)[i]->GetNumLEDs();
                switch ((*m_strips)[i]->GetPin()) {

                    case 2:
                        FastLED.addLeds<WS2812, 2, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 3:
                        FastLED.addLeds<WS2812, 3, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 4:
                        FastLED.addLeds<WS2812, 4, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 5:
                        FastLED.addLeds<WS2812, 5, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 6:
                        FastLED.addLeds<WS2812, 6, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 7:
                        FastLED.addLeds<WS2812, 7, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 8:
                        FastLED.addLeds<WS2812, 8, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 9:
                        FastLED.addLeds<WS2812, 9, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 10:
                        FastLED.addLeds<WS2812, 10, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 11:
                        FastLED.addLeds<WS2812, 11, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 12:
                        FastLED.addLeds<WS2812, 12, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 13:
                        FastLED.addLeds<WS2812, 13, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 14:
                        FastLED.addLeds<WS2812, 14, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 15:
                        FastLED.addLeds<WS2812, 15, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 16:
                        FastLED.addLeds<WS2812, 16, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 17:
                        FastLED.addLeds<WS2812, 17, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 18:
                        FastLED.addLeds<WS2812, 18, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 19:
                        FastLED.addLeds<WS2812, 19, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 20:
                        FastLED.addLeds<WS2812, 20, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 21:
                        FastLED.addLeds<WS2812, 21, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 22:
                        FastLED.addLeds<WS2812, 22, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 23:
                        FastLED.addLeds<WS2812, 23, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 24:
                        FastLED.addLeds<WS2812, 24, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 25:
                        FastLED.addLeds<WS2812, 25, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 26:
                        FastLED.addLeds<WS2812, 26, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 27:
                        FastLED.addLeds<WS2812, 27, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 28:
                        FastLED.addLeds<WS2812, 28, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 29:
                        FastLED.addLeds<WS2812, 29, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 30:
                        FastLED.addLeds<WS2812, 30, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 31:
                        FastLED.addLeds<WS2812, 31, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 32:
                        FastLED.addLeds<WS2812, 32, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 33:
                        FastLED.addLeds<WS2812, 33, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 34:
                        FastLED.addLeds<WS2812, 34, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 35:
                        FastLED.addLeds<WS2812, 35, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 36:
                        FastLED.addLeds<WS2812, 36, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 37:
                        FastLED.addLeds<WS2812, 37, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 38:
                        FastLED.addLeds<WS2812, 38, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 39:
                        FastLED.addLeds<WS2812, 39, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 40:
                        FastLED.addLeds<WS2812, 40, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 41:
                        FastLED.addLeds<WS2812, 41, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 42:
                        FastLED.addLeds<WS2812, 42, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 43:
                        FastLED.addLeds<WS2812, 43, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 44:
                        FastLED.addLeds<WS2812, 44, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 45:
                        FastLED.addLeds<WS2812, 45, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 46:
                        FastLED.addLeds<WS2812, 46, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 47:
                        FastLED.addLeds<WS2812, 47, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 48:
                        FastLED.addLeds<WS2812, 48, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 49:
                        FastLED.addLeds<WS2812, 49, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 50:
                        FastLED.addLeds<WS2812, 50, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 51:
                        FastLED.addLeds<WS2812, 51, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 52:
                        FastLED.addLeds<WS2812, 52, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                        break;
                    case 53:
                        FastLED.addLeds<WS2812, 53, GRB>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
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

        int GetTotal() {

            return m_totalLEDs;
        }

        Location* GetFullLocation(int index) {

            if (index < 0 || index >= m_totalLEDs) return nullptr;
            
            Location* toReturn = new Location;
            int runningIndex = 0;
            for (toReturn->strip = 0; toReturn->strip < m_strips->size(); toReturn->strip++) {

                if (runningIndex + (*m_strips)[toReturn->strip]->GetNumLEDs() > index) {

                    toReturn->led = index - runningIndex;
                    return toReturn;
                }
            }
            return nullptr;
        }

        void Clear() {

            for (int i = 0; i < m_strips->size(); i++) {

                for (int j = 0; j < (*m_strips)[i]->GetNumLEDs(); j++) {

                    (*m_strips)[i]->leds[j] = CHSV(0, 0, 0);
                }
            }
        }

    private:
        Vehicle(const Vehicle&) = delete;
        Vehicle& operator=(const Vehicle&) = delete;
        Vehicle(Vehicle&&) = delete;
        Vehicle& operator=(Vehicle&&) = delete;

        bool m_locked;
        int m_totalLEDs;
        std::vector<Strip*>* m_strips;
};

#endif