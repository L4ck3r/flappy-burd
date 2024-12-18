#include "sprites.h"

void sprite_draw(VGA3Bit* display, const sprite_t* sprite, int16_t start_x,
                 int16_t start_y) {
  for (uint16_t x = 0; x < sprite->width; x++) {
    for (uint16_t y = 0; y < sprite->height; y++) {
      uint16_t index = x + y * sprite->width;
      int16_t x_coordinate = x + start_x;
      int16_t y_coordinate = y + start_y;
      if (x_coordinate < 0 || x_coordinate >= display->xres ||
          y_coordinate < 0 || y_coordinate >= display->yres) {
        continue;
      }
      if (sprite->texture_data[index] == 0x0f0f0f) {
        continue;
      }
      display->dot(x_coordinate, y_coordinate,
                   display->RGB(sprite->texture_data[index]));
    }
  }
}