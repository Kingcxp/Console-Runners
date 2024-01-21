#ifndef RUNNER_STEEL
#define RUNNER_STEEL


#include "../../elements/Runner.h"

const wchar_t Steel_runningFrames[4][4][4] = {
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
const char Steel_runningCollisionBox[4][4][4] = {
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
const Color Steel_runningColors[4][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_DarkGray, Color_Escape},
        {Color_DarkGray, Color_DarkGray, Color_DarkGray},
        {Color_DarkGray, Color_Escape, Color_DarkGray},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_DarkGray, Color_Escape},
        {Color_DarkGray, Color_DarkGray, Color_DarkGray},
        {Color_DarkGray, Color_Escape, Color_DarkGray},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_DarkGray, Color_Escape},
        {Color_DarkGray, Color_DarkGray, Color_DarkGray},
        {Color_DarkGray, Color_Escape, Color_DarkGray},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_DarkGray, Color_Escape},
        {Color_DarkGray, Color_DarkGray, Color_DarkGray},
        {Color_DarkGray, Color_Escape, Color_DarkGray},
    },
};
const short Steel_runningFrameCount = 4;
const float Steel_runningSeconds[4] = {0.1f, 0.1f, 0.1f, 0.1f};

const wchar_t Steel_rollingFrames[7][4][4] = {
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
const char Steel_rollingCollisionBox[7][4][4] = {
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
const Color Steel_rollingColors[7][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_DarkGray, Color_DarkGray, Color_DarkGray},
        {Color_Escape, Color_DarkGray, Color_Escape},
        {Color_DarkGray, Color_Escape, Color_DarkGray},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_DarkGray, Color_DarkGray, Color_DarkGray},
        {Color_DarkGray, Color_Escape, Color_DarkGray},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_DarkGray, Color_Escape},
        {Color_DarkGray, Color_Escape, Color_DarkGray},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_DarkGray, Color_DarkGray, Color_DarkGray},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_DarkGray, Color_Escape},
        {Color_DarkGray, Color_Escape, Color_DarkGray},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_DarkGray, Color_DarkGray, Color_DarkGray},
        {Color_DarkGray, Color_Escape, Color_DarkGray},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_DarkGray, Color_DarkGray, Color_DarkGray},
        {Color_Escape, Color_DarkGray, Color_Escape},
        {Color_DarkGray, Color_Escape, Color_DarkGray},
    },
};
const short Steel_rollingFrameCount = 7;
const float Steel_rollingSeconds[7] = {0.1f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.1f};

const wchar_t Steel_jumpingFrames[1][4][4] = {
    {
        L"   ",
        L"\\○/",
        L" | ",
        L"/ \\",
    }
};
const Color Steel_jumpingColors[1][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_DarkGray, Color_DarkGray, Color_DarkGray},
        {Color_Escape, Color_DarkGray, Color_Escape},
        {Color_DarkGray, Color_Escape, Color_DarkGray},
    }
};
const char Steel_jumpingCollisionBox[1][4][4] = {
    {
        "   ",
        "xxx",
        " x ",
        "x x",
    }
};
const short Steel_jumpingFrameCount = 1;

const wchar_t Steel_deadFrames[1][4][4] = {
    {
        L"   ",
        L"   ",
        L"\\ /",
        L"/○\\",
    }
};
const Color Steel_deadColors[1][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_DarkGray, Color_Escape, Color_DarkGray},
        {Color_DarkGray, Color_DarkGray, Color_DarkGray},
    }
};
const short Steel_deadFrameCount = 1;

const float Steel_jumpSpeed = 10.f;
const float Steel_gravity = 26.f;
const float Steel_switchTrackSpeed = 24.f;
const float Steel_runningSpeed = 6.f;
const wchar_t *Steel_name = L"Steel Runner";
const wchar_t *Steel_description = L"Way too heavy";
const wchar_t *Steel_comment = L"\"It's hard to move it.\"";
const int Steel_price = 512;

#endif // RUNNER_STEEL
