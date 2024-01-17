#include "StateStack.h"

void StateStack_handleEvent(StateStack *this, const int key) {

}

void StateStack_update(StateStack *this, float deltaTime) {

}

void StateStack_render(const StateStack *this, const Renderer *renderer) {

}

void StateStack_pushState(StateStack *this, StateID id) {
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
                    this->stack[++this->stackTop] = NULL; // TODO: Create new state here.
                }
                break;
            case StackPop:
                if (this->stackTop >= 0) {
                    free(this->stack[this->stackTop--]);
                }
                break;
            case StackClear:
                while (this->stackTop >= 0) {
                    free(this->stack[this->stackTop--]);
                }
                break;
            default:
                break;
        }
        this->pendingFront = (this->pendingFront + 1) % PENDING_MAX_LENGTH;
    }
}