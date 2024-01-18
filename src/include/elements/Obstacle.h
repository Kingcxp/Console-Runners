#ifndef OBSTACLE
#define OBSTACLE


#include "../Globals.h"

typedef enum ObstacleType ObstacleType;

typedef struct Obstacle {
    // Methods

    void            (*handleEvent)(struct Obstacle *this, const int key);
    void            (*update)(struct Obstacle *this, float deltaTime, float speed);
    void            (*render)(const struct Obstacle *this, const Renderer *renderer);

    const Rect      (*getCollisionRect)(const struct Obstacle *this);
    const char      (*getCollisionChar)(const struct Obstacle *this, const Vector2i position);

    // Variables

    const wchar_t   (*frame)[6];
    const Color     (*colors)[5];
    const char      (*collisionBox)[6];
    short           height;
    Vector2f        position;

} Obstacle;

Obstacle *createObstacle(ObstacleType type);
void destroyObstacle(Obstacle *obstacle);

#endif // OBSTACLE