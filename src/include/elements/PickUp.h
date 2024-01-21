#ifndef PICKUP
#define PICKUP


#include "Runner.h"
#include "../Globals.h"

typedef enum PickUpType PickUpType;

typedef struct PickUp {
    // Methods

    void            (*handleEvent)(struct PickUp *this, const int key);
    void            (*update)(struct PickUp *this, float deltaTime, float speed);
    void            (*render)(const struct PickUp *this, const Renderer *renderer);

    void            (*takeEffect)(struct PickUp *this, Runner *runner);

    bool            (*collideRunner)(const struct PickUp *this, const Runner *runner);

    // Variables

    const Globals   *globals;
    const wchar_t   (*frame)[6];
    const Color     (*colors)[5];
    const char      (*collisionBox)[6];
    short           height;
    Vector2f        position;
    int             spawnChance,
                    spawnChanceTotal;
} PickUp;

PickUp *createPickUp(const PickUpType type, const Globals *globals);
void destroyPickUp(PickUp *pickup);

#endif // PICKUP
