#ifndef GAMESTATE
#define GAMESTATE


#include "../basics/State.h"
#include "../resources/runners/RunnerList.h"
#include "../resources/obstacles/ObstacleList.h"
#include "../resources/pickups/PickUpList.h"

#define SAFETY_TIME 1.2f
#define PICKUP_INTERVAL 0.4f
#define GAME_OFFSETX 1
#define GAME_OFFSETY 1

bool GameState_handleEvent(State *this, const int key) {
    Runner *runner = this->slots[6];
    runner->handleEvent(runner, key);

    for (int i = 7; i * 2 < STATE_SLOTS; ++i) {
        if (this->slots[i]) {
            ((Obstacle *)this->slots[i])->handleEvent(this->slots[i], key);
        }
    }
    for (int i = STATE_SLOTS / 2; i < STATE_SLOTS; ++i) {
        if (this->slots[i]) {
            ((PickUp *)this->slots[i])->handleEvent(this->slots[i], key);
        }
    }

    return false;
}

bool GameState_update(State *this, float deltaTime) {
    bool satisfy = false;
    for (int i = 0; i < 3; ++i) {
        *(float *)this->slots[i] += deltaTime;
        if (*(float *)this->slots[i] >= SAFETY_TIME) {
            satisfy = true;
        }
    }
    for (int i = 3; i < 6; ++i) {
        *(float *)this->slots[i] += deltaTime;
    }
    
    // Spawn obstacles if needed.
    int unpassables = 0;
    for (int i = 7; i * 2 < STATE_SLOTS; ++i) {
        if (!this->slots[i]) {
            continue;
        }
        if (!((Obstacle *)this->slots[i])->passable) {
            ++unpassables;
        }
    }
    if (satisfy) {
        for (int i = 0; i < 3; ++i) {
            if (*(float *)this->slots[i] < SAFETY_TIME || random(0, 100000) > 1) {
                continue;
            }
            Obstacle *obstacle = createObstacle(random(0, Obstacle_Count - 1));
            while (unpassables >= 2 && !obstacle->passable) {
                destroyObstacle(obstacle);
                obstacle = createObstacle(random(0, Obstacle_Count - 1));
            }
            *(float *)this->slots[i] = 0.f;
            obstacle->position = (Vector2f) {1.f + (float)ROAD_WIDTH * 0.5f + i * (1.f + ROAD_WIDTH) + GAME_OFFSETX, GAME_OFFSETY};
            for (int j = 7; j * 2 < STATE_SLOTS; ++j) {
                if (!this->slots[j]) {
                    this->slots[j] = obstacle;
                    obstacle = NULL;
                    break;
                }
            }
            if (obstacle) {
                destroyObstacle(obstacle);
            }
        }
    }
    
    // Spawn pickups
    for (int i = 0; i < 3; ++i) {
        if (*(float *)this->slots[i] < SAFETY_TIME / 2 || *(float *)this->slots[i] > SAFETY_TIME / 4 * 3 || *(float *)this->slots[i + 3] < PICKUP_INTERVAL) {
            continue;
        }
        PickUp *pickup = NULL;
        *(float *)this->slots[i + 3] = 0.f;
        for (int j = PickUp_Coin + 1; j < PickUp_Count; ++j) {
            pickup = createPickUp(j, this->globals);
            if (random(0, pickup->spawnChanceTotal) <= pickup->spawnChance) {
                break;
            }
            destroyPickUp(pickup);
            pickup = NULL;
        }
        if (!pickup) {
            pickup = createPickUp(PickUp_Coin, this->globals);
        }
        pickup->position = (Vector2f) {1.f + (float)ROAD_WIDTH * 0.5f + i * (1.f + ROAD_WIDTH) + GAME_OFFSETX, GAME_OFFSETY};
        for (int j = STATE_SLOTS / 2; j < STATE_SLOTS; ++j) {
            if (!this->slots[j]) {
                this->slots[j] = pickup;
                pickup = NULL;
                break;
            }
        }
        if (!pickup) {
            destroyPickUp(pickup);
        }
    }

    Runner *runner = this->slots[6];
    runner->update(runner, deltaTime);

    for (int i = 7; i * 2 < STATE_SLOTS; ++i) {
        if (!this->slots[i]) {
            continue;
        }
        ((Obstacle *)this->slots[i])->update(this->slots[i], deltaTime, runner->runningSpeed);
        if (floor(((Obstacle *)this->slots[i])->position.y) == ROAD_LENGTH + GAME_OFFSETY - 1 && ((Obstacle *)this->slots[i])->collideRunner(this->slots[i], runner)) {
            runner->die(runner);
            continue;
        }
        if (((Obstacle *)this->slots[i])->position.y >= ROAD_LENGTH + GAME_OFFSETY) {
            destroyObstacle(this->slots[i]);
            this->slots[i] = NULL;
        }
    }

    for (int i = STATE_SLOTS / 2; i < STATE_SLOTS; ++i) {
        if (!this->slots[i]) {
            continue;
        }
        ((PickUp *)this->slots[i])->update(this->slots[i], deltaTime, runner->runningSpeed);
        if (floor(((PickUp *)this->slots[i])->position.y) == ROAD_LENGTH + GAME_OFFSETY - 1 && ((PickUp *)this->slots[i])->collideRunner(this->slots[i], runner)) {
            ((PickUp *)this->slots[i])->takeEffect(this->slots[i], runner);
            continue;
        }
        if (((PickUp *)this->slots[i])->position.y >= ROAD_LENGTH + GAME_OFFSETY) {
            destroyPickUp(this->slots[i]);
            this->slots[i] = NULL;
        }
    }

    return false;
}

void GameState_render(const State *this, const Renderer *renderer) {
    // Render road border.
    Vector2i position;
    for (int i = 0; i < ROAD_LENGTH; ++i) {
        Color color = Color_Escape;
        position.y = i + GAME_OFFSETY;
        position.x = GAME_OFFSETX;
        renderer->renderCharAt(renderer, L'|', &color, &position);
        position.x = ROAD_WIDTH + 1 + GAME_OFFSETX;
        renderer->renderCharAt(renderer, L'|', &color, &position);
        position.x = (ROAD_WIDTH + 1) * 2 + GAME_OFFSETX;
        renderer->renderCharAt(renderer, L'|', &color, &position);
        position.x = (ROAD_WIDTH + 1) * 3 + GAME_OFFSETX;
        renderer->renderCharAt(renderer, L'|', &color, &position);
    }

    // Render Obstacles
    for (int i = 7; i * 2 < STATE_SLOTS; ++i) {
        if (this->slots[i]) {
            ((Obstacle *)this->slots[i])->render(this->slots[i], renderer);
        }
    }

    // Render pickups
    for (int i = STATE_SLOTS / 2; i < STATE_SLOTS; ++i) {
        if (this->slots[i]) {
            ((PickUp *)this->slots[i])->render(this->slots[i], renderer);
        }
    }

    // Render runner
    Runner *runner = this->slots[6];
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
    runner->position = (Vector2f) {2.f + (float)ROAD_WIDTH * 1.5f + GAME_OFFSETX, (float)ROAD_LENGTH - 0.5f + GAME_OFFSETY};
    state->slots[6] = runner;

    for (int i = 0; i < 3; ++i) {
        state->slots[i] = malloc(sizeof(float));
        *(float *)state->slots[i] = SAFETY_TIME;
    }
    for (int i = 3; i < 6; ++i) {
        state->slots[i] = malloc(sizeof(float));
        *(float *)state->slots[i] = 0.f;
    }

    // clear slots for obstacles and pickups
    for (int i = 7; i < STATE_SLOTS; ++i) {
        state->slots[i] = NULL;
    }

    return state;
}

void destroyGameState(State *state) {
    destroyRunner(state->slots[6]);
    for (int i = 0; i < 4; ++i) {
        free(state->slots[i]);
    }
    for (int i = 7; i * 2 < STATE_SLOTS; ++i) {
        if (state->slots[i]) {
            destroyObstacle(state->slots[i]);
        }
    }
    for (int i = STATE_SLOTS / 2; i < STATE_SLOTS; ++i) {
        if (state->slots[i]) {
            destroyPickUp(state->slots[i]);
        }
    }

    free(state);
}

#endif // GAMESTATE