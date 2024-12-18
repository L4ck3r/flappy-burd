#include <ESP32Video.h>
#include <WiFi.h>

#include "config.h"
#include "game/game.h"
#include "game/pipe.h"
#include "game/wifi_controls.h"
#include "video/sprites.h"
#include "video/vga.h"
//test
VGA3Bit display;

game_t game;
bird_t bird;

void render_loading_screen() {
  vga_show_loading_screen(&display);
}

void setup() {
  Serial.begin(115200);

  display = vga_init();

  Serial.println("Connecting to WiFi");
  controls_setup(render_loading_screen);
  game_reset(&game, &bird);

  uint64_t loading_screen_start_time = millis();
  while(millis() - loading_screen_start_time < 15000) {
    render_loading_screen();
  }
}

void loop() {
  if (controls_flap_active()) {
    game_flap(&bird);
  }
  game_tick(&game, &bird);
  if (pipes_check_collision(&bird)) {
#ifndef DEBUG
    game_reset(&game, &bird);
#endif
  }

  display.fillRect(0, 0, VGA_WIDTH, VGA_HEIGHT, display.RGB(0, 255, 255));

  if (bird.flap_active) {
    sprite_draw(&display, &sprite_bird_active, round(bird.x), round(bird.y));
  } else {
    sprite_draw(&display, &sprite_bird, round(bird.x), round(bird.y));
  }
  
  pipes_draw(&display);

  display.setCursor(2, 2);
  display.setTextColor(display.RGB(0), display.RGB(255, 255, 255));
#ifdef DEBUG
  display.fillRect(0, PIPE_MIN_DISTANCE, VGA_WIDTH, 1, display.RGB(255, 0, 0));
  display.fillRect(0, VGA_HEIGHT - PIPE_MIN_DISTANCE, VGA_WIDTH, 1,
                   display.RGB(255, 0, 0));
  display.print("Res: ");
  display.print(display.xres);
  display.print("x");
  display.println(display.yres);
  display.print("FPS: ");
  display.println(vga_get_fps());
#endif
  display.print("Score: ");
  char buffer[10];
  itoa(game.score, buffer, 10);
  display.println(buffer);

  vga_show(&display);
}
