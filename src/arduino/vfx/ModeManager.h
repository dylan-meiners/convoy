#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#include "Mode.h"
#include <vector>

class ModeManager {

    public:
        enum Mode_t {
            kTestMode,
            kRainbowWave,
            kGreenPulse,
            kFlow,
            kDriving,
            kWarning,
            kRainbowWaveUniform,
            kFlowUniform
        };

        ModeManager() {

            m_activeMode = kDriving;
            m_oldMode = kDriving;
        }

        static ModeManager& GetInstance() {

            static ModeManager* the_one_and_only = new ModeManager();
            return *the_one_and_only;
        }

        void AddModes(std::vector<Mode*>& modesToSet) {

            modes = new Mode*[modesToSet.size()];
            for (int i = 0; i < modesToSet.size(); i++) {

                modes[i] = modesToSet[i];
                modes[i]->reset();
            }
        }

        void Step() {

            if(modes[m_activeMode]->step()) {

                // Do not use switchMode(E_Mode) because it will reset the mode. If
                // step returns true, then it is returning from a quick effect so,
                // strictly resume the previous mode.
                m_activeMode = m_oldMode;
            }
        }

        Mode* GetMode(Mode_t mode) {

            return modes[mode];
        }

        void SwitchMode(Mode_t modeToSwtichTo, bool force = false) {

            if (force || m_activeMode != modeToSwtichTo) {

                m_activeMode = modeToSwtichTo;
                modes[m_activeMode]->reset();
            }
        }

        void PlayQuickMode(Mode_t modeToPlay) {

            m_oldMode = m_activeMode;
            SwitchMode(modeToPlay);
        }

    private:
        ModeManager(const ModeManager&) = delete;
        ModeManager& operator=(const ModeManager&) = delete;
        ModeManager(ModeManager&&) = delete;
        ModeManager& operator=(ModeManager&&) = delete;

        Mode** modes;
        Mode_t m_activeMode;
        Mode_t m_oldMode;
};

#endif