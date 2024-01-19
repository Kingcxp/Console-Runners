#ifndef BUTTON_GROUP
#define BUTTON_GROUP


#include "../basics/StateStack.h"

#define BUTTON_GROUP_SLOTS 8

typedef struct ButtonGroup {
    // Methods

    void            (*handleEvent)(struct ButtonGroup *this, const int key);
    void            (*render)(const struct ButtonGroup *this, const Renderer *renderer);

    void            (*pushButton)(struct ButtonGroup *this, const wchar_t *label, void (*trigger)(State *state));

    // Variables

    State           *state;

    wchar_t         indicator;
    Color           indicatorColor,
                    buttonColor;

    int             prevKey,
                    nextKey,
                    triggerKey;

    short           index,
                    total;
    Vector2i        position;

    const wchar_t   *labels[BUTTON_GROUP_SLOTS];
    void            (*triggers[BUTTON_GROUP_SLOTS])(State *state);
} ButtonGroup;

ButtonGroup *createButtonGroup(State *state, const wchar_t indicator, const Color indicatorColor, const Color buttonColor, const int prevKey, const int nextKey, const int triggerKey);
void destroyButtonGroup(ButtonGroup *group);

#endif // BUTTON_GROUP