#ifndef RUNNER_TRIANGLE
#define RUNNER_TRIANGLE


#include "../../elements/Runner.h"

const wchar_t TR_runningFrames[4][4][4] = {
    {
        L"   ",
        L" ▲ ",
        L"/|\\",
        L"/ \\",
    },
    {
        L"   ",
        L" ▲ ",
        L"/|>",
        L"< \\",
    },
    {
        L"   ",
        L" ▲ ",
        L"/|\\",
        L"/ \\",
    },
    {
        L"   ",
        L" ▲ ",
        L"<|\\",
        L"/ >",
    },
};
const char TR_runningCollisionBox[4][4][4] = {
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
const Color TR_runningColors[4][4][3] = {
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
const short TR_runningFrameCount = 4;
const float TR_runningSeconds[4] = {0.1f, 0.1f, 0.1f, 0.1f};

const wchar_t TR_rollingFrames[7][4][4] = {
    {
        L"   ",
        L"\\▲/",
        L" | ",
        L"/ \\",
    },
    {
        L"   ",
        L"   ",
        L"\\▲/",
        L"/ \\",
    },
    {
        L"   ",
        L"   ",
        L" ▲ ",
        L"/ \\",
    },
    {
        L"   ",
        L"   ",
        L"   ",
        L"/▲\\",
    },
    {
        L"   ",
        L"   ",
        L" ▲ ",
        L"/ \\",
    },
    {
        L"   ",
        L"   ",
        L"\\▲/",
        L"/ \\",
    },
    {
        L"   ",
        L"\\▲/",
        L" | ",
        L"/ \\",
    },
};
const char TR_rollingCollisionBox[7][4][4] = {
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
const Color TR_rollingColors[7][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Yellow, Color_Yellow, Color_Yellow},
        {Color_Escape, Color_Yellow, Color_Escape},
        {Color_Yellow, Color_Escape, Color_Yellow},
    },
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
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Yellow, Color_Yellow, Color_Yellow},
        {Color_Escape, Color_Yellow, Color_Escape},
        {Color_Yellow, Color_Escape, Color_Yellow},
    },
};
const short TR_rollingFrameCount = 7;
const float TR_rollingSeconds[7] = {0.1f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.1f};

const wchar_t TR_jumpingFrames[1][4][4] = {
    {
        L"   ",
        L"\\▲/",
        L" | ",
        L"/ \\",
    }
};
const Color TR_jumpingColors[1][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Yellow, Color_Yellow, Color_Yellow},
        {Color_Escape, Color_Yellow, Color_Escape},
        {Color_Yellow, Color_Escape, Color_Yellow},
    }
};
const char TR_jumpingCollisionBox[1][4][4] = {
    {
        "   ",
        "xxx",
        " x ",
        "x x",
    }
};
const short TR_jumpingFrameCount = 1;

const wchar_t TR_deadFrames[1][4][4] = {
    {
        L"   ",
        L"   ",
        L"\\ /",
        L"/▲\\",
    }
};
const Color TR_deadColors[1][4][3] = {
    {
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Escape, Color_Escape, Color_Escape},
        {Color_Yellow, Color_Escape, Color_Yellow},
        {Color_Yellow, Color_Yellow, Color_Yellow},
    }
};
const short TR_deadFrameCount = 1;

const float TR_jumpSpeed = 18.f;
const float TR_gravity = 26.f;
const float TR_switchTrackSpeed = 30.f;
const float TR_runningSpeed = 16.f;
const wchar_t *TR_name = L"Triangle Runner";
const wchar_t *TR_description = L"Triangle makes power";
const wchar_t *TR_comment = L"\"Why is he so...sharp?\"";
const int TR_price = 256;

#endif // RUNNER_TRIANGLE
