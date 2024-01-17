#ifndef COLLISIONBOX
#define COLLISIONBOX


#include "Definitions.h"

typedef struct CollisionBox {
    Rect        rect;
    const char  **detail;
} CollisionBox;

bool isCollide(const CollisionBox *lhs, const CollisionBox *rhs) {
    if (!Rect_intersects(&lhs->rect, &rhs->rect)) {
        return false;
    }
    for (int i = 0; i < lhs->rect.y; ++i) {
        for (int j = 0; j < lhs->rect.x; ++j) {
            Vector2i lhsPos = {lhs->rect.x + j, lhs->rect.y + i};
            if (!Rect_contains(&rhs->rect, &lhsPos)) {
                continue;
            }
            Vector2i rhsPos = {lhsPos.x - rhs->rect.x, lhsPos.y - rhs->rect.y};
            if (lhs->detail[lhsPos.y][lhsPos.x] != ' ' && rhs->detail[rhsPos.y][rhsPos.x] != ' ') {
                return true;
            }
        }
    }
    return false;
};

#endif // COLLISIONBOX