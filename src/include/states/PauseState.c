#ifndef PAUSESTATE
#define PAUSESTATE

#include "../basics/State.h"
#include "../basics/StateStack.h"
#include "../GUI/ButtonGroup.h"


bool PauseState_handleEvent(State *this, const int key) {
    ((ButtonGroup *)this->slots[0])->handleEvent(this->slots[0], key);

    return false;
}

bool PauseState_update(State *this, float deltaTime) {
    return false;
}

void PauseState_render(const State *this, const Renderer *renderer) {
    Vector2i position;
    Color color = Color_GreenBlink;
    position.x = GAME_OFFSETX, position.y = GAME_OFFSETY;
    
    // Render title
    position.y += 3;
    for (int i = 1; i <= 3; ++i) {
        renderer->renderStringAt(renderer, this->slots[i], &color, &position, true);
        position.y += 1;
    }

    // Render border and inner space
    position.y += 1;
    position.x += 2;
    color = Color_LightBlue;
    renderer->renderStringAt(renderer, L"╔════════════╗", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║            ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║            ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║            ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║            ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║            ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"╚════════════╝", &color, &position, true);

    // Render buttons
    ((ButtonGroup *)this->slots[0])->render(this->slots[0], renderer);
}

void PauseState_Button_continue(State *state) {
    state->stack->popState(state->stack);
}

void PauseState_Button_menu(State *state) {
    state->stack->popState(state->stack);
    state->stack->popState(state->stack);
}

State *createPauseState(Globals *globals, StateStack *stack) {
    State *state = (State *)malloc(sizeof(State));

    state->globals = globals;
    state->stack = stack;
    state->handleEvent = PauseState_handleEvent;
    state->update = PauseState_update;
    state->render = PauseState_render;
    state->isLowerVisible = true;

    state->slots[0] = createButtonGroup(state, L'>', Color_Escape, Color_Escape, 72, 80, 13);
    ButtonGroup *buttons = state->slots[0];
    buttons->pushButton(buttons, L"Continue", PauseState_Button_continue);
    buttons->pushButton(buttons, L"  Menu  ", PauseState_Button_menu);
    buttons->position.x = GAME_OFFSETX + 4;
    buttons->position.y = GAME_OFFSETY + 9;
    
    state->slots[1] = L"┳━┓┳━┓┳ ┓┓━┓┳━┓┳━┓┓";
    state->slots[2] = L"┃━┛┃━┫┃ ┃┗━┓┣━ ┃ ┃┃";
    state->slots[3] = L"┇  ┛ ┇┇━┛━━┛┻━┛┇━┛o";

    return state;
}

void destroyPauseState(State *state) {
    destroyButtonGroup(state->slots[0]);

    free(state);
}

#endif // PAUSESTATE