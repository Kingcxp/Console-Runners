#include "ScoreBoard.h"

ScoreBoard *createScoreBoard() {
    ScoreBoard *scoreBoard = (ScoreBoard *)malloc(sizeof(ScoreBoard));

    return scoreBoard;
}

void destroyScoreBoard(ScoreBoard *scoreBoard) {
    free(scoreBoard);
}