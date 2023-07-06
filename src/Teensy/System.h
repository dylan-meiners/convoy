#ifndef SYSTEM_H
#define SYSTEM_H

#include "FastLED.h"
#include <vector>
#include "Strip.h"
#include "ks.h"

typedef struct {
    int strip;
    int led;
} Location;

class System {

    public:
        System();

        static System& GetInstance() {

            static System* the_one_and_only = new System();
            return *the_one_and_only;
        }

        bool AddConfiguration(std::vector<Strip*>* strips);

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

            for (int i = 0; i < (int)m_strips->size(); i++) {

                (*m_strips)[i]->MoveHSVToRGB();
            }
        }

        Location* GetFullLocation(int index);

        void Filter(std::vector<Strip*>* dest, Strip::Type type);

        void Clear() {

            for (int i = 0; i < (int)m_strips->size(); i++) {

                for (int j = 0; j < (*m_strips)[i]->GetNumLEDs(); j++) {

                    (*m_strips)[i]->leds[j] = CHSV(0, 0, 0);
                }
            }
        }

        void SetAllHSV(uint8_t h, uint8_t s, uint8_t v) {

            for (int i = 0; i < (int)m_strips->size(); i++) {

                (*m_strips)[i]->SetAllHSV(h, s, v);
            }
        }

        void UniformSet(int index, uint8_t h, uint8_t s, uint8_t v);

        void ApplyReverse();

        enum Direction {
            kForward,
            kReversed
        };

    private:
        System(const System&) = delete;
        System& operator=(const System&) = delete;
        System(System&&) = delete;
        System& operator=(System&&) = delete;

        bool m_locked;
        int m_totalLEDs;
        std::vector<Strip*>* m_strips;
        std::vector<std::vector<Strip*>*> m_stripsSorted;
        Location* m_location;
};

#endif