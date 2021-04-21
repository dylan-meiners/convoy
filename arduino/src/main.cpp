#include <Arduino.h>

void ClearSerial();

void setup() {

    //noInterrupts();
    Serial.begin(115200);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {

    if (Serial.available() > 0) {
        Serial.read();

        //ClearSerial();
        Serial.write(77);
        char recv[256] = { 0 };
        int numRecvd = Serial.readBytes(recv, 256);
        if (numRecvd == 256) {

            bool valid = true;
            for (int i = 0; i < 256 && valid; i++) {

                valid = recv[i] == 88;
            }
            if (!valid) {

                digitalWrite(LED_BUILTIN, HIGH);
            }
        }
    }
}

void ClearSerial() {

    while (Serial.available() > 0) { Serial.read(); }
}