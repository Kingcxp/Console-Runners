#include "Renderer.h"

void Renderer_renderCharAt(const Renderer *renderer, const wchar_t *ch, const Color *color, const Vector2i *position) {
    if ((*ch) == L' ' || outOfBounds(renderer, position->x, position->y)) {
        return;
    }
    renderer->canvas[position->y][position->x] = *ch;
    renderer->colors[position->y][position->x] = *color;
}

void Renderer_renderStringAt(const Renderer *renderer, const wchar_t *str, const Color *color, const Vector2i *position) {
    int len = wcslen(str);
    if (outOfBounds(renderer, position->x, position->y) || 
        outOfBounds(renderer, position->x + len - 1, position->y)) {
        return;
    }
    for (int i = 0; i < len; ++i) {
        if (str[i] == L' ') {
            continue;
        }
        renderer->canvas[position->y][position->x + i] = str[i];
        renderer->colors[position->y][position->x + i] = color[i];
    }
}

void Renderer_renderRectAt(const Renderer *renderer, const wchar_t **mat, const Color **colorMat, const Rect *rect, const Vector2i *center) {
    if (outOfBounds(renderer, rect->x - center->x, rect->y - center->y) || 
        outOfBounds(renderer, rect->x - center->x + rect->w - 1, rect->y - center->y + rect->h - 1)) {
        return;
    }
    const Vector2i *position = {rect->x - center->x, rect->y - center->y};
    for (int i = 0; i < rect->h; ++i) {
        for (int j = 0; j < rect->w; ++j) {
            if (mat[i][j] == L' ') {
                continue;
            }
            renderer->canvas[position->y + i][position->x + j] = mat[i][j];
            renderer->colors[position->y + i][position->x + j] = colorMat[i][j];
        }
    }
}

void Renderer_clear(const Renderer *renderer) {
    for (int i = 0; i < renderer->height; ++i) {
        for (int j = 0; j < renderer->width; ++j) {
            renderer->canvas[i][j] = L' ';
            renderer->colors[i][j] = Color_Escape;
        }
    }
}

void Renderer_display(const Renderer *renderer) {
    for (int i = 0; i < renderer->height; ++i) {
        for (int j = 0; j < renderer->width; ++j) {
            if (renderer->canvas[i][j] == renderer->lastCanvas[i][j] && renderer->colors[i][j] == renderer->lastColors[i][j]) {
                continue;
            }
            renderer->lastCanvas[i][j] = renderer->canvas[i][j];
            renderer->lastColors[i][j] = renderer->colors[i][j];
            if (outOfTermBounds(renderer->y + i, renderer->x + j)) {
                continue;
            }
            printf(ANSI_Colors[renderer->colors[i][j]]);
            bc_putchar((bc_point) {renderer->y + i, renderer->x + j}, renderer->canvas[i][j]);
            printf(ANSI_Colors[Color_Escape]);
        }
    }
}

bool Renderer_canFullyDisplay(const Renderer *renderer) {
    if (outOfTermBounds(renderer->x, renderer->y) || 
        outOfTermBounds(renderer->x + renderer->width - 1, renderer->y + renderer->height - 1)) {
        return false;
    }
    return true;
}

Renderer *createRenderer(int x, int y, int w, int h) {
    Renderer *renderer = (Renderer *)malloc(sizeof(Renderer));
    renderer->width = w, renderer->height = h;
    renderer->x = x, renderer->y = y;
    renderer->canvas = (wchar_t **)malloc(sizeof(wchar_t *) * renderer->height);
    renderer->lastCanvas = (wchar_t **)malloc(sizeof(wchar_t *) * renderer->height);
    renderer->colors = (Color **)malloc(sizeof(Color *) * renderer->height);
    renderer->lastColors = (Color **)malloc(sizeof(Color *) * renderer->height);
    for (int i = 0; i < renderer->height; ++i) {
        renderer->canvas[i] = (wchar_t *)malloc(sizeof(wchar_t) * renderer->width);
        renderer->lastCanvas[i] = (wchar_t *)malloc(sizeof(wchar_t) * renderer->width);
        renderer->colors[i] = (Color *)malloc(sizeof(Color) * renderer->width);
        renderer->lastColors[i] = (Color *)malloc(sizeof(Color) * renderer->width);
        for (int j = 0; j < renderer->width; ++j) {
            renderer->canvas[i][j] = L' ';
            renderer->lastCanvas[i][j] = L' ';
            renderer->colors[i][j] = Color_Escape;
            renderer->lastColors[i][j] = Color_Escape;
        }
    }
    renderer->renderCharAt = Renderer_renderCharAt;
    renderer->renderStringAt = Renderer_renderStringAt;
    renderer->renderRectAt = Renderer_renderRectAt;
    renderer->clear = Renderer_clear;
    renderer->display = Renderer_display;
    renderer->canFullyDisplay = Renderer_canFullyDisplay;

    return renderer;
}

void destroyRenderer(Renderer *renderer) {
    for (int i = 0; i < renderer->height; ++i) {
        free(renderer->canvas[i]);
        free(renderer->lastCanvas[i]);
        free(renderer->colors[i]);
        free(renderer->lastColors[i]);
    }
    free(renderer->canvas);
    free(renderer->lastCanvas);
    free(renderer->colors);
    free(renderer->lastColors);

    free(renderer);
}