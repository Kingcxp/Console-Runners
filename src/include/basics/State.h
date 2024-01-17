#ifndef STATE_H
#define STATE_H


#include "../Globals.h"

typedef struct StateStack;

typedef enum StateID {
    GameState,
    MenuState,
    PauseState,
} StateID;

typedef struct State {
    // Methods

    void            (*handleEvent)(State *, const int);
    void            (*update)(State *, float);
    void            (*render)(const State *, const Renderer *);

    // Variables

    StateStack      *stack;
    Globals         *globals;
} State;

#endif // STATE_H