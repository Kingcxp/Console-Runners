#include "StateStack.h"

void StateStack_handleEvent(StateStack *this, const int key) {
    if (this->isEmpty(this)) {
        return;
    }
    for (int i = this->stackTop; i >= 0; --i) {
        if (!this->stack[i]->handleEvent(this->stack[i], key)) {
            break;
        }
    }
    this->applyPendingTasks(this);
}

void StateStack_update(StateStack *this, float deltaTime) {
    if (this->isEmpty(this)) {
        return;
    }
    for (int i = this->stackTop; i >= 0; --i) {
        if (!this->stack[i]->update(this->stack[i], deltaTime)) {
            break;
        }
    }
    this->applyPendingTasks(this);
}

void StateStack_render(const StateStack *this, const Renderer *renderer) {
    if (this->isEmpty(this)) {
        return;
    }
    int i = this->stackTop;
    while (i > 0 && this->stack[i]->isLowerVisible) {
        --i;
    }
    for (; i <= this->stackTop; ++i) {
        this->stack[i]->render(this->stack[i], renderer);
    }
}

void StateStack_pushState(StateStack *this, StateID id) {
    if (this->stackTop == -1) {
        this->stack[++this->stackTop] = createState(this->globals, this, id);
        this->idStack[this->stackTop] = id;
        return;
    }
    this->pendingBack = (this->pendingBack + 1) % PENDING_MAX_LENGTH;
    this->pendingList[this->pendingBack].action = StackPush;
    this->pendingList[this->pendingBack].stateID = id;
}

void StateStack_popState(StateStack *this) {
    this->pendingBack = (this->pendingBack + 1) % PENDING_MAX_LENGTH;
    this->pendingList[this->pendingBack].action = StackPop;
}

void StateStack_clearStates(StateStack *this) {
    this->pendingBack = (this->pendingBack + 1) % PENDING_MAX_LENGTH;
    this->pendingList[this->pendingBack].action = StackClear;
}

bool StateStack_isEmpty(const StateStack *this) {
    return this->stackTop == -1;
}

void StateStack_applyPendingTasks(StateStack *this) {
    while (this->pendingFront != (this->pendingBack + 1) % PENDING_MAX_LENGTH) {
        switch (this->pendingList[this->pendingFront].action) {
            case StackPush:
                if (this->stackTop + 1 < STACK_MAX_LENGTH) {
                    this->stack[++this->stackTop] = createState(this->globals, this, this->pendingList[this->pendingFront].stateID);
                    this->idStack[this->stackTop] = this->pendingList[this->pendingFront].stateID;
                }
                break;
            case StackPop:
                if (this->stackTop >= 0) {
                    destroyState(this->stack[this->stackTop], this->idStack[this->stackTop]);
                    --this->stackTop;
                }
                break;
            case StackClear:
                while (this->stackTop >= 0) {
                    destroyState(this->stack[this->stackTop], this->idStack[this->stackTop]);
                    --this->stackTop;
                }
                break;
            default:
                break;
        }
        this->pendingFront = (this->pendingFront + 1) % PENDING_MAX_LENGTH;
    }
}

StateStack *createStateStack(Globals *globals) {
    StateStack *stack = (StateStack *)malloc(sizeof(StateStack));

    stack->globals = globals;

    stack->stackTop = -1;
    stack->pendingFront = 0;
    stack->pendingBack = -1;

    stack->handleEvent = StateStack_handleEvent;
    stack->update = StateStack_update;
    stack->render = StateStack_render;
    stack->pushState = StateStack_pushState;
    stack->popState = StateStack_popState;
    stack->clearStates = StateStack_clearStates;
    stack->isEmpty = StateStack_isEmpty;
    stack->applyPendingTasks = StateStack_applyPendingTasks;

    return stack;
}

void destroyStateStack(StateStack *stack) {
    free(stack);
}
