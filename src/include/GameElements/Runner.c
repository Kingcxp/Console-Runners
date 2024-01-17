#include "Runner.h"

void Runner_handleEvent(Runner *this, const int key) {
    // Switching track
    if (key == runnerKeyValue[GoLeft] && this->targetTrack >= 0) {
        this->targetTrack -= 1;
    } else if (key == runnerKeyValue[GoRight] && this->targetTrack <= 0) {
        this->targetTrack += 1;
    }

    // handle vertical operations
    if (key == runnerKeyValue[Jump]) {
        if (this->status == Running) {
            // Jump if on ground and not rolling.
            this->jumpVelocity = this->jumpSpeed;
            this->status = Jumping;
            this->frame = random(0, this->jumpingFrameCount);
        } else if (this->status == Rolling) {
            // Should jump immediately after rolling.
            this->readyToJump = true;
        }
    } else if (key == runnerKeyValue[Roll]) {
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
    // Switching track
    float targetX = this->targetTrack * this->trackDistance;
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
        this->jumpVelocity -= this->gravity * deltaTime;
        if (this->jumpDelta >= 0) {
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
    if (this->status == Rolling) {
        this->frameTimer += deltaTime;
        while (this->frameTimer >= this->rollingSeconds[this->frame]) {
            this->frameTimer -= this->rollingSeconds[this->frame];
            this->frame = this->frame + 1;
            if (this->frame >= this->rollingFrameCount) {
                if (this->readyToJump) {
                    this->readyToJump = false;
                    this->jumpVelocity = this->jumpSpeed;
                    this->status = Jumping;
                    this->frame = random(0, this->jumpingFrameCount);
                } else {
                    this->status = Running;
                }
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
    Rect rect;
    rect.x = floor((this->position.x + this->trackDelta) / distPerChar.x), rect.y = floor((this->position.y + this->jumpDelta) / distPerChar.y);
    rect.w = 3, rect.h = 4;
    switch (this->status) {
        case Idle:
            renderer->renderRectAt(renderer, this->runningFrames[0], this->runningColors[0], &rect, &this->center);
            break;
        case Running:
            renderer->renderRectAt(renderer, this->runningFrames[this->frame], this->runningColors[this->frame], &rect, &this->center);
            break;
        case Rolling:
            renderer->renderRectAt(renderer, this->rollingFrames[this->frame], this->rollingColors[this->frame], &rect, &this->center);
            break;
        case Jumping:
            renderer->renderRectAt(renderer, this->jumpingFrames[this->frame], this->jumpingColors[this->frame], &rect, &this->center);
            break;
        default:
            break;
    }
}

const CollisionBox Runner_getCollisionBox(const Runner *this) {
    CollisionBox box;
    box.rect.x = floor((this->position.x + this->trackDelta) / distPerChar.x), box.rect.y = floor((this->position.y + this->jumpDelta) / distPerChar.y);
    box.rect.w = 3, box.rect.h = 4;
    switch (this->status) {
        case Idle:
            box.detail = this->runningFrames[0];
            break;
        case Running:
            box.detail = this->runningFrames[this->frame];
            break;
        case Rolling:
            box.detail = this->rollingFrames[this->frame];
            break;
        case Jumping:
            box.detail = this->jumpingFrames[this->frame];
            break;
        default:
            break;
    }
    return box;
}

Runner *createRunner() {
    Runner *runner = (Runner *)malloc(sizeof(Runner));

    setRunner(runner, Basical);
    runner->center = (Vector2i){1, 3};
    runner->jumpDelta = 0.f;
    runner->jumpVelocity = 0.f;
    runner->status = Idle;
    runner->frame = 0;
    runner->frameTimer = 0.f;
    runner->targetTrack = 0;
    runner->trackDistance = 6.f;
    runner->trackDelta = 0.f;

    runner->readyToJump = runner->readyToRoll = false;
    
    runner->handleEvent = Runner_handleEvent;
    runner->update = Runner_update;
    runner->render = Runner_render;
    runner->getCollisionBox = Runner_getCollisionBox;

    return runner;
}

void destroyRunner(Runner *runner) {
    free(runner);
}