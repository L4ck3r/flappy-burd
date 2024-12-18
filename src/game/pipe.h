#pragma once
#include <stdint.h>
#include "video/sprites.h"
#include "game/game.h"

typedef struct {
    float x;
    uint16_t y;
    uint16_t height;
    const sprite_t* sprite_top;
    const sprite_t* sprite_bottom;
} pipe_t;

void pipes_create();
bool pipes_check_collision(bird_t* bird);

void pipes_move(float move_factor);
void pipes_draw(VGA3Bit* display);
