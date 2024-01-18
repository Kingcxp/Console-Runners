#ifndef OBSTACLE_LIST
#define OBSTACLE_LIST


#include "../../elements/Obstacle.h"
#include "LowBarrier.h"
#include "HighBarrier.h"
#include "HollowLowBarrier.h"
#include "HollowHighBarrier.h"

typedef enum ObstacleType {
    Obstacle_LowBarrier,
    Obstacle_HollowLowBarrier,
    Obstacle_HighBarrier,
    Obstacle_HollowHighBarrier,
    Obstacle_Count
    // TODO: Register more obstacles.
} ObstacleType;

void setObstacle(Obstacle *obstacle, ObstacleType type) {
    if (type == Obstacle_LowBarrier) {
        obstacle->frame = LB_frame;
        obstacle->colors = LB_colors;
        obstacle->collisionBox = LB_collisionBox;
        obstacle->height = LB_height;
        obstacle->passable = LB_passable;
    } else if (type == Obstacle_HighBarrier) {
        obstacle->frame = HB_frame;
        obstacle->colors = HB_colors;
        obstacle->collisionBox = HB_collisionBox;
        obstacle->height = HB_height;
        obstacle->passable = HB_passable;
    } else if (type == Obstacle_HollowLowBarrier) {
        obstacle->frame = HLB_frame;
        obstacle->colors = HLB_colors;
        obstacle->collisionBox = HLB_collisionBox;
        obstacle->height = HLB_height;
        obstacle->passable = HLB_passable;
    } else if (type == Obstacle_HollowHighBarrier) {
        obstacle->frame = HHB_frame;
        obstacle->colors = HHB_colors;
        obstacle->collisionBox = HHB_collisionBox;
        obstacle->height = HHB_height;
        obstacle->passable = HHB_passable;
    }
}

#endif // OBSTACLE_LIST