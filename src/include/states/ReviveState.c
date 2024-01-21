#ifndef REVIVESTATE
#define REVIVESTATE

#include "../basics/State.h"
#include "../basics/StateStack.h"
#include "../GUI/ProgressBar.h"
#include "../GUI/ButtonGroup.h"

#define COST_MULTIPLIER 30
#define REVIVE_COST(state) ((state->globals->scoreBoard->revivedTimes + 1) * COST_MULTIPLIER)

bool ReviveState_handleEvent(State *this, const int key) {
    if (key == QUIT || key == QUIT - 32) {
        this->stack->popState(this->stack);
        this->stack->popState(this->stack);
        return false;
    }
    ((ButtonGroup *)this->slots[2])->handleEvent(this->slots[2], key);
    return false;
}

bool ReviveState_update(State *this, float deltaTime) {
    if (*(float *)this->slots[0] > 0.f) {
        *(float *)this->slots[0] -= deltaTime;
        if (*(float *)this->slots[0] <= 0.f) {
            *(float *)this->slots[0] = 0.f;
            this->stack->popState(this->stack);
            this->stack->popState(this->stack);
        }
    }
    ((ProgressBar *)this->slots[1])->update(this->slots[1], deltaTime);

    return false;
}

void ReviveState_render(const State *this, const Renderer *renderer) {
    Vector2i position;
    Color color = Color_Green;
    position.x = GAME_OFFSETX - 1, position.y = GAME_OFFSETY;
    
    // Render title
    renderer->renderStringAt(renderer, L"                     ", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"┳ ┳┳━┓┳  ┳━┓  ┏┏┓┳━┓┓", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"┃━┫┣━ ┃  ┃━┛  ┃┃┃┣━ ┃", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"┇ ┻┻━┛┇━┛┇    ┛ ┇┻━┛o", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"                     ", &color, &position, true); position.y += 1;

    // Render border and inner space
    position.x += 3;
    color = Color_LightGreen;
    renderer->renderStringAt(renderer, L"╔════════════╗", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║            ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║            ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║            ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║            ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║            ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║            ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║            ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"╚════════════╝", &color, &position, true);

    // Render cost
    position.y = GAME_OFFSETY + 6;
    position.x += 2;
    wchar_t costString[10], costValueString[10];
    color = Color_LightPurple;
    swprintf(costString, 9, L"Cost: ");
    swprintf(costValueString, 9, L"%04d", REVIVE_COST(this));

    renderer->renderStringAt(renderer, costString, &color, &position, true);
    position.x += 6;
    color = Color_Yellow;
    renderer->renderStringAt(renderer, costValueString, &color, &position, true);

    // Render button and countdown
    ((ProgressBar *)this->slots[1])->render(this->slots[1], renderer);
    ((ButtonGroup *)this->slots[2])->render(this->slots[2], renderer);
}

void ReviveState_Button_Confirm(State *state) {
    if (state->globals->scoreBoard->coins < REVIVE_COST(state)) {
        return;
    }
    state->globals->scoreBoard->coins -= REVIVE_COST(state);
    state->globals->scoreBoard->revivedTimes += 1;
    state->globals->scoreBoard->isInvincible = true;
    state->globals->scoreBoard->invincibleTimer = 5.f;
    state->stack->popState(state->stack);
}

State *createReviveState(Globals *globals, StateStack *stack) {
    State *state = (State *)malloc(sizeof(State));

    state->globals = globals;
    state->stack = stack;
    state->handleEvent = ReviveState_handleEvent;
    state->update = ReviveState_update;
    state->render = ReviveState_render;
    state->isLowerVisible = true;

    state->slots[0] = malloc(sizeof(float));
    state->slots[1] = createProgressBar(Color_LightRed, 12, 3, 5.f, 5.f);
    state->slots[2] = createButtonGroup(state, L'>', Color_Green, Color_Yellow, UP, DOWN, ENTER);

    ButtonGroup *buttons = (ButtonGroup *)state->slots[2];
    ProgressBar *bar = (ProgressBar *)state->slots[1];
    buttons->pushButton(buttons, L"Confirm!", ReviveState_Button_Confirm);
    buttons->position.x = GAME_OFFSETX + 4;
    buttons->position.y = GAME_OFFSETY + 8;
    *(float *)state->slots[0] = 5.f;
    bar->follow = state->slots[0];
    bar->position.x = GAME_OFFSETX + 3;
    bar->position.y = GAME_OFFSETY + 10;

    return state;
}

void destroyReviveState(State *state) {
    free(state->slots[0]);
    destroyProgressBar(state->slots[1]);
    destroyButtonGroup(state->slots[2]);
    
    free(state);
}

#endif // REVIVESTATE
