#ifndef GAMESTATE
#define GAMESTATE


#include "../basics/State.h"
#include "../elements/Runner.h"

bool GameState_handleEvent(State *this, const int key) {
    Runner *runner = this->slots[0];
    runner->handleEvent(runner, key);

    return false;
}

bool GameState_update(State *this, float deltaTime) {
    Runner *runner = this->slots[0];
    runner->update(runner, deltaTime);

    return false;
}

void GameState_render(const State *this, const Renderer *renderer) {
    // Render road border.
    Vector2i position;
    for (int i = 0; i < ROAD_LENGTH; ++i) {
        Color color = Color_Escape;
        position.y = i;
        position.x = 0;
        renderer->renderCharAt(renderer, L'|', &color, &position);
        position.x = ROAD_WIDTH + 1;
        renderer->renderCharAt(renderer, L'|', &color, &position);
        position.x = (ROAD_WIDTH + 1) * 2;
        renderer->renderCharAt(renderer, L'|', &color, &position);
        position.x = (ROAD_WIDTH + 1) * 3;
        renderer->renderCharAt(renderer, L'|', &color, &position);
    }

    // Render runner
    Runner *runner = this->slots[0];
    runner->render(runner, renderer);
}

State *createGameState(Globals *globals, StateStack *stack) {
    State *state = malloc(sizeof(State));

    state->globals = globals;
    state->stack = stack;
    state->isLowerVisible = false;

    state->handleEvent = GameState_handleEvent;
    state->update = GameState_update;
    state->render = GameState_render;
    
    Runner *runner = createRunner();
    runner->status = Running;
    runner->position = (Vector2f) {2.f + (float)ROAD_WIDTH * 1.5f, (float)ROAD_LENGTH - 0.5f};
    state->slots[0] = runner;

    return state;
}

void destroyGameState(State *state) {
    destroyRunner(state->slots[0]);

    free(state);
}

#endif // GAMESTATE