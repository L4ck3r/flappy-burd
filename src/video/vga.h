#pragma once
#include <ESP32Video.h>

VGA3Bit vga_init();
void vga_show(VGA3Bit* display);
uint16_t vga_get_fps();
void vga_show_loading_screen(VGA3Bit* display);