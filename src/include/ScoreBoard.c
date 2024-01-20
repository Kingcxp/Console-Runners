#include "ScoreBoard.h"

ScoreBoard *createScoreBoard() {
    ScoreBoard *scoreBoard = (ScoreBoard *)malloc(sizeof(ScoreBoard));
    
    scoreBoard->coins = scoreBoard->highScore = 1000;

    return scoreBoard;
}

void destroyScoreBoard(ScoreBoard *scoreBoard) {
    free(scoreBoard);
}