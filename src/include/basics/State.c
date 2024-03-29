#include "State.h"
#include "StateStack.h"

State *createState(Globals *globals, StateStack *stack, StateID id) {
    State *state = NULL;
    switch (id) {
        case GameState:
            state = createGameState(globals, stack);
            break;
        case PauseState:
            state = createPauseState(globals, stack);
            break;
        case MenuState:
            state = createMenuState(globals, stack);
            break;
        case ReviveState:
            state = createReviveState(globals, stack);
            break;
        case StoreState:
            state = createStoreState(globals, stack);
            break;
        case InfoState:
            state = createInfoState(globals, stack);
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
        case PauseState:
            destroyPauseState(state);
            break;
        case MenuState:
            destroyMenuState(state);
            break;
        case ReviveState:
            destroyReviveState(state);
            break;
        case StoreState:
            destroyStoreState(state);
            break;
        case InfoState:
            destroyInfoState(state);
            break;
        default:
            break;
    }
}
