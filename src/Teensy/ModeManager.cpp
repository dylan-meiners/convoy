#include "ModeManager.h"

Mode** ModeManager::modes = nullptr;
ModeManager::Mode_t ModeManager::m_activeMode = ModeManager::Mode_t::kDriving;
ModeManager::Mode_t ModeManager::m_oldMode = ModeManager::Mode_t::kDriving;