#ifndef SCOREBOARD
#define SCOREBOARD


typedef struct ScoreBoard {
    // Methods

    // Variables

    int     coins;
} ScoreBoard;

ScoreBoard *createScoreBoard();
void destroyScoreBoard(ScoreBoard *scoreBoard);

#endif // SCOREBOARD