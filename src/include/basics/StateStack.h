#ifndef STATESTACK_H
#define STATESTACK_H


#include "Renderer.h"
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

    void        (*handleEvent)(StateStack *, const int);
    void        (*update)(StateStack *, float);
    void        (*render)(const StateStack *, const Renderer *);

    void        (*pushState)(StateStack *, StateID);
    void        (*popState)(StateStack *);
    void        (*clearStates)(StateStack *);

    bool        (*isEmpty)(const StateStack *);

    void        (*applyPendingTasks)(StateStack *);

    // Variables

    int         stackTop,
                pendingFront,
                pendingBack;

    State       *stack[STACK_MAX_LENGTH];

    PendingTask pendingList[PENDING_MAX_LENGTH];
} StateStack;

#endif // STATESTACK_H