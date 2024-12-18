#pragma once
#include "ESP32Video.h"

#define VGA_PIN_RED 17
#define VGA_PIN_GREEN 18
#define VGA_PIN_BLUE 19
#define VGA_PIN_HSYNC 15
#define VGA_PIN_VSYNC 16
#define VGA_MODE VGAMode::MODE320x240
#define VGA_WIDTH 320
#define VGA_HEIGHT 240

#define PIPE_INTERVAL 90
#define PIPE_COUNT ((VGA_WIDTH / PIPE_INTERVAL) + 1)
#define PIPE_MIN_DISTANCE 40
#define PIPE_HEIGHT 60

#define WIFI_CREATE_ACCESS_POINT false
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

// #define DEBUG