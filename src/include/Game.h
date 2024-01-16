#ifndef GAME_H
#define GAME_H


#include "Globals.h"

typedef struct Game {
    // Methods

    void        (*loop)(struct Game *);

    // Variables

    Globals     *globals;
    bool        isLooping;
} Game;

#endif // GAME_H