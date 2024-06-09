#include "game.h"
#include "trivia.c" // not recomended, but...
#include "game.c"   // not recomended, but...

#define NUM_ENEMIES 50
#define TILE_SIZE 70
#define GAME_SPRITESHEET 1

riv_waveform_desc shoot_sfx = {
    .id = 102,
    .type = RIV_WAVEFORM_PULSE,
    .attack = 0.05f,
    .decay = 0.05f,
    .sustain = 0.15f,
    .release = 0.075f,
    .start_frequency = 880.0f,
    .end_frequency = 220.0f,
    .amplitude = 0.15f,
    .sustain_level = 0.25f,
    .duty_cycle = 0.65f,
    .pan = 0.0f,
};

riv_waveform_desc big_shoot_sfx = {
    .id = 103,
    .type = RIV_WAVEFORM_NOISE,
    .attack = 0.375f,
    .decay = 0.625f,
    .sustain = 0.875f,
    .release = 0.575f,
    .start_frequency = 106.108f,
    .end_frequency = 33.836f,
    .amplitude = 0.300f,
    .sustain_level = 0.675f,
    .duty_cycle = 0.625f,
    .pan = 0.125f,
};

riv_waveform_desc explosion_sfx = {
    .id = 105,
    .type = RIV_WAVEFORM_NOISE,
    .attack = 0.025f,
    .decay = 0.1f,
    .sustain = 0.5f,
    .release = 0.025f,
    .start_frequency = 110.0f,
    .end_frequency = 27.0f,
    .amplitude = 0.25f,
    .sustain_level = 0.5f,
    .duty_cycle = 0.5f,
    .pan = 0.0f,
};

void run_game(struct Game *game)
{
    riv_clear(RIV_COLOR_BLUE);                            // clear screen
    riv_draw_rect_fill(0, 200, 256, 56, RIV_COLOR_PEACH); // draw beach
    if (riv->keys[RIV_GAMEPAD_UP].down)
        game->y--;
    else if (riv->keys[RIV_GAMEPAD_DOWN].down)
        game->y += 2;
    if (riv->keys[RIV_GAMEPAD_LEFT].down)
        game->x_momentum -= game->x_push;
    else if (riv->keys[RIV_GAMEPAD_RIGHT].down)
        game->x_momentum += game->x_push;
    if (riv->keys[RIV_GAMEPAD_L1].down && game->cool_down <= 0)
    {
        game->fire_x = game->x;
        game->fire_width = 1;
        game->fire_back = 0;
        game->cool_down = game->cool_down_time;
        riv_waveform(&shoot_sfx);
    }
    if (game->big_cool_down <= 0 && game->trivia_game.points >= 6)
    {
        riv_draw_text("'d' to Dave",
                      RIV_SPRITESHEET_FONT_5X7,
                      RIV_CENTER, 128, 248, 1, RIV_COLOR_BLUE);
        if (riv->keys[RIV_GAMEPAD_R1].down)
        {
            game->big_cool_down = game->cool_down_time * 10;
            game->fire_x = game->x;
            game->fire_width = 70;
            game->fire_back = 1000;
            riv_waveform(&big_shoot_sfx);
        }
    }
    game->x += (int)game->x_momentum;
    game->x_momentum -= game->x_momentum * game->x_drag;

    riv_draw_rect_fill(game->fire_x + 1 - (int)(game->fire_width / 2), 0, game->fire_width, game->y + game->fire_back, RIV_COLOR_YELLOW); // draw shoot
    int sprite = (riv->frame / 4) % 4;
    riv_draw_sprite(sprite, GAME_SPRITESHEET, game->x - 7, game->y, 1, 1, 1, 1);

    for (int i = 0; i < game->enemy_count; i++)
    {
        game->e[i].y++;
        int half = (int)(game->e[i].w / 2);
        riv_draw_sprite(0, 2, game->e[i].x - half, game->e[i].y, 1, 1, 1, 1);
        // riv_draw_circle_fill(game->e[i].x, game->e[i].y, game->e[i].w, RIV_COLOR_RED);

        if (game->fire_x > 0 &&
            game->e[i].y > -5 &&
            game->e[i].y < game->y + game->fire_back &&
            ((game->e[i].x - (half + 1) < game->fire_x &&
              game->fire_x <= game->e[i].x + half) ||
             (game->fire_x - (int)(game->fire_width / 2) < game->e[i].x + half &&
              game->e[i].x - (half + 1) < game->fire_x + (int)(game->fire_width / 2))))
        {
            riv_waveform(&explosion_sfx);
            game->points += 1;
            game->e[i].x = 28 + riv_rand_uint(200);
            game->e[i].y = -riv_rand_uint(200);
            // Output scores on the output card
            riv->outcard_len = riv_snprintf((char *)riv->outcard, RIV_SIZE_OUTCARD, "JSON{\"score\":%d,\"trivia\":%d}", game->points, game->trivia_game.points);
        }
        if (game->e[i].y > 256)
        {
            if (game->e[i].x > 0)
            {
                game->hp--;
            }
            game->e[i].y = 0;
            game->e[i].x = 28 + riv_rand_uint(200);
        }
    }

    if (game->points > game->next_level)
    {
        game->next_level = (int)(game->points * 1.5) + 3;
        game->e[game->enemy_count].y = -10;
        game->e[game->enemy_count].x = 28 + riv_rand_uint(200);
        game->enemy_count++;
        game->trivia = 1;
    }
    game->fire_x = -1000000;
    if (game->cool_down > 0)
    {
        game->cool_down--;
    }
    if (game->big_cool_down > 0)
    {
        game->big_cool_down--;
    }
    if (game->x > 256)
    {
        game->x = 0;
    }
    if (game->x < 0)
    {
        game->x = 256;
    }
    if (game->hp <= 0)
    {
        riv_draw_text(riv_tprintf("GAME OVER\n\nPoints %d", game->points), RIV_SPRITESHEET_FONT_5X7,
                      RIV_CENTER, 128, 64, 1, RIV_COLOR_WHITE); // draw text
        riv->quit = true;
    }
    else
    {
        riv_draw_text(riv_tprintf("HP %d Points %d\nInt %d", game->hp, game->points, game->trivia_game.points), RIV_SPRITESHEET_FONT_5X7,
                      RIV_CENTER, 128, 64, 1, RIV_COLOR_WHITE); // draw text
    }
    riv_draw_text("left, right, up, down to move.\n's' to fire.",
                  RIV_SPRITESHEET_FONT_5X7,
                  RIV_CENTER, 128, 230, 1, RIV_COLOR_BLUE);
}

void main()
{ // entry point
    riv_make_spritesheet(riv_make_image("ship.png", 0), 16, 16);
    riv_make_spritesheet(riv_make_image("enemy.png", 1), 16, 16);
    struct Game game;
    game.enemy_count = 1;
    game.x = 128, game.y = 170;
    game.fire_x = -10;
    game.fire_width = 1;
    game.fire_back = 0;
    game.points = 0;
    game.next_level = 5;
    game.cool_down_time = 10;
    game.big_cool_down = 0;
    game.cool_down = 0;
    game.x_momentum = 0;
    game.x_push = 0.7;
    game.x_drag = 0.08;
    game.hp = 10;
    game.trivia = 1;
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        game.e[i].x = -10;
        game.e[i].y = 100;
        game.e[i].w = 15;
    }
    initialize_trivia(&game.trivia_game);
    riv->target_fps = 30;
    game.trivia_game.current_question_index = riv_rand_uint(game.trivia_game.num_questions - 1);
    game.trivia_game.timeout = 10;
    do
    { // main loop
        if (game.trivia == 0)
        {
            run_game(&game);
        }
        else
        {
            run_trivia(&game);
            if (game.trivia_game.trivia_step == 2)
            {
                game.trivia = 0;
                game.trivia_game.timeout = 10;
                game.trivia_game.trivia_step = 0;
                game.trivia_game.selected = riv_rand_uint(3);
                game.trivia_game.current_question_index = riv_rand_uint(game.trivia_game.num_questions - 1);
                push_back_enemies(&game);
            }
        }
    } while (riv_present()); // refresh screen and wait next frame
}
