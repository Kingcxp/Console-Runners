#ifndef PICKUP_COIN
#define PICKUP_COIN


#include "../../elements/PickUp.h"

const wchar_t Coin_frame[3][4] = {
    L".-.",
    L"|$|",
    L"`-` ",
};

const Color Coin_colors[3][3] = {
    {Color_Yellow, Color_Yellow, Color_Yellow},
    {Color_Yellow, Color_Yellow, Color_Yellow},
    {Color_Yellow, Color_Yellow, Color_Yellow},
};

const char Coin_collisionBox[3][4] = {
    "xxx",
    "xxx",
    "xxx",
};

const short Coin_height = 3;

void Coin_takeEffect(PickUp *this) {
    // TODO: Add coins to scoreboard.
}

#endif // PICKUP_COIN