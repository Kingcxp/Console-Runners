#ifndef OBSTACLE_HOLLOWLOWBARRIER
#define OBSTACLE_HOLLOWLOWBARRIER


#include "../../elements/Obstacle.h"

const wchar_t HLB_frame[3][6] = {
    L"╔═══╗",
    L"║   ║",
    L"╩   ╩",
};

const Color HLB_colors[3][5] = {
    {Color_Red, Color_Red, Color_Red, Color_Red, Color_Red},
    {Color_Red, Color_Escape, Color_Escape, Color_Escape, Color_Red},
    {Color_Red, Color_Escape, Color_Escape, Color_Escape, Color_Red},
};

const char HLB_collisionBox[3][6] = {
    "xxxxx",
    "x   x",
    "x   x",
};

const short HLB_height = 3;
const bool HLB_passable = true;

#endif // OBSTACLE_HOLLOWLOWBARRIER
