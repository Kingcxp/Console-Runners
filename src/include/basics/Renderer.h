#ifndef RENDERER
#define RENDERER


#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>
#include "Definitions.h"

typedef struct Renderer {
    // Methods

    void            (*renderCharAt)(const struct Renderer *this, const wchar_t ch, const Color *color, const Vector2i *position);
    void            (*renderStringAt)(const struct Renderer *this, const wchar_t *str, const Color *colors, const Vector2i *position, const bool pure);
    void            (*clear)(const struct Renderer *this);
    void            (*display)(const struct Renderer *this);

    // Variables

    wchar_t         **canvas,
                    **lastCanvas;

    Color           **colors,
                    **lastColors;

    int             width,
                    height,
                    x, y;
} Renderer;

Renderer *createRenderer(int x, int y, int w, int h);
void destroyRenderer(Renderer *renderer);

#endif // RENDERER
