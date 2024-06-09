// game.h
#ifndef GAME_H
#define GAME_H

#include <riv.h> // MUST BE THE FIRST LINE

#define NUM_ENEMIES 50
#define MAX_QUESTIONS 15
#define MAX_ANSWER_LENGTH 50
#define NUM_ANSWERS 4
#define TILE_SIZE 70
#define GAME_SPRITESHEET 1

struct TriviaAnswer {
    char text[100];
};

struct TriviaQuestion {
    char question[100];
    struct TriviaAnswer answers[4];
    int correct_answer_index;
};

struct TriviaGame {
    struct TriviaQuestion questions[MAX_QUESTIONS];
    int current_question_index;
    int num_questions;
    int trivia_step;
    int selected;
    int points;
    int timeout;
};

struct Enemy {
    int x;
    int y;
    int w;
};

struct Game {
    struct Enemy e[NUM_ENEMIES];
    int enemy_count;
    int x;
    int y;
    int fire_x;
    int fire_width;
    int fire_back;
    int points;
    int next_level;
    int cool_down_time;
    int big_cool_down;
    int cool_down;
    float x_momentum;
    float x_push;
    float x_drag;
    int hp;
    int trivia;
    struct TriviaGame trivia_game;
};

extern riv_waveform_desc shoot_sfx;
extern riv_waveform_desc big_shoot_sfx;
extern riv_waveform_desc explosion_sfx;

void initialize_trivia(struct TriviaGame *game);
int check_answer(struct TriviaGame *game);
void display_question(struct TriviaGame *game);
void display_result(struct Game *game);
void run_trivia(struct Game *game);
void run_game(struct Game *game);
void push_back_enemies(struct Game *game);

#endif // GAME_H
