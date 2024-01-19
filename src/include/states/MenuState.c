#ifndef MENUSTATE
#define MENUSTATE


#include "../basics/State.h"
#include "../basics/StateStack.h"
#include "../GUI/ButtonGroup.h"

bool MenuState_handleEvent(State *this, const int key) {
    if (key == 27) {
        this->stack->popState(this->stack);
        return false;
    }
    ((ButtonGroup *)this->slots[6])->handleEvent(this->slots[6], key);

    return false;
}

bool MenuState_update(State *this, float deltaTime) {
    return false;
}

void MenuState_render(const State *this, const Renderer *renderer) {
    // Render title
    Vector2i position;
    Color color = Color_BlueBlink;
    position.x = 2, position.y = 3;
    renderer->renderStringAt(renderer, this->slots[0], &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, this->slots[1], &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, this->slots[2], &color, &position, true); position.y += 2;
    renderer->renderStringAt(renderer, this->slots[3], &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, this->slots[4], &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, this->slots[5], &color, &position, true);

    // Render buttons
    ((ButtonGroup *)this->slots[6])->render(this->slots[6], renderer);
}

void MenuState_Button_start(State *state) {
    state->stack->pushState(state->stack, GameState);
}

void MenuState_Button_store(State *state) {
    // TODO: Add store state.
}

void MenuState_Button_info(State *state) {
    // TODO: Add info state.
}

void MenuStaet_Button_quit(State *state) {
    state->stack->popState(state->stack);
}

State *createMenuState(Globals *globals, StateStack *stack) {
    State *state = (State *)malloc(sizeof(State));

    state->globals = globals;
    state->stack = stack;
    state->isLowerVisible = false;
    state->handleEvent = MenuState_handleEvent;
    state->update = MenuState_update;
    state->render = MenuState_render;

    state->slots[0] = L"┏━┓┏━┓┏┓┓┓━┓┏━┓┳  ┳━┓";
    state->slots[1] = L"┃  ┃ ┃┃┃┃┗━┓┃ ┃┃  ┣━ ";
    state->slots[2] = L"┗━┛┛━┛┇┗┛━━┛┛━┛┇━┛┻━┛";

    state->slots[3] = L"     ┳━┓┳ ┓┏┓┓┏┓┓┳━┓┳━┓┓━┓┓";
    state->slots[4] = L"     ┃┳┛┃ ┃┃┃┃┃┃┃┣━ ┃┳┛┗━┓┃";
    state->slots[5] = L"     ┇┗┛┇━┛┇┗┛┇┗┛┻━┛┇┗┛━━┛o";

    ButtonGroup *buttons = createButtonGroup(state, L'>', Color_Yellow, Color_Green, 72, 80, 13);
    state->slots[6] = buttons;
    buttons->pushButton(buttons, L"Start", MenuState_Button_start);
    buttons->pushButton(buttons, L"Store", MenuState_Button_store);
    buttons->pushButton(buttons, L"Info", MenuState_Button_info);
    buttons->pushButton(buttons, L"Quit", MenuStaet_Button_quit);
    buttons->position.y = 12;
    buttons->position.x = 11;

    return state;
}

void destroyMenuState(State *state) {
    free(state);
}

#endif