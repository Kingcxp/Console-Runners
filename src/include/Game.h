#ifndef GAME_H
#define GAME_H


#include "Globals.h"

typedef struct Game {
    // Methods

    void (*loop)(struct Game *);

    // Variables

    Globals *mGlobals;
    bool mIsLooping;
} Game;

#endif // GAME_H