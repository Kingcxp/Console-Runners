#ifndef INFOSTATE
#define INFOSTATE

#include "../basics/State.h"
#include "../basics/StateStack.h"
#include "../GUI/ButtonGroup.h"

bool InfoState_handleEvent(State *this, const int key) {
    if (key == QUIT || key == QUIT - 32) {
        this->stack->popState(this->stack);
        return false;
    }
    ((ButtonGroup *)this->slots[0])->handleEvent(this->slots[0], key);
    
    return false;
}

bool InfoState_update(State *this, float deltaTime) {
    return false;
}

void InfoState_render(const State *this, const Renderer *renderer) {
    Vector2i position;
    Color color = Color_Red;
    position.x = 2, position.y = 3;
    renderer->renderStringAt(renderer, L"┏━┓┏━┓┏┓┓┓━┓┏━┓┳  ┳━┓", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"┃  ┃ ┃┃┃┃┗━┓┃ ┃┃  ┣━ ", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"┗━┛┛━┛┇┗┛━━┛┛━┛┇━┛┻━┛", &color, &position, true); position.y += 2;
    color = Color_Blue;
    renderer->renderStringAt(renderer, L"     ┳━┓┳ ┓┏┓┓┏┓┓┳━┓┳━┓┓━┓┓", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"     ┃┳┛┃ ┃┃┃┃┃┃┃┣━ ┃┳┛┗━┓┃", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"     ┇┗┛┇━┛┇┗┛┇┗┛┻━┛┇┗┛━━┛o", &color, &position, true); position.y += 2;

    color = Color_Yellow;
    renderer->renderStringAt(renderer, L"    Game controls:     ", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"       ↑: Jump/Prev    ", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"       ↓: Roll/Next    ", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"       ←: Go Left      ", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"       →: Go Right     ", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"       Enter: Confirm  ", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"       q/Q: Back/Quit  ", &color, &position, true); position.y += 4;
    color = Color_LightBlue;
    position.x = 15 - (wcslen(VERSION) >> 1);
    renderer->renderStringAt(renderer, VERSION, &color, &position, true);

    ((ButtonGroup *)this->slots[0])->render(this->slots[0], renderer);
}

State *createInfoState(Globals *globals, StateStack *stack) {
    State *state = (State *)malloc(sizeof(State));

    state->globals = globals;
    state->stack = stack;
    state->handleEvent = InfoState_handleEvent;
    state->update = InfoState_update;
    state->render = InfoState_render;
    state->isLowerVisible = false;

    ButtonGroup *buttons = createButtonGroup(state, L'>', Color_Yellow, Color_Green, UP, DOWN, ENTER);
    state->slots[0] = buttons;
    buttons->pushButton(buttons, L"Back", Button_back);
    buttons->position.y = 19;
    buttons->position.x = 11;

    return state;
}

void destroyInfoState(State *state) {
    destroyButtonGroup(state->slots[0]);

    free(state);
}

#endif // INFOSTATE
