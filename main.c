#include <riv.h> // MUST BE THE FIRST LINE

#define NUM_ENEMIES 50

#define MAX_QUESTIONS 11
#define MAX_ANSWER_LENGTH 50
#define NUM_ANSWERS 4

struct TriviaAnswer
{
    char text[100];
};

struct TriviaQuestion
{
    char question[100];
    struct TriviaAnswer answers[4];
    int correct_answer_index;
};

struct TriviaGame
{
    struct TriviaQuestion questions[MAX_QUESTIONS];
    int current_question_index;
    int num_questions;
    int trivia_step;
    int selected;
    int points;
};

void initialize_trivia(struct TriviaGame *game)
{
    struct TriviaAnswer question1Answers[NUM_ANSWERS] = {
        {"Improved security"},
        {"Faster transactions"},
        {"Reduced costs"},
        {"Decentralization"}};
    game->questions[0] = (struct TriviaQuestion){
        .question = "What is the primary benefit\nof using Blockchain technology\nin a city's infrastructure?",
        .answers = {question1Answers[0], question1Answers[1], question1Answers[2], question1Answers[3]},
        .correct_answer_index = 3};

    struct TriviaAnswer question2Answers[NUM_ANSWERS] = {
        {"Transparency"},
        {"Immutability"},
        {"Efficiency"},
        {"Security"}};
    game->questions[1] = (struct TriviaQuestion){
        .question = "Which of the following is\na key characteristic\nof Blockchain technology?",
        .answers = {question2Answers[0], question2Answers[1], question2Answers[2], question2Answers[3]},
        .correct_answer_index = 1};

    struct TriviaAnswer question3Answers[NUM_ANSWERS] = {
        {"Centralized"},
        {"Hierarchical"},
        {"Peer-to-peer"},
        {"Decentralized"}};
    game->questions[2] = (struct TriviaQuestion){
        .question = "What type of network architecture\ndoes Blockchain technology utilize?",
        .answers = {question3Answers[0], question3Answers[1], question3Answers[2], question3Answers[3]},
        .correct_answer_index = 2};

    struct TriviaAnswer question4Answers[NUM_ANSWERS] = {
        {"Smart contracts"},
        {"Secure shell (SSH)"},
        {"Social media"},
        {"Supply chain management"}};
    game->questions[3] = (struct TriviaQuestion){
        .question = "Which application is NOT typically\nassociated with Blockchain technology?",
        .answers = {question4Answers[0], question4Answers[1], question4Answers[2], question4Answers[3]},
        .correct_answer_index = 1};

    struct TriviaAnswer question5Answers[NUM_ANSWERS] = {
        {"Ethereum"},
        {"Amazon Web Services (AWS)"},
        {"Bitcoin"},
        {"Hyperledger"}};
    game->questions[4] = (struct TriviaQuestion){
        .question = "Which platform is commonly\nused for deploying smart contracts?",
        .answers = {question5Answers[0], question5Answers[1], question5Answers[2], question5Answers[3]},
        .correct_answer_index = 0};

    struct TriviaAnswer question6Answers[NUM_ANSWERS] = {
        {"Bitcoin"},
        {"Litecoin"},
        {"Ethereum"},
        {"Ripple"}};
    game->questions[5] = (struct TriviaQuestion){
        .question = "Which cryptocurrency is known\nfor its focus on speed and low fees?",
        .answers = {question6Answers[0], question6Answers[1], question6Answers[2], question6Answers[3]},
        .correct_answer_index = 1};

    struct TriviaAnswer question7Answers[NUM_ANSWERS] = {
        {"Proof of Work (PoW)"},
        {"Proof of Stake (PoS)"},
        {"Proof of Authority (PoA)"},
        {"Proof of Concept (PoC)"}};
    game->questions[6] = (struct TriviaQuestion){
        .question = "Which consensus mechanism\nis used by Bitcoin?",
        .answers = {question7Answers[0], question7Answers[1], question7Answers[2], question7Answers[3]},
        .correct_answer_index = 0};

    struct TriviaAnswer question8Answers[NUM_ANSWERS] = {
        {"Public key cryptography"},
        {"Symmetric key cryptography"},
        {"Hash functions"},
        {"Digital signatures"}};
    game->questions[7] = (struct TriviaQuestion){
        .question = "Which cryptographic techniques\nare commonly used in Blockchain?",
        .answers = {question8Answers[0], question8Answers[1], question8Answers[2], question8Answers[3]},
        .correct_answer_index = 3};

    struct TriviaAnswer question9Answers[NUM_ANSWERS] = {
        {"Immutable ledger"},
        {"Dynamic database"},
        {"Decentralized ledger"},
        {"Centralized database"}};
    game->questions[8] = (struct TriviaQuestion){
        .question = "Which term describes the main\nfeature of a Blockchain?",
        .answers = {question9Answers[0], question9Answers[1], question9Answers[2], question9Answers[3]},
        .correct_answer_index = 0};

    struct TriviaAnswer question10Answers[NUM_ANSWERS] = {
        {"Permissionless"},
        {"Permissioned"},
        {"Public"},
        {"Private"}};
    game->questions[9] = (struct TriviaQuestion){
        .question = "What type of access control\nis commonly used in public\nBlockchain networks?",
        .answers = {question10Answers[0], question10Answers[1], question10Answers[2], question10Answers[3]},
        .correct_answer_index = 0};

    struct TriviaAnswer question11Answers[NUM_ANSWERS] = {
        {"Proof of Work (PoW)"},
        {"Proof of Stake (PoS)"},
        {"Proof of Authority (PoA)"},
        {"Proof of Concept (PoC)"}};
    game->questions[10] = (struct TriviaQuestion){
        .question = "Which consensus mechanism\nis used by Ethereum?",
        .answers = {question11Answers[0], question11Answers[1], question11Answers[2], question11Answers[3]},
        .correct_answer_index = 1};

    game->selected = 0;
    game->num_questions = MAX_QUESTIONS; // Update the total number of questions
    game->current_question_index = 0;
    game->points = 0;
}

int check_answer(struct TriviaGame *game)
{
    int correct_answer_index = game->questions[game->current_question_index].correct_answer_index;
    return (game->selected == correct_answer_index);
}

void display_question(struct TriviaGame *game)
{
    riv_clear(RIV_COLOR_BLACK);
    if (riv->keys[RIV_GAMEPAD_UP].release)
    {
        game->selected--;
    }
    if (riv->keys[RIV_GAMEPAD_DOWN].release)
    {
        game->selected++;
    }
    if (game->selected < 0)
    {
        game->selected = 3;
    }
    if (game->selected > 3)
    {
        game->selected = 0;
    }
    if (riv->keys[RIV_GAMEPAD_L2].release)
    {
        game->trivia_step = 1;
    }
    else
    {
        riv_draw_text(riv_tprintf("%s", game->questions[game->current_question_index].question), RIV_SPRITESHEET_FONT_5X7,
                      RIV_CENTER, 128, 64, 1, RIV_COLOR_WHITE);
        int i = 0;
        for (; i < 4; i++)
        {
            if (game->selected == i)
            {
                riv_draw_text(riv_tprintf("%d) %s", i + 1, game->questions[game->current_question_index].answers[i].text), RIV_SPRITESHEET_FONT_5X7,
                              RIV_CENTER, 128, 94 + (i * 20), 1, RIV_COLOR_YELLOW);
            }
            else
            {
                riv_draw_text(riv_tprintf("%d) %s", i + 1, game->questions[game->current_question_index].answers[i].text), RIV_SPRITESHEET_FONT_5X7,
                              RIV_CENTER, 128, 94 + (i * 20), 1, RIV_COLOR_WHITE);
            }
        }
        riv_draw_text("up or down to select.\n'a' to answer.",
                      RIV_SPRITESHEET_FONT_5X7,
                      RIV_CENTER, 128, 104 + (i * 20), 1, RIV_COLOR_BLUE);
    }
}

struct Enemy
{
    int x;
    int y;
};

struct Game
{
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
    int trivia;
    struct TriviaGame trivia_game;
};

void display_result(struct Game *game)
{
    // riv_printf("trivia points");
    int ok = check_answer(&game->trivia_game);
    if (riv->keys[RIV_GAMEPAD_L2].release)
    {
        game->trivia_game.trivia_step = 2;
        game->trivia_game.points += 1;
    }
    if (ok)
    {
        riv_draw_text("Congratulations! You were promoted.", RIV_SPRITESHEET_FONT_5X7,
                      RIV_CENTER, 128, 64, 1, RIV_COLOR_WHITE);
    }
    else
    {
        riv_draw_text("You need to study\nin order to get promoted.", RIV_SPRITESHEET_FONT_5X7,
                      RIV_CENTER, 128, 64, 1, RIV_COLOR_WHITE);
    }
}

void run_trivia(struct Game *game)
{
    if (game->trivia_game.trivia_step)
    {
        display_result(game);
    }
    else
    {
        display_question(&game->trivia_game);
    }
}

void run_game(struct Game *game)
{
    if (riv->keys[RIV_GAMEPAD_UP].down)
        game->y--;
    if (riv->keys[RIV_GAMEPAD_DOWN].down)
        game->y++;
    if (riv->keys[RIV_GAMEPAD_LEFT].down)
        game->x_momentum -= game->x_push;
    if (riv->keys[RIV_GAMEPAD_RIGHT].down)
        game->x_momentum += game->x_push;
    if (riv->keys[RIV_GAMEPAD_A2].down && game->cool_down <= 0)
    {
        game->fire_x = game->x;
        game->cool_down = game->cool_down_time;
    }
    game->x += (int)game->x_momentum;
    game->x_momentum -= game->x_momentum * game->x_drag;

    // draw screen
    riv_clear(RIV_COLOR_BLUE);                                             // clear screen
    riv_draw_rect_fill(0, 200, 256, 56, RIV_COLOR_PEACH);                  // draw beach
    riv_draw_rect_fill(game->fire_x + 1, 0, 1, game->y, RIV_COLOR_YELLOW); // draw beach
    riv_draw_circle_fill(game->x, game->y, 8, RIV_COLOR_RED);              // draw red dot

    for (int i = 0; i < game->enemy_count; i++)
    {
        game->e[i].y++;
        riv_draw_circle_fill(game->e[i].x, game->e[i].y, 8, RIV_COLOR_RED); // draw red dot
        if (game->fire_x > 0 && game->e[i].y < game->y && game->e[i].x - 5 < game->fire_x && game->fire_x <= game->e[i].x + 4)
        {
            game->points += 1;
            game->e[i].x = 28 + riv_rand_uint(200);
            game->e[i].y = -100;
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
        game->next_level = (int)(game->points * 1.5);
        game->e[game->enemy_count].y = -10;
        game->e[game->enemy_count].x = 28 + riv_rand_uint(200);
        game->enemy_count++;
        game->trivia = 1;
    }
    game->fire_x = -10;
    game->cool_down--;
    if (game->hp <= 0)
    {
        riv_draw_text(riv_tprintf("GAME OVER\n\nPoints %d", game->points), RIV_SPRITESHEET_FONT_5X7,
                      RIV_CENTER, 128, 64, 1, RIV_COLOR_WHITE); // draw text
        riv->quit = true;
    }
    else
    {
        riv_draw_text(riv_tprintf("HP %d Points %d N %d", game->hp, game->points, game->trivia_game.points), RIV_SPRITESHEET_FONT_5X7,
                      RIV_CENTER, 128, 64, 1, RIV_COLOR_WHITE); // draw text
    }
    riv_draw_text("left, right, up, down to move.\n'x' to fire.",
                  RIV_SPRITESHEET_FONT_5X7,
                  RIV_CENTER, 128, 230, 1, RIV_COLOR_BLUE);
}

void main()
{ // entry point
    riv_printf("Dave Raid");
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
    game.trivia = 1;
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        game.e[i].x = -10;
        game.e[i].y = 100;
    }
    initialize_trivia(&game.trivia_game);
    riv->target_fps = 30;
    game.trivia_game.current_question_index = riv_rand_uint(game.trivia_game.num_questions - 1);
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
                game.trivia_game.trivia_step = 0;
                game.trivia_game.selected = 0;
                game.trivia_game.current_question_index = riv_rand_uint(game.trivia_game.num_questions - 1);
            }
        }
    } while (riv_present()); // refresh screen and wait next frame
}
