#ifndef GAME
#define GAME


#include "Globals.h"
#include "ScoreBoard.c"
#include "basics/Renderer.c"
#include "basics/State.c"
#include "basics/StateStack.c"
#include "elements/Runner.c"
#include "elements/Obstacle.c"
#include "elements/PickUp.c"
#include "states/GameState.c"
#include "states/PauseState.c"
#include "states/MenuState.c"
#include "states/ReviveState.c"
#include "states/StoreState.c"
#include "states/InfoState.c"
#include "GUI/ButtonGroup.c"
#include "GUI/ProgressBar.c"

typedef struct Game {
    // Methods

    void        (*loop)(struct Game *this);

    // Variables

    Globals     globals;
    StateStack  *stack;
} Game;

Game *createGame();
void destroyGame(Game *game);

#endif // GAME