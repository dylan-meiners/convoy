#ifndef TIMER_H
#define TIMER_H

class Timer {

    public:
        Timer() {

            m_running = false;
            m_intervalSet = false;
            m_interval = 0;
            m_iter = 0;
            m_iterInterval = 0;
        }

        void SetInterval(long interval) {

            m_interval = interval;
            m_intervalSet = true;
        }

        void SetIterationInterval(int interval) {

            m_iterInterval = interval;
        }

        void Restart() {

            // if (!m_intervalSet) do something
            m_running = true;
            m_time = millis();
        }

        bool WhenElapsed(long time) {

            return ((millis() - m_time) >= time);
        }

        bool RunInterval() {

            if (!m_running) return false;
            if (!m_intervalSet) return false;

            long now = millis();
            if (now - m_time >= m_interval) {

                // delay(250);
                digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
                m_time = now;
                return true;
            }
            return false;
        }

        bool RunIterationInterval() {

            if (m_iter == m_iterInterval) {

                m_iter = 0;
                return true;
            }
            else {

                m_iter++;
                return false;
            }
        }

    private:
        long m_time;
        bool m_intervalSet;
        long m_interval;
        bool m_running;
        int m_iter;
        int m_iterInterval;
};

#endif