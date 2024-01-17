#ifndef RENDERER
#define RENDERER


#include <wchar.h>
#include <stdbool.h>
#include "../basics/CollisionBox.h"
#include "../basics/boxchar/boxchar.h"

typedef struct Renderer {
    // Methods

    void            (*renderCharAt)(const Renderer *this, const wchar_t *ch, const Color *color, const Vector2i *position);
    void            (*renderStringAt)(const Renderer *this, const wchar_t *str, const Color *colors, const Vector2i *position);
    void            (*renderRectAt)(const Renderer *this, const wchar_t **mat, const Color **colorMat, const Rect *dstRect, const Vector2i *center);
    void            (*clear)(const Renderer *this);
    void            (*display)(const Renderer *this);
    bool            (*canFullyDisplay)(const Renderer *this);

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