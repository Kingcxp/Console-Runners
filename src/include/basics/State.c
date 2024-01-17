#include "State.h"
#include "StateStack.h"

State *createState(Globals *globals, StateStack *stack, StateID id) {
    State *state = NULL;
    switch (id) {
        case GameState:
            state = createGameState(globals, stack);
            break;
        default:
            break;
    }
    return state;
}

void destroyState(State *state, StateID id) {
    switch (id) {
        case GameState:
            destroyGameState(state);
            break;
        default:
            break;
    }
}