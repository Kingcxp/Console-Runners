#ifndef GAME
#define GAME


#include "Globals.h"

#define RENDER_WIDTH    19
#define RENDER_HEIGHT   24

typedef struct Game {
    // Methods

    void        (*loop)(Game *this);

    // Variables

    Globals     globals;
    bool        isLooping;
} Game;

Game *createGame();
void destroyGame(Game *game);

#endif // GAME