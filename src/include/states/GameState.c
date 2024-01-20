#ifndef GAMESTATE
#define GAMESTATE


#include "../basics/State.h"
#include "../basics/StateStack.h"
#include "../resources/runners/RunnerList.h"
#include "../resources/obstacles/ObstacleList.h"
#include "../resources/pickups/PickUpList.h"

#define SAFETY_TIME 1.2f
#define PICKUP_INTERVAL 0.4f
#define SCORE_SPEED 10
#define SPEEDUP 0.005f

bool GameState_handleEvent(State *this, const int key) {
    if (key == QUIT || key == QUIT - 32) {
        this->stack->pushState(this->stack, PauseState);
        return false;
    }

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
    Runner *runner = this->slots[6];
    runner->update(runner, deltaTime);

    // Handle revive
    if (this->globals->scoreBoard->reviveTimer > 0.f && runner->isDead) {
        this->globals->scoreBoard->reviveTimer -= deltaTime;
        if (this->globals->scoreBoard->reviveTimer <= 0.f) {
            this->globals->scoreBoard->reviveTimer = 0.f;
            this->stack->pushState(this->stack, ReviveState);
            return false;
        }
    }

    if (this->globals->scoreBoard->lastRevivedTimes < this->globals->scoreBoard->revivedTimes) {
        this->globals->scoreBoard->lastRevivedTimes = this->globals->scoreBoard->revivedTimes;
        runner->revive(runner);
    }

    // Update score
    this->globals->scoreBoard->score += SCORE_SPEED * runner->runningSpeed * deltaTime;
    this->globals->scoreBoard->highScore = fmax(this->globals->scoreBoard->highScore, (int)floor(this->globals->scoreBoard->score));
    runner->runningSpeed *= (1.f + SPEEDUP * deltaTime);
    if (this->globals->scoreBoard->isInvincible) {
        this->globals->scoreBoard->invincibleTimer -= deltaTime;
        if (this->globals->scoreBoard->invincibleTimer <= 0.f) {
            this->globals->scoreBoard->invincibleTimer = 0.f;
            this->globals->scoreBoard->isInvincible = false;
        }
    }

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
            if (*(float *)this->slots[i] < SAFETY_TIME || randInt(0, 100000) > 1) {
                continue;
            }
            Obstacle *obstacle = createObstacle(randInt(0, Obstacle_Count - 1));
            while (unpassables >= 2 && !obstacle->passable) {
                destroyObstacle(obstacle);
                obstacle = createObstacle(randInt(0, Obstacle_Count - 1));
            }
            *(float *)this->slots[i] = 0.f;
            obstacle->position = (Vector2f){1.f + (float)ROAD_WIDTH * 0.5f + i * (1.f + ROAD_WIDTH) + GAME_OFFSETX, GAME_OFFSETY};
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
            if (randInt(0, pickup->spawnChanceTotal) <= pickup->spawnChance) {
                break;
            }
            destroyPickUp(pickup);
            pickup = NULL;
        }
        if (!pickup) {
            pickup = createPickUp(PickUp_Coin, this->globals);
        }
        pickup->position = (Vector2f){1.f + (float)ROAD_WIDTH * 0.5f + i * (1.f + ROAD_WIDTH) + GAME_OFFSETX, GAME_OFFSETY};
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

    for (int i = 7; i * 2 < STATE_SLOTS; ++i) {
        if (!this->slots[i]) {
            continue;
        }
        ((Obstacle *)this->slots[i])->update(this->slots[i], deltaTime, runner->runningSpeed);
        if (floor(((Obstacle *)this->slots[i])->position.y) == ROAD_LENGTH + GAME_OFFSETY - 1 &&
            ((Obstacle *)this->slots[i])->collideRunner(this->slots[i], runner) &&
            !this->globals->scoreBoard->isInvincible) {
            runner->die(runner);
            this->globals->scoreBoard->reviveTimer = 1.f;
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
            destroyPickUp(this->slots[i]);
            this->slots[i] = NULL;
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
        Color color = Color_LightBlue;
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

    // Render score
    wchar_t hiscoreString[25], scoreString[25], coinString[25];
    swprintf(hiscoreString, 24, L" HiScore: %06d   ", (int)floor(this->globals->scoreBoard->score));
    swprintf(scoreString, 24, L"   Score: %06d   ", (int)floor(this->globals->scoreBoard->score));
    swprintf(coinString, 24, L"   Coins: %06d   ", (int)floor(this->globals->scoreBoard->coins));
    position.x = GAME_OFFSETX;
    position.y = GAME_OFFSETY - 4;
    Color color = Color_LightPurple;
    renderer->renderStringAt(renderer, hiscoreString, &color, &position, true);
    position.y += 1;
    renderer->renderStringAt(renderer, scoreString, &color, &position, true);
    position.y += 1;
    renderer->renderStringAt(renderer, coinString, &color, &position, true);
}

State *createGameState(Globals *globals, StateStack *stack) {
    State *state = malloc(sizeof(State));

    state->globals = globals;
    state->globals->scoreBoard->score = 0;
    state->globals->scoreBoard->isInvincible = false;
    state->globals->scoreBoard->invincibleTimer = 0.f;
    state->globals->scoreBoard->lastRevivedTimes = 0;
    state->globals->scoreBoard->revivedTimes = 0;
    state->stack = stack;
    state->isLowerVisible = false;

    state->handleEvent = GameState_handleEvent;
    state->update = GameState_update;
    state->render = GameState_render;
    
    Runner *runner = createRunner(Runner_Basical);
    runner->status = Running;
    runner->position = (Vector2f){2.f + (float)ROAD_WIDTH * 1.5f + GAME_OFFSETX, (float)ROAD_LENGTH - 0.5f + GAME_OFFSETY};
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