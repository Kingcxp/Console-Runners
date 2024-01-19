#ifndef BUTTON_GROUP
#define BUTTON_GROUP


#include "../basics/StateStack.h"

#define BUTTON_GROUP_SLOTS 8

typedef struct ButtonGroup {
    // Methods

    void            (*handleEvent)(struct ButtonGroup *this, const int key);
    void            (*render)(const struct ButtonGroup *this, const Renderer *renderer);

    // Variables

    wchar_t         indicator;
    short           index;

    const wchar_t   *labels[BUTTON_GROUP_SLOTS];
    void            (*triggers[BUTTON_GROUP_SLOTS])(Globals *globals, StateStack *stack);
} ButtonGroup;

#endif // BUTTON_GROUP