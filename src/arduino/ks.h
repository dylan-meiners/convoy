#ifndef KS_H
#define KS_H

const int K_PIN_STRIP_FRONT         = 7;
const int K_PIN_STRIP_RIGHT         = 3;
const int K_PIN_STRIP_LEFT          = 4;
const int K_PIN_STRIP_BACK          = 5;

const int K_NUM_LEDS_STRIP_FRONT    = 300;
const int K_NUM_LEDS_STRIP_RIGHT    = 90;
const int K_NUM_LEDS_STRIP_LEFT     = 90;
const int K_NUM_LEDS_STRIP_BACK     = 45;

const uint8_t K_COLOR_HSV_H_GREEN   = 85;
const uint8_t K_COLOR_HSV_S_GREEN   = 255;
const uint8_t K_COLOR_HSV_V_GREEN   = 255;

const double K_MODE_RAINBOW_WAVE_SPEED_SCALAR   = 1.0;

const double K_MODE_FLOW_PERCENT_PER_SECOND     = 1.0 / 3.0;
const int K_MODE_FLOW_LENGTH                    = 3;
const uint8_t K_MODE_FLOW_COLOR_HSV_H           = 128;
const uint8_t K_MODE_FLOW_COLOR_HSV_S           = 255;
const uint8_t K_MODE_FLOW_COLOR_HSV_V           = 255;

#endif