#ifndef MENUSTATE
#define MENUSTATE


#include "../basics/State.h"
#include "../basics/StateStack.h"
#include "../GUI/ButtonGroup.h"

bool MenuState_handleEvent(State *this, const int key) {
    if (key == QUIT || key == QUIT - 32) {
        this->stack->popState(this->stack);
        return false;
    }
    ((ButtonGroup *)this->slots[0])->handleEvent(this->slots[0], key);

    return false;
}

bool MenuState_update(State *this, float deltaTime) {
    return false;
}

void MenuState_render(const State *this, const Renderer *renderer) {
    // Render title
    Vector2i position;
    Color color = Color_Red;
    position.x = 2, position.y = 3;
    renderer->renderStringAt(renderer, L"┏━┓┏━┓┏┓┓┓━┓┏━┓┳  ┳━┓", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"┃  ┃ ┃┃┃┃┗━┓┃ ┃┃  ┣━ ", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"┗━┛┛━┛┇┗┛━━┛┛━┛┇━┛┻━┛", &color, &position, true); position.y += 2;
    color = Color_Blue;
    renderer->renderStringAt(renderer, L"     ┳━┓┳ ┓┏┓┓┏┓┓┳━┓┳━┓┓━┓┓", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"     ┃┳┛┃ ┃┃┃┃┃┃┃┣━ ┃┳┛┗━┓┃", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"     ┇┗┛┇━┛┇┗┛┇┗┛┻━┛┇┗┛━━┛o", &color, &position, true);

    // Render buttons
    ((ButtonGroup *)this->slots[0])->render(this->slots[0], renderer);

    // Render Tips
    position.x = 2, position.y = 21;
    color = Color_LightBlue;
    renderer->renderStringAt(renderer, L"↑/↓: Select, Enter: Confirm", &color, &position, true);
}

void MenuState_Button_start(State *state) {
    state->stack->pushState(state->stack, GameState);
}

void MenuState_Button_store(State *state) {
    state->stack->pushState(state->stack, StoreState);
}

void MenuState_Button_info(State *state) {
    state->stack->pushState(state->stack, InfoState);
}

State *createMenuState(Globals *globals, StateStack *stack) {
    State *state = (State *)malloc(sizeof(State));

    state->globals = globals;
    state->stack = stack;
    state->isLowerVisible = false;
    state->handleEvent = MenuState_handleEvent;
    state->update = MenuState_update;
    state->render = MenuState_render;

    ButtonGroup *buttons = createButtonGroup(state, L'>', Color_Yellow, Color_Green, UP, DOWN, ENTER);
    state->slots[0] = buttons;
    buttons->pushButton(buttons, L"Start", MenuState_Button_start);
    buttons->pushButton(buttons, L"Store", MenuState_Button_store);
    buttons->pushButton(buttons, L"Info", MenuState_Button_info);
    buttons->pushButton(buttons, L"Quit", Button_back);
    buttons->position.y = 12;
    buttons->position.x = 11;

    return state;
}

void destroyMenuState(State *state) {
    destroyButtonGroup(state->slots[0]);

    free(state);
}

#endif
