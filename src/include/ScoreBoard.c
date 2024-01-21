#include "ScoreBoard.h"
#include "resources/runners/RunnerList.h"

void ScoreBoard_save(const ScoreBoard *this) {
    FILE *outFile = fopen("save.dat", "r");
    fprintf(outFile, "%d %d %d\n", this->coins, this->highScore, this->runnerIndex);
    for (int i = 0; i < Runner_Count; ++i) {
        if (i == Runner_Count - 1) {
            fprintf("%d\n", this->runnerUnlocked[i]);
        } else {
            fprintf("%d ", this->runnerUnlocked[i]);
        }
    }
    fclose(outFile);
}

void ScoreBoard_load(ScoreBoard *this) {
    FILE *inFile = fopen("save.dat", "r");
    if (!inFile) {
        return;
    }
    fscanf(inFile, "%d%d%d", &this->coins, &this->highScore, &this->runnerIndex);
    for (int i = 0; i < Runner_Count; ++i) {
        fscanf(inFile, "%d", &this->runnerUnlocked[i]);
    }
    fclose(inFile);
}

ScoreBoard *createScoreBoard() {
    ScoreBoard *scoreBoard = (ScoreBoard *)malloc(sizeof(ScoreBoard));

    scoreBoard->save = ScoreBoard_save;
    scoreBoard->load = ScoreBoard_load;
    
    scoreBoard->coins = 0;
    scoreBoard->highScore = 0;
    scoreBoard->runnerIndex = 0;
    scoreBoard->runnerUnlocked = malloc(sizeof(bool) * Runner_Count);
    for (int i = 0; i < Runner_Count; i++) {
        scoreBoard->runnerUnlocked[i] = false;
    }
    scoreBoard->runnerUnlocked[0] = true;
    scoreBoard->load(scoreBoard);
    scoreBoard->save(scoreBoard);

    return scoreBoard;
}

void destroyScoreBoard(ScoreBoard *scoreBoard) {
    free(scoreBoard);
}
