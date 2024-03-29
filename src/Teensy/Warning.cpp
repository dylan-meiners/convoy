#include "Warning.h"

Warning::Warning() {

    m_side = kRight;
    m_color = kFirst;
    m_timer = new Timer;
    m_timer->SetInterval(333);
    m_strobeTimer = new Timer;
    m_strobeTimer->SetInterval(K_MODE_WARNING_STROBE_INTERBAL_MS);
}

bool Warning::step() {

    bool strobe = m_strobeTimer->RunInterval();

    if (m_timer->RunInterval()) {

        if (m_side == kLeft) {

            m_color = m_color == kFirst ? kSecond : kFirst;
            m_side = kRight;
        }
        else {

            m_side = kLeft;
        }
    }

    for (int i = 0; i < (int)System::GetInstance().GetStrips().size(); i++) {

        Strip* tempStrip = System::GetInstance().GetStrips()[i];
        // This needs to be integer division
        int batches = tempStrip->GetNumLEDs() / K_MODE_WARNING_BATCH_SIZE_HALF;
        for (int j = 0; j < batches; j++) {

            for (int k = 0; k < K_MODE_WARNING_BATCH_SIZE_HALF; k++) {

                tempStrip->leds[j * K_MODE_WARNING_BATCH_SIZE_HALF + k] =
                    strobe ?
                    (
                        // If current batch is on the left
                        j % 2 == 0 || j == 0 ?
                        (
                            // If left is active
                            m_side == kLeft ?
                            (
                                m_color == kFirst ?
                                CHSV(
                                    K_COLOR_HSV_H_WHITE,
                                    K_COLOR_HSV_S_WHITE,
                                    K_COLOR_HSV_V_WHITE
                                )
                                :
                                CHSV(
                                    K_COLOR_HSV_H_AMBER,
                                    K_COLOR_HSV_S_AMBER,
                                    K_COLOR_HSV_V_AMBER
                                )
                                )
                            :
                            CHSV(
                                K_COLOR_HSV_H_OFF,
                                K_COLOR_HSV_S_OFF,
                                K_COLOR_HSV_V_OFF
                            )
                            )
                        :
                (
                    m_side == kRight ?
                    (
                        m_color == kFirst ?
                        CHSV(
                            K_COLOR_HSV_H_WHITE,
                            K_COLOR_HSV_S_WHITE,
                            K_COLOR_HSV_V_WHITE
                        )
                        :
                        CHSV(
                            K_COLOR_HSV_H_AMBER,
                            K_COLOR_HSV_S_AMBER,
                            K_COLOR_HSV_V_AMBER
                        )
                        )
                    :
                    CHSV(
                        K_COLOR_HSV_H_OFF,
                        K_COLOR_HSV_S_OFF,
                        K_COLOR_HSV_V_OFF
                    )
                    )
                    )
                    :
                CHSV(
                    K_COLOR_HSV_H_OFF,
                    K_COLOR_HSV_S_OFF,
                    K_COLOR_HSV_V_OFF
                );
            }
        }
    }

    return false;
}

void Warning::reset() {

    m_side = kRight;
    m_color = kFirst;
    m_timer->Restart();
    m_strobeTimer->Restart();
}