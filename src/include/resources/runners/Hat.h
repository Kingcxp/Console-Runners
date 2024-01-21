#ifndef RUNNER_HAT
#define RUNNER_HAT


#include "../../elements/Runner.h"

const wchar_t Hat_runningFrames[4][4][4] = {
    {
        L"<^>",
        L" ○ ",
        L"/|\\",
        L"/ \\",
    },
    {
        L"<^>",
        L" ○ ",
        L"/|>",
        L"< \\",
    },
    {
        L"<^>",
        L" ○ ",
        L"/|\\",
        L"/ \\",
    },
    {
        L"<^>",
        L" ○ ",
        L"<|\\",
        L"/ >",
    },
};
const char Hat_runningCollisionBox[4][4][4] = {
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
const Color Hat_runningColors[4][4][3] = {
    {
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Escape, Color_Green, Color_Escape},
        {Color_Green, Color_Green, Color_Green},
        {Color_Green, Color_Escape, Color_Green},
    },
    {
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Escape, Color_Green, Color_Escape},
        {Color_Green, Color_Green, Color_Green},
        {Color_Green, Color_Escape, Color_Green},
    },
    {
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Escape, Color_Green, Color_Escape},
        {Color_Green, Color_Green, Color_Green},
        {Color_Green, Color_Escape, Color_Green},
    },
    {
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Escape, Color_Green, Color_Escape},
        {Color_Green, Color_Green, Color_Green},
        {Color_Green, Color_Escape, Color_Green},
    },
};
const short Hat_runningFrameCount = 4;
const float Hat_runningSeconds[4] = {0.1f, 0.1f, 0.1f, 0.1f};

const wchar_t Hat_rollingFrames[7][4][4] = {
    {
        L"<^>",
        L"\\○/",
        L" | ",
        L"/ \\",
    },
    {
        L"   ",
        L"<^>",
        L"\\○/",
        L"/ \\",
    },
    {
        L"   ",
        L"<^>",
        L" ○ ",
        L"/ \\",
    },
    {
        L"   ",
        L"   ",
        L"<^>",
        L"/○\\",
    },
    {
        L"   ",
        L"<^>",
        L" ○ ",
        L"/ \\",
    },
    {
        L"   ",
        L"<^>",
        L"\\○/",
        L"/ \\",
    },
    {
        L"<^>",
        L"\\○/",
        L" | ",
        L"/ \\",
    },
};
const char Hat_rollingCollisionBox[7][4][4] = {
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
const Color Hat_rollingColors[7][4][3] = {
    {
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Green, Color_Green, Color_Green},
        {Color_Escape, Color_Green, Color_Escape},
        {Color_Green, Color_Escape, Color_Green},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Green, Color_Green, Color_Green},
        {Color_Green, Color_Escape, Color_Green},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Escape, Color_Green, Color_Escape},
        {Color_Green, Color_Escape, Color_Green},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Green, Color_Green, Color_Green},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Escape, Color_Green, Color_Escape},
        {Color_Green, Color_Escape, Color_Green},
    },
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Green, Color_Green, Color_Green},
        {Color_Green, Color_Escape, Color_Green},
    },
    {
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Green, Color_Green, Color_Green},
        {Color_Escape, Color_Green, Color_Escape},
        {Color_Green, Color_Escape, Color_Green},
    },
};
const short Hat_rollingFrameCount = 7;
const float Hat_rollingSeconds[7] = {0.1f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.1f};

const wchar_t Hat_jumpingFrames[1][4][4] = {
    {
        L"<^>",
        L"\\○/",
        L" | ",
        L"/ \\",
    }
};
const Color Hat_jumpingColors[1][4][3] = {
    {
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Green, Color_Green, Color_Green},
        {Color_Escape, Color_Green, Color_Escape},
        {Color_Green, Color_Escape, Color_Green},
    }
};
const char Hat_jumpingCollisionBox[1][4][4] = {
    {
        "   ",
        "xxx",
        " x ",
        "x x",
    }
};
const short Hat_jumpingFrameCount = 1;

const wchar_t Hat_deadFrames[1][4][4] = {
    {
        L"<^>",
        L"   ",
        L"\\ /",
        L"/○\\",
    }
};
const Color Hat_deadColors[1][4][3] = {
    {
        {Color_LightGray, Color_LightGray, Color_LightGray},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Green, Color_Escape, Color_Green},
        {Color_Green, Color_Green, Color_Green},
    }
};
const short Hat_deadFrameCount = 1;

const float Hat_jumpSpeed = 15.f;
const float Hat_gravity = 26.f;
const float Hat_switchTrackSpeed = 24.f;
const float Hat_runningSpeed = 10.f;
const wchar_t *Hat_name = L"Runner with a hat";
const wchar_t *Hat_description = L"Classic style with a hat";
const wchar_t *Hat_comment = L"\"121 coins worth of a hat!\"";
const int Hat_price = 121;

#endif // RUNNER_HAT
