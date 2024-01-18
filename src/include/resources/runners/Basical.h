#ifndef RUNNER_BASICAL
#define RUNNER_BASICAL


#include "../../elements/Runner.h"

const wchar_t BR_runningFrames[4][4][4] = {
    {
        L"   ",
        L" ○ ",
        L"/|\\",
        L"/ \\",
    },
    {
        L"   ",
        L" ○ ",
        L"/|>",
        L"< \\",
    },
    {
        L"   ",
        L" ○ ",
        L"/|\\",
        L"/ \\",
    },
    {
        L"   ",
        L" ○ ",
        L"<|\\",
        L"/ >",
    },
};
const char BR_runningCollisionBox[4][4][4] = {
    {
        "   ",
        " x ",
        "xxx",
        "x x",
    },
    {
        "   ",
        " x ",
        "xxx",
        "x x",
    },
    {
        "   ",
        " x ",
        "xxx",
        "x x",
    },
    {
        "   ",
        " x ",
        "xxx",
        "x x",
    },
};
const Color BR_runningColors[4][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Cyan, Color_Escape},
        {Color_Cyan, Color_Cyan, Color_Cyan},
        {Color_Cyan, Color_Escape, Color_Cyan},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Cyan, Color_Escape},
        {Color_Cyan, Color_Cyan, Color_Cyan},
        {Color_Cyan, Color_Escape, Color_Cyan},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Cyan, Color_Escape},
        {Color_Cyan, Color_Cyan, Color_Cyan},
        {Color_Cyan, Color_Escape, Color_Cyan},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Cyan, Color_Escape},
        {Color_Cyan, Color_Cyan, Color_Cyan},
        {Color_Cyan, Color_Escape, Color_Cyan},
    },
};
const short BR_runningFrameCount = 4;
const float BR_runningSeconds[4] = {0.1f, 0.1f, 0.1f, 0.1f};

const wchar_t BR_rollingFrames[7][4][4] = {
    {
        L"   ",
        L"\\○/",
        L" | ",
        L"/ \\",
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
    {
        L"   ",
        L"\\○/",
        L" | ",
        L"/ \\",
    },
};
const char BR_rollingCollisionBox[7][4][4] = {
    {
        "   ",
        "xxx",
        " x ",
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
    {
        "   ",
        "xxx",
        " x ",
        "x x",
    },
};
const Color BR_rollingColors[7][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Cyan, Color_Cyan, Color_Cyan},
        {Color_Escape, Color_Cyan, Color_Escape},
        {Color_Cyan, Color_Escape, Color_Cyan},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Cyan, Color_Cyan, Color_Cyan},
        {Color_Cyan, Color_Escape, Color_Cyan},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Cyan, Color_Escape},
        {Color_Cyan, Color_Escape, Color_Cyan},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Cyan, Color_Cyan, Color_Cyan},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Cyan, Color_Escape},
        {Color_Cyan, Color_Escape, Color_Cyan},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Cyan, Color_Cyan, Color_Cyan},
        {Color_Cyan, Color_Escape, Color_Cyan},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Cyan, Color_Cyan, Color_Cyan},
        {Color_Escape, Color_Cyan, Color_Escape},
        {Color_Cyan, Color_Escape, Color_Cyan},
    },
};
const short BR_rollingFrameCount = 7;
const float BR_rollingSeconds[7] = {0.1f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.1f};

const wchar_t BR_jumpingFrames[1][4][4] = {
    {
        L"   ",
        L"\\○/",
        L" | ",
        L"/ \\",
    }
};
const Color BR_jumpingColors[1][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Cyan, Color_Cyan, Color_Cyan},
        {Color_Escape, Color_Cyan, Color_Escape},
        {Color_Cyan, Color_Escape, Color_Cyan},
    }
};
const char BR_jumpingCollisionBox[1][4][4] = {
    {
        "   ",
        "xxx",
        " x ",
        "x x",
    }
};
const short BR_jumpingFrameCount = 1;

const wchar_t BR_deadFrames[1][4][4] = {
    {
        L"   ",
        L"   ",
        L"\\ /",
        L"/○\\",
    }
};
const Color BR_deadColors[1][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Cyan, Color_Escape, Color_Cyan},
        {Color_Cyan, Color_Cyan, Color_Cyan},
    }
};
const short BR_deadFrameCount = 1;

const float BR_jumpSpeed = 15.f;
const float BR_gravity = 26.f;
const float BR_switchTrackSpeed = 24.f;
const float BR_runningSpeed = 10.f;

#endif // RUNNER_BASICAL