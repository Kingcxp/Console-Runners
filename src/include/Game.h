#ifndef GAME
#define GAME


#include "Globals.h"
#include "basics/Renderer.c"
#include "basics/State.c"
#include "basics/StateStack.c"
#include "elements/Runner.c"
#include "states/GameState.c"

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