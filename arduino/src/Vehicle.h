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

        bool AddConfiguration(std::vector<Strip*>* m_strips) {

            if (m_locked) return false;
            m_locked = true;

            m_strips = m_strips;
            for (int i = 0; i < m_strips->size(); i++) {

                switch ((*m_strips)[i]->GetPin()) {

                    case 2:
                        FastLED.addLeds<WS2811, 2>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 3:
                        FastLED.addLeds<WS2811, 3>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 4:
                        FastLED.addLeds<WS2811, 4>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 5:
                        FastLED.addLeds<WS2811, 5>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 6:
                        FastLED.addLeds<WS2811, 6>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 7:
                        FastLED.addLeds<WS2811, 7>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 8:
                        FastLED.addLeds<WS2811, 8>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 9:
                        FastLED.addLeds<WS2811, 9>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 10:
                        FastLED.addLeds<WS2811, 10>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 11:
                        FastLED.addLeds<WS2811, 11>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 12:
                        FastLED.addLeds<WS2811, 12>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 13:
                        FastLED.addLeds<WS2811, 13>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 14:
                        FastLED.addLeds<WS2811, 14>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 15:
                        FastLED.addLeds<WS2811, 15>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 16:
                        FastLED.addLeds<WS2811, 16>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 17:
                        FastLED.addLeds<WS2811, 17>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 18:
                        FastLED.addLeds<WS2811, 18>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 19:
                        FastLED.addLeds<WS2811, 19>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 20:
                        FastLED.addLeds<WS2811, 20>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 21:
                        FastLED.addLeds<WS2811, 21>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 22:
                        FastLED.addLeds<WS2811, 22>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 23:
                        FastLED.addLeds<WS2811, 23>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 24:
                        FastLED.addLeds<WS2811, 24>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 25:
                        FastLED.addLeds<WS2811, 25>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 26:
                        FastLED.addLeds<WS2811, 26>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 27:
                        FastLED.addLeds<WS2811, 27>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 28:
                        FastLED.addLeds<WS2811, 28>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 29:
                        FastLED.addLeds<WS2811, 29>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 30:
                        FastLED.addLeds<WS2811, 30>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 31:
                        FastLED.addLeds<WS2811, 31>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 32:
                        FastLED.addLeds<WS2811, 32>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 33:
                        FastLED.addLeds<WS2811, 33>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 34:
                        FastLED.addLeds<WS2811, 34>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 35:
                        FastLED.addLeds<WS2811, 35>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 36:
                        FastLED.addLeds<WS2811, 36>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 37:
                        FastLED.addLeds<WS2811, 37>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 38:
                        FastLED.addLeds<WS2811, 38>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 39:
                        FastLED.addLeds<WS2811, 39>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 40:
                        FastLED.addLeds<WS2811, 40>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 41:
                        FastLED.addLeds<WS2811, 41>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 42:
                        FastLED.addLeds<WS2811, 42>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 43:
                        FastLED.addLeds<WS2811, 43>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 44:
                        FastLED.addLeds<WS2811, 44>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 45:
                        FastLED.addLeds<WS2811, 45>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 46:
                        FastLED.addLeds<WS2811, 46>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 47:
                        FastLED.addLeds<WS2811, 47>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 48:
                        FastLED.addLeds<WS2811, 48>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 49:
                        FastLED.addLeds<WS2811, 49>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 50:
                        FastLED.addLeds<WS2811, 50>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 51:
                        FastLED.addLeds<WS2811, 51>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 52:
                        FastLED.addLeds<WS2811, 52>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    case 53:
                        FastLED.addLeds<WS2811, 53>((*m_strips)[i]->leds, (*m_strips)[i]->GetNumLEDs());
                    default:
                        //TODO: This is not the way.
                        exit(-1);
                }
                m_totalLEDs += (*m_strips)[i]->GetNumLEDs();
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

            if (index < 0 || index > m_totalLEDs) return nullptr;
            
            Location* toReturn = new Location;
            int runningIndex = 0;
            for (toReturn->strip = 0; toReturn->strip < m_strips->size(); toReturn->strip++) {

                if (runningIndex + (*m_strips)[toReturn->strip]->GetNumLEDs() > index) {

                    toReturn->led = index - runningIndex - 1;
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