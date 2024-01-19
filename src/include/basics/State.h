#ifndef STATE
#define STATE


#include "../Globals.h"

#define STATE_SLOTS 32

typedef struct StateStack StateStack;

typedef enum StateID {
    GameState,
    PauseState,
    MenuState,
    ReviveState,
    StoreState,
    InfoState,
} StateID;

typedef struct State {
    // Methods

    bool            (*handleEvent)(struct State *this, const int key);
    bool            (*update)(struct State *this, float deltaTime);
    void            (*render)(const struct State *this, const Renderer *renderer);

    // Variables

    StateStack      *stack;
    Globals         *globals;
    bool            isLowerVisible;
    void            *slots[STATE_SLOTS];
} State;

State *createState(Globals *globals, StateStack *stack, StateID id);
void destroyState(State *statek, StateID id);

State *createGameState(Globals *globals, StateStack *stack);
void destroyGameState(State *state);

State *createPauseState(Globals *globals, StateStack *stack);
void destroyPauseState(State *state);

State *createMenuState(Globals *globals, StateStack *stack);
void destroyMenuState(State *state);

State *createReviveState(Globals *globals, StateStack *stack);
void destroyReviveState(State *state);

State *createStoreState(Globals *globals, StateStack *stack);
void destroyStoreState(State *state);

State *createInfoState(Globals *globals, StateStack *stack);
void destroyInfoState(State *state);

#endif // STATE