#pragma once
#include <stdint.h>
#include "video/sprites.h"
#include "game/game.h"

typedef struct {
    int16_t x;
    uint16_t y;
    uint16_t height;
    const sprite_t* sprite_top;
    const sprite_t* sprite_bottom;
} pipe_t;

void pipes_create();
bool pipes_check_collision(bird_t* bird);

void pipes_move(uint64_t elapsed_millis);
void pipes_draw(VGA3Bit* display);