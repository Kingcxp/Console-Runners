#ifndef RUNNER_FINAL
#define RUNNER_FINAL


#include "../../elements/Runner.h"

const wchar_t Final_runningFrames[4][4][4] = {
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
const char Final_runningCollisionBox[4][4][4] = {
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
const Color Final_runningColors[4][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    },
};
const short Final_runningFrameCount = 4;
const float Final_runningSeconds[4] = {0.1f, 0.1f, 0.1f, 0.1f};

const wchar_t Final_rollingFrames[7][4][4] = {
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
const char Final_rollingCollisionBox[7][4][4] = {
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
const Color Final_rollingColors[7][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    },
};
const short Final_rollingFrameCount = 7;
const float Final_rollingSeconds[7] = {0.1f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.1f};

const wchar_t Final_jumpingFrames[1][4][4] = {
    {
        L"   ",
        L"\\○/",
        L" | ",
        L"/ \\",
    }
};
const Color Final_jumpingColors[1][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    }
};
const char Final_jumpingCollisionBox[1][4][4] = {
    {
        "   ",
        "xxx",
        " x ",
        "x x",
    }
};
const short Final_jumpingFrameCount = 1;

const wchar_t Final_deadFrames[1][4][4] = {
    {
        L"   ",
        L"   ",
        L"\\ /",
        L"/○\\",
    }
};
const Color Final_deadColors[1][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
    }
};
const short Final_deadFrameCount = 1;

const float Final_jumpSpeed = 15.f;
const float Final_gravity = 26.f;
const float Final_switchTrackSpeed = 24.f;
const float Final_runningSpeed = 10.f;
const wchar_t *Final_name = L"Final Runner";
const wchar_t *Final_description = L"Invincible!";
const wchar_t *Final_comment = L"\"Represents the end.\"";
const int Final_price = 8192;

#endif // RUNNER_FINAL
