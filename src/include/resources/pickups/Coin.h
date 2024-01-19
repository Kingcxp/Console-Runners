#ifndef PICKUP_COIN
#define PICKUP_COIN


#include "../../elements/PickUp.h"

const wchar_t Coin_frame[3][6] = {
    L" .-. ",
    L" |$| ",
    L" `-` ",
};

const Color Coin_colors[3][5] = {
    {Color_Escape, Color_Yellow, Color_Yellow, Color_Yellow, Color_Escape},
    {Color_Escape, Color_Yellow, Color_Yellow, Color_Yellow, Color_Escape},
    {Color_Escape, Color_Yellow, Color_Yellow, Color_Yellow, Color_Escape},
};

const char Coin_collisionBox[3][6] = {
    " xxx ",
    " xxx ",
    " xxx ",
};

const short Coin_height = 3;

void Coin_takeEffect(PickUp *this, Runner *runner) {
    this->globals->scoreBoard->coins += 1;
    this->globals->scoreBoard->score += 100.f;
}

#endif // PICKUP_COIN