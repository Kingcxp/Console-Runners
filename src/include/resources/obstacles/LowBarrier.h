#ifndef OBSTACLE_LOWBARRIER
#define OBSTACLE_LOWBARRIER


#include "../../elements/Obstacle.h"

const wchar_t LB_frame[3][6] = {
    L"╔╦╦╦╗",
    L"╠╬╬╬╣",
    L"╩╩╩╩╩",
};

const Color LB_colors[3][5] = {
    {Color_Red, Color_Red, Color_Red, Color_Red, Color_Red},
    {Color_Red, Color_LightRed, Color_LightRed, Color_LightRed, Color_Red},
    {Color_Red, Color_Red, Color_Red, Color_Red, Color_Red},
};

const char LB_collisionBox[3][6] = {
    "xxxxx",
    "xxxxx",
    "xxxxx",
};

const short LB_height = 3;
const bool LB_passable = true;

#endif // OBSTACLE_LOWBARRIER
