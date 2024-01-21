#ifndef RUNNER_RAINBOW
#define RUNNER_RAINBOW


#include "../../elements/Runner.h"

const wchar_t RR_runningFrames[4][4][4] = {
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
const char RR_runningCollisionBox[4][4][4] = {
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
const Color RR_runningColors[4][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Green, Color_Escape},
        {Color_LightGray, Color_Yellow, Color_Blue},
        {Color_Purple, Color_Escape, Color_LightRed},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Yellow, Color_Escape},
        {Color_LightRed, Color_Green, Color_Purple},
        {Color_Blue, Color_Escape, Color_LightGray},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_LightGray, Color_Escape},
        {Color_Purple, Color_Green, Color_Blue},
        {Color_Yellow, Color_Escape, Color_LightRed},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Blue, Color_Escape},
        {Color_LightGray, Color_LightRed, Color_Yellow},
        {Color_Purple, Color_Escape, Color_Green},
    },
};
const short RR_runningFrameCount = 4;
const float RR_runningSeconds[4] = {0.1f, 0.1f, 0.1f, 0.1f};

const wchar_t RR_rollingFrames[7][4][4] = {
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
const char RR_rollingCollisionBox[7][4][4] = {
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
const Color RR_rollingColors[7][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_LightGray, Color_Green, Color_LightBlue},
        {Color_Escape, Color_Yellow, Color_Escape},
        {Color_LightRed, Color_Escape, Color_Cyan},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Purple, Color_LightRed, Color_Green},
        {Color_LightCyan, Color_Escape, Color_Yellow},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Green, Color_Escape},
        {Color_LightCyan, Color_Escape, Color_Yellow},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_LightCyan, Color_LightRed, Color_Purple},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_LightCyan, Color_Escape},
        {Color_LightRed, Color_Escape, Color_Purple},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Purple, Color_Yellow, Color_LightGray},
        {Color_LightRed, Color_Escape, Color_LightCyan},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Yellow, Color_LightRed, Color_LightBlue},
        {Color_Escape, Color_LightGray, Color_Escape},
        {Color_LightPurple, Color_Escape, Color_Green},
    },
};
const short RR_rollingFrameCount = 7;
const float RR_rollingSeconds[7] = {0.1f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.1f};

const wchar_t RR_jumpingFrames[1][4][4] = {
    {
        L"   ",
        L"\\○/",
        L" | ",
        L"/ \\",
    }
};
const Color RR_jumpingColors[1][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    }
};
const char RR_jumpingCollisionBox[1][4][4] = {
    {
        "   ",
        "xxx",
        " x ",
        "x x",
    }
};
const short RR_jumpingFrameCount = 1;

const wchar_t RR_deadFrames[1][4][4] = {
    {
        L"   ",
        L"   ",
        L"\\ /",
        L"/○\\",
    }
};
const Color RR_deadColors[1][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_LightCyan, Color_Escape, Color_LightPurple},
        {Color_LightGreen, Color_LightRed, Color_Yellow},
    }
};
const short RR_deadFrameCount = 1;

const float RR_jumpSpeed = 15.f;
const float RR_gravity = 26.f;
const float RR_switchTrackSpeed = 24.f;
const float RR_runningSpeed = 10.f;
const wchar_t *RR_name = L"Rainbow Runner";
const wchar_t *RR_description = L"Colorful classic";
const wchar_t *RR_comment = L"\"Doesn't feel any better.\"";
const int RR_price = 120;

#endif // RUNNER_RAINBOW
