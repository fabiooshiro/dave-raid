// trivia.c
#include "game.h"

#define MAX_QUESTIONS 15
#define MAX_ANSWER_LENGTH 50
#define NUM_ANSWERS 4

void initialize_trivia(struct TriviaGame *game) {
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
        {"Solana"},
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

    struct TriviaAnswer question12Answers[NUM_ANSWERS] = {
        {"Layer 0"},
        {"Sharding"},
        {"Layer 1"},
        {"Layer 2"}};
    game->questions[11] = (struct TriviaQuestion){
        .question = "Cartesi primarily operates\non which layer of the Blockchain?",
        .answers = {question12Answers[0], question12Answers[1], question12Answers[2], question12Answers[3]},
        .correct_answer_index = 3};

    struct TriviaAnswer question13Answers[NUM_ANSWERS] = {
        {"Desktops"},
        {"Embedded systems"},
        {"Mobile devices"},
        {"RISC-V architecture"}};
    game->questions[12] = (struct TriviaQuestion){
        .question = "Cartesi's technology stack\nis based on which architecture?",
        .answers = {question13Answers[0], question13Answers[1], question13Answers[2], question13Answers[3]},
        .correct_answer_index = 3};

    struct TriviaAnswer question14Answers[NUM_ANSWERS] = {
        {"Smart contracts"},
        {"Decentralized applications"},
        {"Rive's games"},
        {"All of the above"}};
    game->questions[13] = (struct TriviaQuestion){
        .question = "What kind of applications can\nbe developed using Cartesi?",
        .answers = {question14Answers[0], question14Answers[1], question14Answers[2], question14Answers[3]},
        .correct_answer_index = 3};

    struct TriviaAnswer question15Answers[NUM_ANSWERS] = {
        {"Blockchain nodes"},
        {"Sidechains"},
        {"Off-chain computation"},
        {"Privacy solutions"}};
    game->questions[14] = (struct TriviaQuestion){
        .question = "What unique feature does Cartesi\nprovide compared to other\nBlockchain platforms?",
        .answers = {question15Answers[0], question15Answers[1], question15Answers[2], question15Answers[3]},
        .correct_answer_index = 2};

    game->selected = 0;
    game->num_questions = MAX_QUESTIONS;
    game->current_question_index = 0;
    game->points = 0;
}

int check_answer(struct TriviaGame *game) {
    int correct_answer_index = game->questions[game->current_question_index].correct_answer_index;
    return (game->selected == correct_answer_index);
}

void display_question(struct TriviaGame *game) {
    riv_clear(RIV_COLOR_BLACK);
    if (riv->frame % 30 == 0)
    {
        game->timeout -= 1;
    }
    if (game->timeout <= 0)
    {
        game->trivia_step = 1;
        game->selected = -1;
        return;
    }
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
        riv_draw_text(riv_tprintf("%d", game->timeout), RIV_SPRITESHEET_FONT_5X7,
                      RIV_CENTER, 7, 7, 1, RIV_COLOR_WHITE);
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

void display_result(struct Game *game) {
    int ok = check_answer(&game->trivia_game);
    if (riv->keys[RIV_GAMEPAD_L2].release)
    {
        game->trivia_game.trivia_step = 2;
        if (ok)
        {
            game->trivia_game.points += 1;
        }
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
    riv_draw_text("press 'a' to continue.",
                  RIV_SPRITESHEET_FONT_5X7,
                  RIV_CENTER, 128, 230, 1, RIV_COLOR_BLUE);
}

void run_trivia(struct Game *game) {
    if (game->trivia_game.trivia_step) {
        display_result(game);
    } else {
        display_question(&game->trivia_game);
    }
}
