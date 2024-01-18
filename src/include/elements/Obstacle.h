#ifndef OBSTACLE
#define OBSTACLE


#include "Runner.h"
#include "../Globals.h"

typedef enum ObstacleType ObstacleType;

typedef struct Obstacle {
    // Methods

    void            (*handleEvent)(struct Obstacle *this, const int key);
    void            (*update)(struct Obstacle *this, float deltaTime, float speed);
    void            (*render)(const struct Obstacle *this, const Renderer *renderer);

    bool            (*collideRunner)(const struct Obstacle *this, const Runner *runner);

    // Variables

    const wchar_t   (*frame)[6];
    const Color     (*colors)[5];
    const char      (*collisionBox)[6];
    short           height;
    bool            passable;
    Vector2f        position;

} Obstacle;

Obstacle *createObstacle(const ObstacleType type);
void destroyObstacle(Obstacle *obstacle);

#endif // OBSTACLE