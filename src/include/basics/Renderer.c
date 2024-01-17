#include "Renderer.h"

void Renderer_renderCharAt(const Renderer *this, const wchar_t *ch, const Color *color, const Vector2i *position) {
    if ((*ch) == L' ' || outOfBounds(this, position->x, position->y)) {
        return;
    }
    this->canvas[position->y][position->x] = *ch;
    this->colors[position->y][position->x] = *color;
}

void Renderer_renderStringAt(const Renderer *this, const wchar_t *str, const Color *color, const Vector2i *position) {
    int len = wcslen(str);
    for (int i = 0; i < len; ++i) {
        if (str[i] == L' ' || outOfBounds(this, position->x + i, position->y)) {
            continue;
        }
        this->canvas[position->y][position->x + i] = str[i];
        this->colors[position->y][position->x + i] = color[i];
    }
}

void Renderer_renderRectAt(const Renderer *this, const wchar_t **mat, const Color **colorMat, const Rect *rect, const Vector2i *center) {
    const Vector2i *position = {rect->x - center->x, rect->y - center->y};
    for (int i = 0; i < rect->h; ++i) {
        for (int j = 0; j < rect->w; ++j) {
            if (mat[i][j] == L' ' || outOfBounds(this, position->x + j, position->y + i)) {
                continue;
            }
            this->canvas[position->y + i][position->x + j] = mat[i][j];
            this->colors[position->y + i][position->x + j] = colorMat[i][j];
        }
    }
}

void Renderer_clear(const Renderer *this) {
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            this->canvas[i][j] = L' ';
            this->colors[i][j] = Color_Escape;
        }
    }
}

void Renderer_display(const Renderer *this) {
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            if (this->canvas[i][j] == this->lastCanvas[i][j] && this->colors[i][j] == this->lastColors[i][j]) {
                continue;
            }
            this->lastCanvas[i][j] = this->canvas[i][j];
            this->lastColors[i][j] = this->colors[i][j];
            if (outOfTermBounds(this->y + i, this->x + j)) {
                continue;
            }
            printf(ANSI_Colors[this->colors[i][j]]);
            bc_putchar((bc_point) {this->y + i, this->x + j}, this->canvas[i][j]);
            printf(ANSI_Colors[Color_Escape]);
        }
    }
}

bool Renderer_canFullyDisplay(const Renderer *this) {
    if (outOfTermBounds(this->x, this->y) || 
        outOfTermBounds(this->x + this->width - 1, this->y + this->height - 1)) {
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