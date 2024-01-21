#include "ButtonGroup.h"

void ButtonGroup_handleEvent(ButtonGroup *this, const int key) {
    if (this->total <= 0) {
        return;
    }
    if (key == this->prevKey) {
        if (this->index > 0) {
            --this->index;
        }
    } else if (key == this->nextKey) {
        if (this->index + 1 < this->total) {
            ++this->index;
        }
    } else if (key == this->triggerKey) {
        this->triggers[this->index](this->state);
    }
}

void ButtonGroup_render(const ButtonGroup *this, const Renderer *renderer) {
    if (this->total <= 0) {
        return;
    }
    Vector2i position = this->position;
    // Render indicator
    position.y += this->index * 2;
    renderer->renderCharAt(renderer, this->indicator, &this->indicatorColor, &position);

    // Render labels
    position.x += 2, position.y = this->position.y;
    for (int i = 0; i < this->total; ++i) {
        renderer->renderStringAt(renderer, this->labels[i], &this->buttonColor, &position, true);
        position.y += 2;
    }
}

void ButtonGroup_pushButton(ButtonGroup *this, const wchar_t *label, void (*trigger)(State *state)) {
    this->labels[this->total] = label;
    this->triggers[this->total++] = trigger;
}

ButtonGroup *createButtonGroup(State *state, const wchar_t indicator, const Color indicatorColor, const Color buttonColor, const int prevKey, const int nextKey, const int triggerKey) {
    ButtonGroup *group = (ButtonGroup *)malloc(sizeof(ButtonGroup));

    group->state = state;
    
    group->handleEvent = ButtonGroup_handleEvent;
    group->render = ButtonGroup_render;
    group->pushButton = ButtonGroup_pushButton;

    group->indicator = indicator;
    group->indicatorColor = indicatorColor;
    group->buttonColor = buttonColor;
    group->index = 0;
    group->total = 0;
    group->position = (Vector2i){0, 0};
    group->prevKey = prevKey;
    group->nextKey = nextKey;
    group->triggerKey = triggerKey;

    return group;
}

void destroyButtonGroup(ButtonGroup *group) {
    free(group);
}
