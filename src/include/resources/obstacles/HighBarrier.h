#ifndef OBSTACLE_HIGHBARRIER
#define OBSTACLE_HIGHBARRIER


#include "../../elements/Obstacle.h"

const wchar_t HB_frame[5][6] = {
    L"╔╦╦╦╗",
    L"╠╬╬╬╣",
    L"╠╬╬╬╣",
    L"╠╬╬╬╣",
    L"╩╩╩╩╩",
};

const Color HB_colors[5][5] = {
    {Color_Red, Color_Red, Color_Red, Color_Red, Color_Red},
    {Color_Red, Color_LightRed, Color_LightRed, Color_LightRed, Color_Red},
    {Color_Red, Color_LightRed, Color_LightRed, Color_LightRed, Color_Red},
    {Color_Red, Color_LightRed, Color_LightRed, Color_LightRed, Color_Red},
    {Color_Red, Color_Red, Color_Red, Color_Red, Color_Red},
};

const char HB_collisionBox[5][6] = {
    "xxxxx",
    "xxxxx",
    "xxxxx",
    "xxxxx",
    "xxxxx",
};

const short HB_height = 5;
const bool HB_passable = false;

#endif // OBSTACLE_HIGHBARRIER
