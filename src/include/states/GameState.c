#ifndef GAMESTATE
#define GAMESTATE


#include "../basics/State.h"
#include "../resources/runners/RunnerList.h"
#include "../resources/obstacles/ObstacleList.h"

#define SAFETY_TIME 2.f

bool GameState_handleEvent(State *this, const int key) {
    Runner *runner = this->slots[3];
    runner->handleEvent(runner, key);

    for (int i = 4; i < STATE_SLOTS; ++i) {
        if (this->slots[i]) {
            ((Obstacle *)this->slots[i])->handleEvent(this->slots[i], key);
        }
    }

    return false;
}

bool GameState_update(State *this, float deltaTime) {
    // Spawn obstacles if needed.
    bool satisfy = false;
    for (int i = 0; i < 3; ++i) {
        *(float *)this->slots[i] += deltaTime;
        if (*(float *)this->slots[i] >= SAFETY_TIME) {
            satisfy = true;
        }
    }
    if (satisfy) {
        int val = random(0, 50000);
        ObstacleType type = random(0, Obstacle_Count - 1);
        if (val <= 1)  {
            Obstacle *obstacle = createObstacle(type);
            for (int i = 0; i < 3; ++i) {
                if (*(float *)this->slots[i] < SAFETY_TIME) {
                    continue;
                }
                *(float *)this->slots[i] = 0.f;
                obstacle->position = (Vector2f) {1.f + (float)ROAD_WIDTH * 0.5f + i * (1.f + ROAD_WIDTH), 0.f};
                for (int j = 4; j < STATE_SLOTS; ++j) {
                    if (!this->slots[j]) {
                        this->slots[j] = obstacle;
                        break;
                    }
                }
                break;
            }
        }
    }

    Runner *runner = this->slots[3];
    runner->update(runner, deltaTime);

    for (int i = 4; i < STATE_SLOTS; ++i) {
        if (this->slots[i]) {
            ((Obstacle *)this->slots[i])->update(this->slots[i], deltaTime, runner->runningSpeed);
            if (((Obstacle *)this->slots[i])->position.y >= ROAD_LENGTH) {
                destroyObstacle(this->slots[i]);
                this->slots[i] = NULL;
            }
        }
    }

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

    // Render Obstacles
    for (int i = 4; i < STATE_SLOTS; ++i) {
        if (this->slots[i]) {
            ((Obstacle *)this->slots[i])->render(this->slots[i], renderer);
        }
    }

    // Render runner
    Runner *runner = this->slots[3];
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
    
    Runner *runner = createRunner(Runner_Basical);
    runner->status = Running;
    runner->position = (Vector2f) {2.f + (float)ROAD_WIDTH * 1.5f, (float)ROAD_LENGTH - 0.5f};
    state->slots[3] = runner;

    for (int i = 0; i < 3; ++i) {
        state->slots[i] = malloc(sizeof(float));
        *(float *)state->slots[i] = SAFETY_TIME;
    }
    // clear slots for obstacles
    for (int i = 4; i < STATE_SLOTS; ++i) {
        state->slots[i] = NULL;
    }

    return state;
}

void destroyGameState(State *state) {
    destroyRunner(state->slots[3]);
    for (int i = 0; i < 3; ++i) {
        free(state->slots[i]);
    }
    for (int i = 4; i < STATE_SLOTS; ++i) {
        if (state->slots[i]) {
            destroyObstacle(state->slots[i]);
        }
    }

    free(state);
}

#endif // GAMESTATE