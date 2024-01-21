#ifndef PICKUP_INVINCIBLE
#define PICKUP_INVINCIBLE


#include "../../elements/PickUp.h"

#define INVINCIBLE_TIME 5.f

const wchar_t Invincible_frame[3][6] = {
    L" /▼\\ ",
    L" >&< ",
    L" \\▲/ ",
};

const Color Invincible_colors[3][5] = {
    {Color_Escape, Color_LightBlue, Color_Red, Color_Brown, Color_Escape},
    {Color_Escape, Color_LightPurple, Color_Green, Color_Blue, Color_Escape},
    {Color_Escape, Color_Purple, Color_Yellow, Color_Cyan, Color_Escape},
};

const char Invincible_collisionBox[3][6] = {
    " xxx ",
    " xxx ",
    " xxx ",
};

const short Invincible_height = 3;

void Invincible_takeEffect(PickUp *this, Runner *runner) {
    this->globals->scoreBoard->score += 500.f;
    this->globals->scoreBoard->isInvincible = true;
    this->globals->scoreBoard->invincibleTimer = INVINCIBLE_TIME;
}

#endif // PICKUP_INVINCIBLE
