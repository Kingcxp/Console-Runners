#ifndef PICKUP_SUPERCOIN
#define PICKUP_SUPERCOIN


#include "../../elements/PickUp.h"

const wchar_t SuperCoin_frame[3][6] = {
    L" .-. ",
    L" |$| ",
    L" `-` ",
};

const Color SuperCoin_colors[3][5] = {
    {Color_Escape, Color_Purple, Color_Yellow, Color_Purple, Color_Escape},
    {Color_Escape, Color_Yellow, Color_LightRed, Color_Yellow, Color_Escape},
    {Color_Escape, Color_Purple, Color_Yellow, Color_Purple, Color_Escape},
};

const char SuperCoin_collisionBox[3][6] = {
    " xxx ",
    " xxx ",
    " xxx ",
};

const short SuperCoin_height = 3;

void SuperCoin_takeEffect(PickUp *this, Runner *runner) {
    this->globals->scoreBoard->coins += 100;
    this->globals->scoreBoard->score += 10000.f;
}

#endif // PICKUP_SUPERCOIN
