#include <riv.h> // MUST BE THE FIRST LINE

#define NUM_ENEMIES 50

struct Enemy {
  int x;
  int y;
};

struct Game {
  struct Enemy e[NUM_ENEMIES];
  int enemy_count;
  int x;
  int y;
  int fire_x;
  int points;
  int next_level;
  int cool_down_time;
  int cool_down;
  float x_momentum;
  float x_push;
  float x_drag;
  int hp;
};

void run_game(struct Game* game) {
// handle inputs
    if (riv->keys[RIV_GAMEPAD_UP].down) game->y--;
    if (riv->keys[RIV_GAMEPAD_DOWN].down) game->y++;
    if (riv->keys[RIV_GAMEPAD_LEFT].down) game->x_momentum -= game->x_push;
    if (riv->keys[RIV_GAMEPAD_RIGHT].down) game->x_momentum += game->x_push;
    if (riv->keys[RIV_GAMEPAD_A2].down && game->cool_down <= 0) {
      game->fire_x = game->x;
      game->cool_down = game->cool_down_time;
    }
    game->x += (int)game->x_momentum;
    game->x_momentum -= game->x_momentum * game->x_drag;

    // draw screen
    riv_clear(RIV_COLOR_BLUE); // clear screen
    riv_draw_rect_fill(0, 200, 256, 56, RIV_COLOR_PEACH); // draw beach
    riv_draw_rect_fill(game->fire_x + 1, 0, 1, game->y, RIV_COLOR_YELLOW); // draw beach
    riv_draw_circle_fill(game->x, game->y, 8, RIV_COLOR_RED); // draw red dot

    for (int i = 0; i < game->enemy_count; i++) {
      game->e[i].y++;
      riv_draw_circle_fill(game->e[i].x, game->e[i].y, 8, RIV_COLOR_RED); // draw red dot
      if (game->fire_x > 0 && game->e[i].y < game->y && game->e[i].x - 5 < game->fire_x && game->fire_x <= game->e[i].x + 4) {
        game->points += 1;
        game->e[i].x = 28 + riv_rand_uint(200);
        game->e[i].y = -100;
      }
      if (game->e[i].y > 256) {
        if (game->e[i].x > 0) {
          game->hp--;
        }
        game->e[i].y = 0;
        game->e[i].x = 28 + riv_rand_uint(200);
      }
    }

    if (game->points > game->next_level) {
      game->next_level = game->points * 1.5;
      game->e[game->enemy_count].y = -10;
      game->e[game->enemy_count].x = 28 + riv_rand_uint(200);
      game->enemy_count++;
    }
    game->fire_x = -10;
    game->cool_down--;
    if (game->hp <= 0) {
      riv_draw_text(riv_tprintf("GAME OVER\n\nPoints %d", game->points), RIV_SPRITESHEET_FONT_5X7,
                    RIV_CENTER, 128, 64, 1, RIV_COLOR_WHITE); // draw text
      riv->quit = true;
    } else {
      riv_draw_text(riv_tprintf("HP %d Points %d", game->hp, game->points), RIV_SPRITESHEET_FONT_5X7,
                    RIV_CENTER, 128, 64, 1, RIV_COLOR_WHITE); // draw text
    }
}

void main() { // entry point
  struct Game game;
  game.enemy_count = 1;
  game.x = 128, game.y = 170; // red dot position
  game.fire_x = -10;
  game.points = 0;
  game.next_level = 5;
  game.cool_down_time = 10;
  game.cool_down = 0;
  game.x_momentum = 0;
  game.x_push = 0.7;
  game.x_drag = 0.08;
  game.hp = 10;
  for (int i = 0; i < NUM_ENEMIES; i++) {
    game.e[i].x = -10;
    game.e[i].y = 100;
  }
  do { // main loop
    run_game(&game);
  } while(riv_present()); // refresh screen and wait next frame
}
