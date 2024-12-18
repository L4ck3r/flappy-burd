#include "vga.h"

#include <Ressources/CodePage437_8x14.h>
#include <Ressources/CodePage437_9x16.h>

#include "config.h"

#include <WiFi.h>

uint16_t fps = 0;

VGA3Bit vga_init() {
  VGA3Bit videodisplay;
  videodisplay.setFrameBufferCount(2);
  videodisplay.init(VGA_MODE, VGA_PIN_RED, VGA_PIN_GREEN, VGA_PIN_BLUE,
                    VGA_PIN_HSYNC, VGA_PIN_VSYNC);
  videodisplay.setFont(CodePage437_8x14);
  VGA_MODE.print<HardwareSerial>(Serial);

  return videodisplay;
}

void vga_show(VGA3Bit* display) {
  static uint16_t fps_temp = 0;
  static uint64_t fps_last_reset = 0;

  display->show();

  fps_temp++;
  if (millis() - fps_last_reset > 1000) {
    fps_last_reset = millis();
    fps = fps_temp;
    fps_temp = 0;
  }
}

uint16_t vga_get_fps() { return fps; }

void vga_show_loading_screen(VGA3Bit* display) {
  display->fillRect(0, 0, VGA_WIDTH, VGA_HEIGHT, display->RGB(0));
  display->setCursor(20, 20);
  display->setTextColor(display->RGB(255, 255, 255));
  display->println("Flappy Burd yurrr");

  if (WiFi.status() == WL_CONNECTED) {
    display->print("IP: ");
     display->setTextColor(display->RGB(0, 255, 0));
    display->println(WiFi.localIP().toString().c_str());
  } else {
    display->print("Setting up WiFi...");
  }
  vga_show(display);
}