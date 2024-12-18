#include "pipe.h"

#include "config.h"

#include "video/sprites.h"

pipe_t pipes[PIPE_COUNT];

uint16_t get_random_y_position() {
  return random(PIPE_MIN_DISTANCE,
                VGA_HEIGHT - PIPE_MIN_DISTANCE - PIPE_HEIGHT);
}

void pipes_create() {
  for (int i = 0; i < PIPE_COUNT; i++) {
    pipes[i].x = PIPE_INTERVAL * i + VGA_WIDTH;
    pipes[i].y = get_random_y_position();
    pipes[i].height = PIPE_HEIGHT;
    pipes[i].sprite_top = &sprite_pipe_top;
    pipes[i].sprite_bottom = &sprite_pipe_bottom;
  }
}

bool pipes_check_collision(bird_t* bird) {
  for (int i = 0; i < PIPE_COUNT; i++) {
    pipe_t pipe = pipes[i];

    if (pipe.x > bird->x + bird->sprite->width) {
      continue;
    }

    if (pipe.x + pipe.sprite_top->width < bird->x) {
      continue;
    }

    if(bird->x + bird->sprite->width < pipe.x ||
        bird->x > pipe.x + pipe.sprite_top->width) {
      continue;
    }

    if (bird->y < pipe.y || bird->y + bird->sprite->height > pipe.y + pipe.height) {
      return true;
    }
  }
  return false;
}

void pipes_move(uint64_t elapsed_millis) {
  for (int i = 0; i < PIPE_COUNT; i++) {
    pipes[i].x -= 2;
    if (pipes[i].x < -pipes[i].sprite_top->width) {
      pipes[i].x += PIPE_INTERVAL * PIPE_COUNT;
      pipes[i].y = get_random_y_position();
    }
  }
}

void pipes_draw(VGA3Bit* display) {
  for (int i = 0; i < PIPE_COUNT; i++) {
    pipe_t pipe = pipes[i];
    sprite_draw(display, pipe.sprite_top, pipe.x,
                pipe.y - pipe.sprite_top->height);
    sprite_draw(display, pipe.sprite_bottom, pipe.x, pipe.y + pipe.height);
  }
}