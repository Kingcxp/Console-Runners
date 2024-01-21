#ifndef RUNNER_KID
#define RUNNER_KID


#include "../../elements/Runner.h"

const wchar_t Kid_runningFrames[4][4][4] = {
    {
        L"   ",
        L"   ",
        L"\\○/",
        L"/ \\",
    },
    {
        L"   ",
        L"   ",
        L"\\○>",
        L"< \\",
    },
    {
        L"   ",
        L"   ",
        L"\\○/",
        L"/ \\",
    },
    {
        L"   ",
        L"   ",
        L"<○/",
        L"/ >",
    },
};
const char Kid_runningCollisionBox[4][4][4] = {
    {
        "   ",
        "   ",
        "xxx",
        "x x",
    },
    {
        "   ",
        "   ",
        "xxx",
        "x x",
    },
    {
        "   ",
        "   ",
        "xxx",
        "x x",
    },
    {
        "   ",
        "   ",
        "xxx",
        "x x",
    },
};
const Color Kid_runningColors[4][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Yellow, Color_Escape},
        {Color_Yellow, Color_Yellow, Color_Yellow},
        {Color_Yellow, Color_Escape, Color_Yellow},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Yellow, Color_Escape},
        {Color_Yellow, Color_Yellow, Color_Yellow},
        {Color_Yellow, Color_Escape, Color_Yellow},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Yellow, Color_Escape},
        {Color_Yellow, Color_Yellow, Color_Yellow},
        {Color_Yellow, Color_Escape, Color_Yellow},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Yellow, Color_Escape},
        {Color_Yellow, Color_Yellow, Color_Yellow},
        {Color_Yellow, Color_Escape, Color_Yellow},
    },
};
const short Kid_runningFrameCount = 4;
const float Kid_runningSeconds[4] = {0.1f, 0.1f, 0.1f, 0.1f};

const wchar_t Kid_rollingFrames[5][4][4] = {
    {
        L"   ",
        L"   ",
        L"\\○/",
        L"/ \\",
    },
    {
        L"   ",
        L"   ",
        L" ○ ",
        L"/ \\",
    },
    {
        L"   ",
        L"   ",
        L"   ",
        L"/○\\",
    },
    {
        L"   ",
        L"   ",
        L" ○ ",
        L"/ \\",
    },
    {
        L"   ",
        L"   ",
        L"\\○/",
        L"/ \\",
    },
};
const char Kid_rollingCollisionBox[5][4][4] = {
    {
        "   ",
        "   ",
        "xxx",
        "x x",
    },
    {
        "   ",
        "   ",
        " x ",
        "x x",
    },
    {
        "   ",
        "   ",
        "   ",
        "xxx",
    },
    {
        "   ",
        "   ",
        " x ",
        "x x",
    },
    {
        "   ",
        "   ",
        "xxx",
        "x x",
    },
};
const Color Kid_rollingColors[5][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Yellow, Color_Yellow, Color_Yellow},
        {Color_Yellow, Color_Escape, Color_Yellow},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Yellow, Color_Escape},
        {Color_Yellow, Color_Escape, Color_Yellow},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Yellow, Color_Yellow, Color_Yellow},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Yellow, Color_Escape},
        {Color_Yellow, Color_Escape, Color_Yellow},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Yellow, Color_Yellow, Color_Yellow},
        {Color_Yellow, Color_Escape, Color_Yellow},
    },
};
const short Kid_rollingFrameCount = 5;
const float Kid_rollingSeconds[5] = {0.15f, 0.15f, 0.15f, 0.15f, 0.15f};

const wchar_t Kid_jumpingFrames[1][4][4] = {
    {
        L"   ",
        L"   ",
        L"\\○/",
        L"/ \\",
    }
};
const Color Kid_jumpingColors[1][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Yellow, Color_Yellow, Color_Yellow},
        {Color_Yellow, Color_Escape, Color_Yellow},
    }
};
const char Kid_jumpingCollisionBox[1][4][4] = {
    {
        "   ",
        "   ",
        "xxx",
        "x x",
    }
};
const short Kid_jumpingFrameCount = 1;

const wchar_t Kid_deadFrames[1][4][4] = {
    {
        L"   ",
        L"   ",
        L"\\ /",
        L"/○\\",
    }
};
const Color Kid_deadColors[1][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Yellow, Color_Escape, Color_Yellow},
        {Color_Yellow, Color_Yellow, Color_Yellow},
    }
};
const short Kid_deadFrameCount = 1;

const float Kid_jumpSpeed = 15.f;
const float Kid_gravity = 26.f;
const float Kid_switchTrackSpeed = 24.f;
const float Kid_runningSpeed = 10.f;
const wchar_t *Kid_name = L"Running Kid";
const wchar_t *Kid_description = L"Smaller hit box";
const wchar_t *Kid_comment = L"\"Why? Why a kid???\"";
const int Kid_price = 210;

#endif // RUNNER_KID
