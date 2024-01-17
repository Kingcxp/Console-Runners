#ifndef GLOBALS_H
#define GLOBALS_H

#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "basics/Renderer.c"

typedef struct Globals {
    Renderer    *renderer;
} Globals;

#define outOfBounds(renderer, x, y) ((x) < 0 || (x) >= renderer->width || (y) < 0 || (y) >= renderer->height)

bool outOfTermBounds(int x, int y) {
    int termWidth, termHeight;
    bc_termsize(&termWidth, &termHeight);
    return (x < 0 || y < 0 || x >= termWidth || y >= termHeight);
}

int random(int l, int r) {
    return rand() % (r - l + 1) + l;
}

#endif // GLOBALS_H