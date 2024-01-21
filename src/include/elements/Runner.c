#include "../resources/runners/RunnerList.h"

#define BLINK_INTERVAL 0.2f

void Runner_handleEvent(Runner *this, const int key) {
    if (this->isDead) {
        return;
    }

    // Switching track
    if (key == LEFT && this->targetTrack >= 0) {
        this->targetTrack -= 1;
    } else if (key == RIGHT && this->targetTrack <= 0) {
        this->targetTrack += 1;
    }

    // handle vertical operations
    if (key == UP) {
        if (this->status == Running) {
            // Jump if on ground and not rolling.
            this->jumpVelocity = this->jumpSpeed;
            this->status = Jumping;
            this->frame = randInt(0, this->jumpingFrameCount - 1);
        } else if (this->status == Rolling) {
            // Should jump immediately after rolling.
            this->readyToJump = true;
        }
    } else if (key == DOWN) {
        if (this->status == Running) {
            // Roll if on ground and not jumping.
            this->status = Rolling;
            this->frame = 0;
            this->frameTimer = 0.f;
        } else if (this->status == Jumping) {
            // Should roll immediately after jumping.
            this->readyToRoll = true;
        }
    }
}

void Runner_update(Runner *this, float deltaTime) {
    // Update invincible
    if (this->isInvincible && *this->isInvincible) {
        this->invincibleVisualTimer += deltaTime;
        if (this->invincibleVisualTimer >= BLINK_INTERVAL) {
            this->invincibleVisualTimer -= BLINK_INTERVAL;
            this->visible ^= true;
        }
    } else {
        this->visible = true;
    }

    // Switching track
    float targetX = this->targetTrack * (1.f + ROAD_WIDTH);
    if (this->trackDelta > targetX) {
        this->trackDelta -= this->switchTrackSpeed * deltaTime;
        if (this->trackDelta <= targetX) {
            this->trackDelta = targetX;
        }
    } else if (this->trackDelta < targetX) {
        this->trackDelta += this->switchTrackSpeed * deltaTime;
        if (this->trackDelta >= targetX) {
            this->trackDelta = targetX;
        }
    }

    // Managing states
    if (this->status == Jumping) {
        this->jumpDelta -= this->jumpVelocity * deltaTime;
        this->jumpVelocity -= this->gravity * deltaTime * (this->readyToRoll ? 8.f : 1.f);
        if (this->jumpDelta > 0.f) {
            this->jumpDelta = 0.f;
            this->jumpVelocity = 0.f;
            if (this->readyToRoll) {
                this->readyToRoll = false;
                this->status = Rolling;
            } else {
                this->status = Running;
            }
            this->frame = 0;
            this->frameTimer = 0.f;
        }
    }
    if (this->isDead) {
        return;
    }
    if (this->status == Rolling) {
        this->frameTimer += deltaTime;
        while (this->frameTimer >= this->rollingSeconds[this->frame]) {
            this->frameTimer -= this->rollingSeconds[this->frame];
            this->frame = this->frame + 1;
            if (this->readyToJump) {
                this->readyToJump = false;
                this->jumpVelocity = this->jumpSpeed;
                this->status = Jumping;
                this->frame = randInt(0, this->jumpingFrameCount - 1);
                this->frame = 0;
                this->frameTimer = 0.f;
            }
            if (this->frame >= this->rollingFrameCount) {
                this->status = Running;
                this->frame = 0;
                this->frameTimer = 0.f;
            }
        }
    }
    if (this->status == Running) {
        this->frameTimer += deltaTime;
        while (this->frameTimer >= this->runningSeconds[this->frame]) {
            this->frameTimer -= this->runningSeconds[this->frame];
            this->frame = (this->frame + 1) % this->runningFrameCount;
        }
    }
}

void Runner_render(const Runner *this, const Renderer *renderer) {
    if (!this->visible) {
        return;
    }
    Vector2i position;
    position.x = floor(this->position.x + this->trackDelta) - 1, position.y = floor(this->position.y + this->jumpDelta) - 3;
    for (int i = 0; i < 4; ++i) {
        if (this->isDead) {
            renderer->renderStringAt(renderer, this->deadFrames[this->frame][i], this->deadColors[this->frame][i], &position, false);
            ++position.y;
            continue;
        }
        switch (this->status) {
            case Idle:
                renderer->renderStringAt(renderer, this->runningFrames[0][i], this->runningColors[0][i], &position, false);
                break;
            case Running:
                renderer->renderStringAt(renderer, this->runningFrames[this->frame][i], this->runningColors[this->frame][i], &position, false);
                break;
            case Rolling:
                renderer->renderStringAt(renderer, this->rollingFrames[this->frame][i], this->rollingColors[this->frame][i], &position, false);
                break;
            case Jumping:
                renderer->renderStringAt(renderer, this->jumpingFrames[this->frame][i], this->jumpingColors[this->frame][i], &position, false);
                break;
            default:
                break;
        }
        ++position.y;
    }
}

void Runner_die(Runner *this) {
    this->isDead = true;
    this->frame = randInt(0, this->deadFrameCount - 1);
}

void Runner_revive(Runner *this) {
    this->isDead = false;
    this->frame = 0;
}

const Rect Runner_getCollisionRect(const Runner *this) {
    Rect rect;
    rect.x = floor(this->position.x + this->trackDelta) - 1, rect.y = floor(this->position.y + this->jumpDelta) - 3;
    rect.w = 3, rect.h = 4;
    return rect;
}

const char Runner_getCollisionChar(const Runner *this, const Vector2i position) {
    switch (this->status) {
        case Idle:
            return this->runningCollisionBox[0][position.y][position.x];
            break;
        case Running:
            return this->runningCollisionBox[this->frame][position.y][position.x];
            break;
        case Rolling:
            return this->rollingCollisionBox[this->frame][position.y][position.x];
            break;
        case Jumping:
            return this->jumpingCollisionBox[this->frame][position.y][position.x];
            break;
        default:
            break;
    }
    return ' ';
}

Runner *createRunner(const RunnerType type) {
    Runner *runner = (Runner *)malloc(sizeof(Runner));

    runner->jumpDelta = 0.f;
    runner->jumpVelocity = 0.f;
    runner->status = Idle;
    runner->frame = 0;
    runner->frameTimer = 0.f;
    runner->targetTrack = 0;
    runner->trackDelta = 0.f;
    runner->position = (Vector2f){0.f, 0.f};

    runner->readyToJump = runner->readyToRoll = runner->isDead = false;
    
    runner->handleEvent = Runner_handleEvent;
    runner->update = Runner_update;
    runner->render = Runner_render;
    runner->die = Runner_die;
    runner->revive = Runner_revive;
    runner->getCollisionRect = Runner_getCollisionRect;
    runner->getCollisionChar = Runner_getCollisionChar;
    runner->visible = true;
    runner->invincibleVisualTimer = 0.f;
    runner->isInvincible = NULL;

    setRunner(runner, type);

    return runner;
}

void destroyRunner(Runner *runner) {
    free(runner);
}
