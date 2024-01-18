#include "../resources/obstacles/ObstacleList.h"

void Obstacle_handleEvent(Obstacle *this, const int key) {}

void Obstacle_update(Obstacle *this, float deltaTime, float speed) {
    this->position.y += speed * deltaTime;
}

void Obstacle_render(const Obstacle *this, const Renderer *renderer) {
    Vector2i position;
    position.x = floor(this->position.x) - 2, position.y = floor(this->position.y) - this->height + 1;
    for (int i = 0; i < this->height; ++i) {
        renderer->renderStringAt(renderer, this->frame[i], this->colors[i], &position);
        ++position.y;
    }
}

const Rect Obstacle_getCollisionRect(const Obstacle *this) {
    Rect rect;
    rect.x = floor(this->position.x) - 2, rect.y = floor(this->position.y) - this->height + 1;
    rect.w = 5, rect.h = this->height;
    return rect;
}

const char Obstacle_getCollisionChar(const Obstacle *this, const Vector2i position) {
    return this->collisionBox[position.y][position.x];
}

Obstacle *createObstacle(ObstacleType type) {
    Obstacle *obstacle = (Obstacle *)malloc(sizeof(Obstacle));

    obstacle->handleEvent = Obstacle_handleEvent;
    obstacle->update = Obstacle_update;
    obstacle->render = Obstacle_render;
    obstacle->getCollisionRect = Obstacle_getCollisionRect;
    obstacle->getCollisionChar = Obstacle_getCollisionChar;

    setObstacle(obstacle, type);

    return obstacle;
}

void destroyObstacle(Obstacle *obstacle) {
    free(obstacle);
}