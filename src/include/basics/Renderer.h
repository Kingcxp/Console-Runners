#ifndef RENDERER_H
#define RENDERER_H


#include <wchar.h>
#include "../Globals.h"

typedef struct Renderer {
    // Methods

    void            (*renderCharAt)(const Renderer *, const wchar_t *, const Color *, const Vector2i *);
    void            (*renderStringAt)(const Renderer *, const wchar_t *, const Color *, const Vector2i *);
    void            (*renderRectAt)(const Renderer *, const wchar_t **, const Color **, const Rect *, const Vector2i *);
    void            (*clear)(const Renderer *);
    void            (*display)(const Renderer *);
    bool            (*canFullyDisplay)(const Renderer *);

    // Variables

    wchar_t         **canvas,
                    **lastCanvas;

    Color           **colors,
                    **lastColors;

    int             width,
                    height,
                    x, y;
} Renderer;

#endif // RENDERER_H