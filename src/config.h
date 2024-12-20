#pragma once
#include "ESP32Video.h"

#define VGA_PIN_RED 17
#define VGA_PIN_GREEN 18
#define VGA_PIN_BLUE 19
#define VGA_PIN_HSYNC 15 // Orange
#define VGA_PIN_VSYNC 16 // Gelb
#define VGA_MODE VGAMode::MODE320x240
#define VGA_WIDTH 320
#define VGA_HEIGHT 240

#define PIPE_INTERVAL 90
#define PIPE_COUNT ((VGA_WIDTH / PIPE_INTERVAL) + 1)
#define PIPE_MIN_DISTANCE 40
#define PIPE_HEIGHT 60

#define WIFI_CREATE_ACCESS_POINT true
#define WIFI_SSID "FlappyBird"
#define WIFI_PASSWORD "12345678"
#define WIFI_IP IPAddress(192, 168, 1, 1)
#define WIFI_SUBNET IPAddress(255, 255, 255, 0)

#define NORMINAL_FPS 18
// #define DEBUG
