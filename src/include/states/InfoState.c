#ifndef INFOSTATE
#define INFOSTATE

#include "../basics/State.h"
#include "../basics/StateStack.h"

bool InfoState_handleEvent(State *this, const int key) {
    return false;
}

bool InfoState_update(State *this, float deltaTime) {
    return false;
}

void InfoState_render(State *this) {

}

State *createInfoState(Globals *globals, StateStack *stack) {
    State *state = (State *)malloc(sizeof(State));

    state->globals = globals;
    state->stack = stack;
    state->handleEvent = InfoState_handleEvent;
    state->update = InfoState_update;
    state->render = InfoState_render;
    state->isLowerVisible = false;

    return state;
}

void destroyInfoState(State *state) {
    free(state);
}

#endif // INFOSTATE