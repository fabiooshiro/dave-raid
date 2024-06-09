// game.c
// #include <riv.h> // MUST BE THE FIRST LINE
#include "game.h"

// void run_game(struct Game *game) {
//     riv_clear(RIV_COLOR_BLUE);                            // clear screen
//     riv_draw_rect_fill(0, 200, 256, 56, RIV_COLOR_PEACH); // draw beach
//     if (riv->keys[RIV_GAMEPAD_UP].down)
//         game->y--;
//     else if (riv->keys[RIV_GAMEPAD_DOWN].down)
//         game->y += 2;
//     if (riv->keys[RIV_GAMEPAD_LEFT].down)
//         game->x_momentum -= game->x_push;
//     else if (riv->keys[RIV_GAMEPAD_RIGHT].down)
//         game->x_momentum += game->x_push;
//     if (riv->keys[RIV_GAMEPAD_L1].down && game->cool_down <= 0) {
//         game->fire_x = game->x;
//         game->fire_width = 1;
//         game->fire_back = 0;
//         game->cool_down = game->cool_down_time;
//         riv_waveform(&shoot_sfx);
//     }
//     if (game->big_cool_down <= 0 && game->trivia_game.points >= 6) {
//         riv_draw_text("'d' to Dave",
//                       RIV_SPRITESHEET_FONT_5X7,
//                       RIV_CENTER, 128, 248, 1, RIV_COLOR_BLUE);
//         if (riv->keys[RIV_GAMEPAD_R1].down) {
//             game->big_cool_down = game->cool_down_time * 10;
//             game->fire_x = game->x;
//             game->fire_width = 70;
//             game->fire_back = 1000;
//             riv_waveform(&big_shoot_sfx);
//         }
//     }
//     game->x += (int)game->x_momentum;
//     game->x_momentum -= game->x_momentum * game->x_drag;

//     riv_draw_rect_fill(game->fire_x + 1 - (int)(game->fire_width / 2), 0, game->fire_width, game->y + game->fire_back, RIV_COLOR_YELLOW); // draw shoot
//     int sprite = (riv->frame / 4) % 4;
//     riv_draw_sprite(sprite, GAME_SPRITESHEET, game->x - 7, game->y, 1, 1, 1, 1);

//     for (int i = 0; i < game->enemy_count; i++) {
//         game->e[i].x = (int)(200 + (i * 25) - (game->enemy_count * 25 / 2));
//         int wave = (int)((float)game->e[i].x + 16.0 * riv_cos(riv->frame / 30.0));
//         riv_draw_sprite(0, GAME_SPRITESHEET, game->e[i].x, wave, 1, -1, 1, 1);
//         if (game->e[i].x >= game->fire_x + 1 - (int)(game->fire_width / 2) && game->e[i].x <= game->fire_x + 1 + (int)(game->fire_width / 2) && wave < game->y + game->fire_back) {
//             game->e[i].x = -10;
//             game->points++;
//             riv_waveform(&explosion_sfx);
//         }
//     }
//     if (game->points > game->next_level) {
//         game->next_level += game->enemy_count * 5;
//         game->enemy_count++;
//         game->big_cool_down = game->cool_down_time * 10;
//         game->cool_down = game->cool_down_time;
//         game->trivia_game.points += 1;
//         game->trivia = 1;
//     }
//     if (game->x < 0)
//         game->x = 0;
//     if (game->x > 255)
//         game->x = 255;

//     char s[5] = "";
//     sprintf(s, "%d", game->points);
//     riv_draw_text(s, RIV_SPRITESHEET_FONT_5X7, 1, 1, 1, 1, RIV_COLOR_WHITE);
//     sprintf(s, "%d", game->hp);
//     riv_draw_text(s, RIV_SPRITESHEET_FONT_5X7, 10, 1, 1, 1, RIV_COLOR_WHITE);
//     game->cool_down--;
//     game->big_cool_down--;
//     game->fire_back -= 10;
//     if (game->fire_back < 0)
//         game->fire_back = 0;
// }

void push_back_enemies(struct Game *game) {
    for (int i = 0; i < game->enemy_count; i++) {
        game->e[i].x -= 5;
    }
}
