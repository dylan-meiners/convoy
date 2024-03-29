#ifndef KS_H
#define KS_H

const int K_PIN_LIGHT_BRAKE         = 2;
const int K_PIN_RUNNING_LIGHTS      = 3;
const int K_PIN_LIGHT_BLINKER_LEFT  = 4;
const int K_PIN_LIGHT_BLINKER_RIGHT = 5;
const int K_PIN_LIGHT_REVERSE       = 6;

const int K_PIN_STRIP_FRONT         = 7;
const int K_PIN_STRIP_LEFT          = 8;
const int K_PIN_STRIP_BACK          = 9;
const int K_PIN_STRIP_RIGHT         = 10;

const int K_PIN_BACKRACK_LIGHT      = 11;

const int K_NUM_LEDS_STRIP_FRONT    = 0;
const int K_NUM_LEDS_STRIP_RIGHT    = 146;
const int K_NUM_LEDS_STRIP_LEFT     = 146;
const int K_NUM_LEDS_STRIP_BACK     = 96;

const int K_NUM_STRIP_TYPES         = 5;

const int K_BLINKER_BPM             = 160;
const double K_MS_PER_BLINK         = 60.0 / K_BLINKER_BPM * 1000.0;
const int K_MS_FLASHERS_TIMEOUT     = 100;

constexpr int K_INCOMING_DATA_PIN = 12;
const int GO                        = 26;
constexpr char K_CMD_SWITCH_MODE	= 27;

const uint8_t K_COLOR_HSV_H_OFF     = 0;
const uint8_t K_COLOR_HSV_S_OFF     = 0;
const uint8_t K_COLOR_HSV_V_OFF     = 0;

const uint8_t K_COLOR_HSV_H_WHITE   = 0;
const uint8_t K_COLOR_HSV_S_WHITE   = 0;
const uint8_t K_COLOR_HSV_V_WHITE   = 255;

const uint8_t K_COLOR_HSV_H_GREEN   = 85;
const uint8_t K_COLOR_HSV_S_GREEN   = 255;
const uint8_t K_COLOR_HSV_V_GREEN   = 255;

const uint8_t K_COLOR_HSV_H_RED     = 0;
const uint8_t K_COLOR_HSV_S_RED     = 255;
const uint8_t K_COLOR_HSV_V_RED     = 255;

const uint8_t K_COLOR_HSV_H_AMBER   = 21;
const uint8_t K_COLOR_HSV_S_AMBER   = 255;
const uint8_t K_COLOR_HSV_V_AMBER   = 255;

const int K_MODE_DATA_LENGTH_GREEN_PULSE    = 1;
const int K_MODE_DATA_LENGTH_FLOW           = 5;
const int K_MODE_DATA_LENGTH_RAINBOW_WAVE   = 2;

const double K_MODE_RAINBOW_WAVE_SPEED_SCALAR   = 1.0;

const int K_MODE_FLOW_SPEED_MS          = 25;
const int K_MODE_FLOW_FADE_ITER         = 2;
const int K_MODE_FLOW_LENGTH            = 3;
const uint8_t K_MODE_FLOW_COLOR_HSV_H   = 128;
const uint8_t K_MODE_FLOW_COLOR_HSV_S   = 255;
const uint8_t K_MODE_FLOW_COLOR_HSV_V   = 255;

const int K_MODE_WARNING_BATCH_SIZE         = 12;
const int K_MODE_WARNING_BATCH_SIZE_HALF    = K_MODE_WARNING_BATCH_SIZE / 2;
const int K_MODE_WARNING_STROBE_INTERBAL_MS = 35;

const int K_MODE_DRIVING_BLINKER_HITS   = 3;

#endif