#include "../resources/pickups/PickUpList.h"

void PickUp_handleEvent(PickUp *this, const int key) {}

void PickUp_update(PickUp *this, const float deltaTime, float speed) {
    this->position.y += speed * deltaTime;
}

void PickUp_render(const PickUp *this, const Renderer *renderer) {
    Vector2i position;
    position.x = floor(this->position.x) - 2, position.y = floor(this->position.y) - this->height + 1;
    for (int i = 0; i < this->height; ++i) {
        renderer->renderStringAt(renderer, this->frame[i], this->colors[i], &position);
        ++position.y;
    }
}

bool PickUp_collideRunner(const PickUp *this, const Runner *runner) {
    Rect runnerRect = runner->getCollisionRect(runner), pickupRect;
    pickupRect.x = floor(this->position.x) - 2, pickupRect.y = floor(this->position.y) - this->height + 1;
    pickupRect.w = 5, pickupRect.h = this->height;
    if (!Rect_intersects(&runnerRect, &pickupRect)) {
        return false;
    }
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            Vector2i charPos = {runnerRect.x + col, runnerRect.y + row};
            char runnerCollision = runner->getCollisionChar(runner, (Vector2i) {col, row});
            if (runnerCollision == ' ' || !Rect_contains(&pickupRect, &charPos)) {
                continue;
            }
            char obstacleCollision = this->collisionBox[charPos.y - pickupRect.y][charPos.x - pickupRect.x];
            if (obstacleCollision != ' ') {
                return true;
            }
        }
    }
    return false;
}

PickUp *createPickUp(const PickUpType type, const Globals *globals) {
    PickUp *pickup = (PickUp *)malloc(sizeof(PickUp));

    pickup->globals = globals;
    pickup->position = (Vector2f){0.f, 0.f};

    pickup->handleEvent = PickUp_handleEvent;
    pickup->update = PickUp_update;
    pickup->render = PickUp_render;
    pickup->collideRunner = PickUp_collideRunner;

    setPickUp(pickup, type);

    return pickup;
}

void destroyPickUp(PickUp *pickup) {
    free(pickup);
}