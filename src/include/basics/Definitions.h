#ifndef DEFINITIONS_H
#define DEFINITIONS_H


#include <stdbool.h>

typedef struct Vector2i {
    int x, y;
} Vector2i;

typedef struct Vector2f {
    float x, y;
} Vector2f;

typedef struct Rect {
    int x, y, w, h;
} Rect;

typedef struct FloatRect {
    float x, y, w, h;
} FloatRect;

typedef enum Color {
    Color_Escape,
    Color_Black,
    Color_DarkGray,
    Color_BlackUnderline,
    Color_BlackBlink,
    Color_Blue,
    Color_LightBlue,
    Color_BlueUnderline,
    Color_BlueBlink,
    Color_Green,
    Color_LightGreen,
    Color_GreenUnderline,
    Color_GreenBlink,
    Color_Cyan,
    Color_LightCyan,
    Color_CyanUnderline,
    Color_CyanBlink,
    Color_Red,
    Color_LightRed,
    Color_RedUnderline,
    Color_RedBlink,
    Color_Purple,
    Color_LightPurple,
    Color_PurpleUnderline,
    Color_PurpleBlink,
    Color_Brown,
    Color_Yellow,
    Color_YellowUnderline,
    Color_YellowBlink,
    Color_LightGray,
    Color_White,
    Color_GrayUnderline,
    Color_GrayBlink,
} Color;

const char *ANSI_Colors[] = {
    "\033[0m",
    "\033[0;30m",
    "\033[1;30m",
    "\033[4;30m",
    "\033[5;30m",
    "\033[0;34m",
    "\033[1;34m",
    "\033[4;34m",
    "\033[5;34m",
    "\033[0;32m",
    "\033[1;32m",
    "\033[4;32m",
    "\033[5;32m",
    "\033[0;36m",
    "\033[1;36m",
    "\033[4;36m",
    "\033[5;36m",
    "\033[0;31m",
    "\033[1;31m",
    "\033[4;31m",
    "\033[5;31m",
    "\033[0;35m",
    "\033[1;35m",
    "\033[4;35m",
    "\033[5;35m",
    "\033[0;33m",
    "\033[1;33m",
    "\033[4;33m",
    "\033[5;33m",
    "\033[0;37m",
    "\033[1;37m",
    "\033[4;37m",
    "\033[5;37m",
};

bool Rect_intersects(const Rect *lhs, const Rect *rhs) {
    return !(lhs->x + lhs->w - 1 < rhs->x || rhs->x + rhs->w - 1 < lhs->x || lhs->y + lhs->h - 1 < rhs->y || rhs->y + rhs->h - 1 < lhs->y);
}

bool Rect_contains(const Rect *rect, const Vector2i *point) {
    return !(point->x < rect->x || rect->x + rect->w - 1 < point->x || point->y < rect->y || rect->y + rect->h - 1 < point->y);
}

bool FloatRect_intersects(const FloatRect *lhs, const FloatRect *rhs) {
    return !(lhs->x + lhs->w < rhs->x || rhs->x + rhs->w < lhs->x || lhs->y + lhs->h < rhs->y || rhs->y + rhs->h < lhs->y);
}

bool FloatRect_contains(const FloatRect *rect, const Vector2f *point) {
    return !(point->x < rect->x || rect->x + rect->w < point->x || point->y < rect->y || rect->y + rect->h < point->y);
}

#endif // DEFINITIONS_H