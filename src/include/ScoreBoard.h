#ifndef SCOREBOARD
#define SCOREBOARD


#include <stdbool.h>

typedef struct ScoreBoard {
    // Methods

    // Variables

    int     coins,
            highScore;

    // In-game variables

    // GameState variables

    float   score;
    bool    isInvincible;
    float   invincibleTimer,
            reviveTimer;
    int     lastRevivedTimes,
            revivedTimes;
} ScoreBoard;

ScoreBoard *createScoreBoard();
void destroyScoreBoard(ScoreBoard *scoreBoard);

#endif // SCOREBOARD