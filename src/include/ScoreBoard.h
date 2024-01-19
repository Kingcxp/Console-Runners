#ifndef SCOREBOARD
#define SCOREBOARD


typedef struct ScoreBoard {
    // Methods

    // Variables

    int     coins,
            highScore;

    // In-game variables

    float   score;
    
    bool    isInvincible;
    float   invincibleTimer;
    int     lastRevivedTimes,
            revivedTimes;
} ScoreBoard;

ScoreBoard *createScoreBoard();
void destroyScoreBoard(ScoreBoard *scoreBoard);

#endif // SCOREBOARD