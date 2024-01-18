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

bool Obstacle_collideRunner(const Obstacle *this, const Runner *runner) {
    Rect runnerRect = runner->getCollisionRect(runner), obstacleRect;
    obstacleRect.x = floor(this->position.x) - 2, obstacleRect.y = floor(this->position.y) - this->height + 1;
    obstacleRect.w = 5, obstacleRect.h = this->height;
    if (!Rect_intersects(&runnerRect, &obstacleRect)) {
        return false;
    }
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            Vector2i charPos = {runnerRect.x + col, runnerRect.y + row};
            char runnerCollision = runner->getCollisionChar(runner, (Vector2i) {col, row});
            if (runnerCollision == ' ' || !Rect_contains(&obstacleRect, &charPos)) {
                continue;
            }
            char obstacleCollision = this->collisionBox[charPos.y - obstacleRect.y][charPos.x - obstacleRect.x];
            if (obstacleCollision != ' ') {
                return true;
            }
        }
    }
    return false;
}

Obstacle *createObstacle(const ObstacleType type) {
    Obstacle *obstacle = (Obstacle *)malloc(sizeof(Obstacle));

    obstacle->handleEvent = Obstacle_handleEvent;
    obstacle->update = Obstacle_update;
    obstacle->render = Obstacle_render;
    obstacle->collideRunner = Obstacle_collideRunner;

    obstacle->position = (Vector2f){0.f, 0.f};

    setObstacle(obstacle, type);

    return obstacle;
}

void destroyObstacle(Obstacle *obstacle) {
    free(obstacle);
}