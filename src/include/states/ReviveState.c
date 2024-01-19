#ifndef REVIVESTATE
#define REVIVESTATE

#include "../basics/State.h"
#include "../basics/StateStack.h"
#include "../GUI/ProgressBar.h"

bool ReviveState_handleEvent(State *this, const int key) {
    return false;
}

bool ReviveState_update(State *this, float deltaTime) {
    return false;
}

void ReviveState_render(State *this) {
    
}

State *createReviveState(Globals *globals, StateStack *stack) {
    State *state = (State *)malloc(sizeof(State));

    state->globals = globals;
    state->stack = stack;
    state->handleEvent = ReviveState_handleEvent;
    state->update = ReviveState_update;
    state->render = ReviveState_render;
    state->isLowerVisible = true;

    return state;
}

void destroyReviveState(State *state) {
    free(state);
}

#endif // REVIVESTATE