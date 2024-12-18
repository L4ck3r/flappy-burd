#include "game.h"

#include "config.h"
#include "pipe.h"

void game_reset(game_t *game, bird_t *bird) {
  pipes_create();
  bird->x = 50;
  bird->sprite = &sprite_bird;
  bird->y = 0;
  bird->y_speed = 0;
  game->score = 0;
}

void game_flap(bird_t *bird) {
  bird->flap_active = true;
  bird->flap_activated_at = millis();
  bird->y_speed = -5;
}

void game_tick(game_t *game, bird_t *bird) {
  pipes_move(1);

  bird->y_speed += 0.5;
  bird->y_speed = fmin(bird->y_speed, 6);
  bird->y += bird->y_speed;

  bird->y = fmax(bird->y, 0);
  bird->y = fmin(bird->y, VGA_HEIGHT - bird->sprite->height);
  game->score++;
  if (millis() - bird->flap_activated_at > 200) {
    bird->flap_active = false;
  }
}