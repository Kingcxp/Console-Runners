#include "ScoreBoard.h"
#include "resources/runners/RunnerList.h"

ScoreBoard *createScoreBoard() {
    ScoreBoard *scoreBoard = (ScoreBoard *)malloc(sizeof(ScoreBoard));
    
    scoreBoard->coins = 0;
    scoreBoard->highScore = 0;
    scoreBoard->runnerIndex = 0;
    scoreBoard->runnerUnlocked = malloc(sizeof(bool) * Runner_Count);
    for (int i = 0; i < Runner_Count; i++) {
        scoreBoard->runnerUnlocked[i] = false;
    }
    scoreBoard->runnerUnlocked[0] = true;

    return scoreBoard;
}

void destroyScoreBoard(ScoreBoard *scoreBoard) {
    free(scoreBoard);
}
