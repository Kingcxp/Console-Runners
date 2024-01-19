#ifndef STORESTATE
#define STORESTATE

#include "../basics/State.h"
#include "../basics/StateStack.h"

bool StoreState_handleEvent(State *this, const int key) {
    return false;
}

bool StoreState_update(State *this, float deltaTime) {
    return false;
}

void StoreState_render(const State *this, const Renderer *renderer) {

}

State *createStoreState(Globals *globals, StateStack *stack) {
    State *state = (State *)malloc(sizeof(State));

    state->globals = globals;
    state->stack = stack;
    state->handleEvent = StoreState_handleEvent;
    state->update = StoreState_update;
    state->render = StoreState_render;
    state->isLowerVisible = false;

    return state;
}

void destroyStoreState(State *state) {
    free(state);
}

#endif // STORESTATE