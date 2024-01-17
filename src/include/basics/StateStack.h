#ifndef STATESTACK
#define STATESTACK


#include "../Globals.h"
#include "State.h"

#define STACK_MAX_LENGTH 8
#define PENDING_MAX_LENGTH 16

typedef enum StackAction {
    StackPush, StackPop, StackClear
} StackAction;

typedef struct PendingTask {
    StackAction action;
    StateID     stateID;
} PendingTask;

typedef struct StateStack {
    // Methods

    void        (*handleEvent)(StateStack *this, const int key);
    void        (*update)(StateStack *this, float deltaTime);
    void        (*render)(const StateStack *this, const Renderer *renderer);

    void        (*pushState)(StateStack *this, StateID id);
    void        (*popState)(StateStack *this);
    void        (*clearStates)(StateStack *this);

    bool        (*isEmpty)(const StateStack *this);

    void        (*applyPendingTasks)(StateStack *this);

    // Variables

    Globals     *globals;

    int         stackTop,
                pendingFront,
                pendingBack;

    State       *stack[STACK_MAX_LENGTH];
    StateID     idStack[STACK_MAX_LENGTH];

    PendingTask pendingList[PENDING_MAX_LENGTH];
} StateStack;

StateStack *createStateStack(Globals *globals);
void destroyStateStack(StateStack *stack);

#endif // STATESTACK