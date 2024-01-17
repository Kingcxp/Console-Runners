#ifndef STATE
#define STATE


#include "../Globals.h"

typedef struct StateStack StateStack;

typedef enum StateID {
    GameState,
    MenuState,
    PauseState,
    // TODO: Register states here.
} StateID;
State *createGameState(Globals *globals, StateStack *stack);
void destroyGameState(State *state);
State *createMenuState(Globals *globals, StateStack *stack);
void destroyMenuState(State *state);
State *createPauseState(Globals *globals, StateStack *stack);
void destroyPauseState(State *state);

typedef struct State {
    // Methods

    bool            (*handleEvent)(State *this, const int key);
    bool            (*update)(State *this, float deltaTime);
    void            (*render)(const State *this, const Renderer *renderer);

    // Variables

    StateStack      *stack;
    Globals         *globals;
    bool            isLowerVisible;
} State;

State *createState(Globals *globals, StateStack *stack, StateID id);
void destroyState(State *statek, StateID id);

#endif // STATE