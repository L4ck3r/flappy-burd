#pragma once

#include <stdint.h>

#include "video/sprites.h"

typedef struct {
  double score;
} game_t;

typedef struct {
  double x;
  double y;
  double y_speed;
  bool flap_active;
  uint64_t flap_activated_at;
  const sprite_t* sprite;
} bird_t;

void game_reset(game_t *game, bird_t *bird);
void game_tick(game_t *game, bird_t *bird, float move_factor);
void game_flap(bird_t *bird, float move_factor);
