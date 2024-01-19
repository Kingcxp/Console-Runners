#ifndef PAUSESTATE
#define PAUSESTATE

#include "../basics/State.h"
#include "../basics/StateStack.h"


bool PauseState_handleEvent(State *this, const int key) {
    return false;
}

bool PauseState_update(State *this, float deltaTime) {
    return false;
}

void PauseState_render(const State *this, const Renderer *renderer) {
    
}

State *createPauseState() {
    State *state = (State *)malloc(sizeof(State));

    state->handleEvent = PauseState_handleEvent;
    state->update = PauseState_update;
    state->render = PauseState_render;
    state->isLowerVisible = true;

    return state;
}

void destroyPauseState(State *state) {
    free(state);
}

#endif // PAUSESTATE