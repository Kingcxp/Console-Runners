#ifndef OBSTACLE_HOLLOWHIGHBARRIER
#define OBSTACLE_HOLLOWHIGHBARRIER


#include "../../elements/Obstacle.h"

const wchar_t HHB_frame[5][6] = {
    L"╔╦╦╦╗",
    L"╠╬╬╬╣",
    L"╠╩╩╩╣",
    L"║   ║",
    L"╩   ╩",
};

const Color HHB_colors[5][5] = {
    {Color_Red, Color_Red, Color_Red, Color_Red, Color_Red},
    {Color_Red, Color_LightRed, Color_LightRed, Color_LightRed, Color_Red},
    {Color_Red, Color_Red, Color_Red, Color_Red, Color_Red},
    {Color_Red, Color_Escape, Color_Escape, Color_Escape, Color_Red},
    {Color_Red, Color_Escape, Color_Escape, Color_Escape, Color_Red},
};

const char HHB_collisionBox[5][6] = {
    "xxxxx",
    "xxxxx",
    "xxxxx",
    "x   x",
    "x   x",
};

const short HHB_height = 5;

#endif // OBSTACLE_HOLLOWHIGHBARRIER