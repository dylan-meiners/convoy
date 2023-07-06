#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#include "Mode.h"
#include <vector>

class ModeManager {

    public:
        enum Mode_t {
            kTestMode,
            kRainbowWave,
            kColorPulse,
            kFlow,
            kDriving,
            kWarning
        };

        static void AddModes(std::vector<Mode*>& modesToSet) {

            modes = new Mode*[modesToSet.size()];
            for (int i = 0; i < (int)modesToSet.size(); i++) {

                modes[i] = modesToSet[i];
                modes[i]->reset();
            }
        }

        static void Step() {

            if(modes[m_activeMode]->step()) {

                // Do not use switchMode(E_Mode) because it will reset the mode. If
                // step returns true, then it is returning from a quick effect so,
                // strictly resume the previous mode.
                m_activeMode = m_oldMode;
            }
        }

        static Mode* GetMode(Mode_t mode) {

            return modes[mode];
        }

        static void SwitchMode(Mode_t modeToSwtichTo, bool force = false) {

            if (force || m_activeMode != modeToSwtichTo) {

                m_activeMode = modeToSwtichTo;
                modes[m_activeMode]->reset();
            }
        }

        static void PlayQuickMode(Mode_t modeToPlay) {

            m_oldMode = m_activeMode;
            SwitchMode(modeToPlay);
        }

    private:
        static Mode** modes;
        static Mode_t m_activeMode;
        static Mode_t m_oldMode;
};

#endif