#ifndef SCOREBOARD
#define SCOREBOARD


#include <stdbool.h>

static char savePath[1024];

typedef struct ScoreBoard {
    // Methods

    void        (*save)(const struct ScoreBoard *this);
    void        (*load)(struct ScoreBoard *this);

    // Variables

    int         coins,
                highScore,
                runnerIndex;
    
    bool        *runnerUnlocked;

    // In-game variables

    // GameState variables

    float       score;
    bool        isInvincible;
    float       invincibleTimer,
                reviveTimer;
    int         lastRevivedTimes,
                revivedTimes;
} ScoreBoard;

ScoreBoard *createScoreBoard();
void destroyScoreBoard(ScoreBoard *scoreBoard);

#endif // SCOREBOARD
