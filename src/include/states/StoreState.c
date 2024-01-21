#ifndef STORESTATE
#define STORESTATE

#include "../basics/State.h"
#include "../basics/StateStack.h"
#include "../GUI/ButtonGroup.h"
#include "../resources/runners/RunnerList.h"

bool StoreState_handleEvent(State *this, const int key) {
    if (key == QUIT || key == QUIT - 32) {
        this->stack->popState(this->stack);
        return false;
    }

    Runner *runner = this->slots[0];
    if (key == UP || key == DOWN) {
        runner->handleEvent(runner, key);    
    }

    ((ButtonGroup *)this->slots[2])->handleEvent(this->slots[2], key);

    RunnerType *index = this->slots[1];
    if (key == LEFT && *index > Runner_Basical) {
        *index -= 1;
        setRunner(runner, *index);
    } else if (key == RIGHT && *index + 1 < Runner_Count) {
        *index += 1;
        setRunner(runner, *index);
    }

    return false;
}

bool StoreState_update(State *this, float deltaTime) {
    RunnerType *index = this->slots[1];

    Runner *runner = this->slots[0];
    runner->update(runner, deltaTime);

    ButtonGroup *buttons = this->slots[2];
    if (this->globals->scoreBoard->runnerUnlocked[*index]) {
        if (this->globals->scoreBoard->runnerIndex != *index) {
            buttons->labels[0] = L"Choose";
            buttons->buttonColor = Color_Green;
            buttons->indicatorColor = Color_Yellow;
        } else {
            buttons->labels[0] = L"Chosen";
            buttons->buttonColor = Color_LightGray;
            buttons->indicatorColor = Color_LightRed;
        }
    } else {
        if (this->globals->scoreBoard->coins >= runnerPrices[*index]) {
            buttons->labels[0] = L"Buy it!";
            buttons->buttonColor = Color_Green;
            buttons->indicatorColor = Color_Yellow;
        } else {
            buttons->labels[0] = L"Dang it";
            buttons->buttonColor = Color_RedUnderline;
            buttons->indicatorColor = Color_LightBlue;
        }
    }

    return false;
}

void StoreState_render(const State *this, const Renderer *renderer) {
    RunnerType *index = this->slots[1];
    Vector2i position;
    Color color;

    // Render border
    position.x = 7;
    position.y = 3;
    color = Color_Escape;
    renderer->renderStringAt(renderer, L"╔═══════════════╗", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║               ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║               ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║               ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║               ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║               ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║               ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"║               ║", &color, &position, true); position.y += 1;
    renderer->renderStringAt(renderer, L"╚═══════════════╝", &color, &position, true); position.y += 1;

    // Render runner
    Runner *runner = this->slots[0];
    runner->render(runner, renderer);

    // Render Name
    position.x = 15 - (wcslen(runnerNames[*index]) >> 1);
    position.y = 2;
    color = Color_Yellow;
    renderer->renderStringAt(renderer, runnerNames[*index], &color, &position, true);

    // Render arrows
    position.x = 4;
    color = Color_LightGreen;
    if (*index > Runner_Basical) {
        renderer->renderCharAt(renderer, L'←', &color, &position);
    }
    if (*index + 1 < Runner_Count) {
        position.x = 26;
        renderer->renderCharAt(renderer, L'→', &color, &position);
    }
    
    // Render Descriptions
    position.y = 13;
    position.x = 15 - (wcslen(runnerDescriptions[*index]) >> 1);
    color = Color_Yellow;
    renderer->renderStringAt(renderer, runnerDescriptions[*index], &color, &position, true);
    
    // Render Comments
    position.y += 2;
    position.x = 15 - (wcslen(runnerComments[*index]) >> 1);
    color = Color_LightBlue;
    renderer->renderStringAt(renderer, runnerComments[*index], &color, &position, true);

    // Render Cost
    color = Color_LightRed;
    wchar_t cost[16];
    swprintf(cost, 15, L"Cost: %04d", runnerPrices[*index]);
    position.y += 2;
    position.x = 15 - (wcslen(cost) >> 1);
    renderer->renderStringAt(renderer, cost, &color, &position, true);

    // Render Buttons
    ((ButtonGroup *)this->slots[2])->render(this->slots[2], renderer);
}

void StoreState_Button_buy(State *state) {
    RunnerType *index = state->slots[1];
    if (state->globals->scoreBoard->runnerUnlocked[*index]) {
        if (state->globals->scoreBoard->runnerIndex != *index) {
            state->globals->scoreBoard->runnerIndex = *index;
        }
    } else if (state->globals->scoreBoard->coins >= runnerPrices[*index]) {
        state->globals->scoreBoard->coins -= runnerPrices[*index];
        state->globals->scoreBoard->runnerUnlocked[*index] = true;
        this->globals->scoreBoard->save(this->globals->scoreBoard);
    }
}

State *createStoreState(Globals *globals, StateStack *stack) {
    State *state = (State *)malloc(sizeof(State));

    state->globals = globals;
    state->stack = stack;
    state->handleEvent = StoreState_handleEvent;
    state->update = StoreState_update;
    state->render = StoreState_render;
    state->isLowerVisible = false;

    Runner *runner = createRunner(Runner_Basical);
    runner->status = Running;
    runner->position = (Vector2f){2.f + (float)ROAD_WIDTH * 1.5f + GAME_OFFSETX, (float)10.5f};
    state->slots[0] = runner;

    state->slots[1] = malloc(sizeof(RunnerType));
    *(RunnerType *)state->slots[1] = Runner_Basical;

    ButtonGroup *buttons = createButtonGroup(state, L'>', Color_Yellow, Color_Green, UP, DOWN, ENTER);
    buttons->pushButton(buttons, L"Buy!", StoreState_Button_buy);
    buttons->position.y = 19;
    buttons->position.x = 10;
    state->slots[2] = buttons;

    return state;
}

void destroyStoreState(State *state) {
    destroyRunner(state->slots[0]);
    free(state->slots[1]);
    destroyButtonGroup(state->slots[2]);

    free(state);
}

#endif // STORESTATE
