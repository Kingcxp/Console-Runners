#ifndef SCOREBOARD
#define SCOREBOARD


#include <stdbool.h>

typedef struct ScoreBoard {
    // Methods

    void        save(const struct ScoreBoard *this);
    void        load(struct ScoreBoard *this);

    // Variables

    int         coins,
                highScore;

    short       runnerIndex;
    
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
