#include "Renderer.h"

void setCursor(const int x, const int y) {
    wprintf(L"\033[%d;%dH", y + 1, x + 1);
}

void Renderer_renderCharAt(const Renderer *this, const wchar_t ch, const Color *color, const Vector2i *position) {
    if ((ch == L' ' && (color == NULL || *color == Color_Escape)) || outOfBounds(this, position->x, position->y)) {
        return;
    }
    this->canvas[position->y][position->x] = ch;
    this->colors[position->y][position->x] = color ? *color : Color_Escape;
}

void Renderer_renderStringAt(const Renderer *this, const wchar_t *str, const Color *colors, const Vector2i *position, const bool pure) {
    int len = wcslen(str);
    for (int i = 0; i < len; ++i) {
        if (outOfBounds(this, position->x + i, position->y)) {
            continue;
        }
        Color color;
        if (pure) {
            color = colors ? *colors : Color_Escape;
        } else {
            color = colors ? colors[i] : Color_Escape;
        }
        if (str[i] == L' ' && color == Color_Escape) {
            continue;
        }
        this->canvas[position->y][position->x + i] = str[i];
        this->colors[position->y][position->x + i] = color;
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
            while (this->canvas[i][j] == this->lastCanvas[i][j] && this->colors[i][j] == this->lastColors[i][j] && j + 1 < this->width) {
                ++j;
            }
            this->lastCanvas[i][j] = this->canvas[i][j];
            this->lastColors[i][j] = this->colors[i][j];
            wprintf(ANSI_Colors[this->colors[i][j]]);
            setCursor(this->x + j, this->y + i);
            putwchar(this->canvas[i][j]);
            wprintf(ANSI_Colors[Color_Escape]);
        }
    }
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
    renderer->clear = Renderer_clear;
    renderer->display = Renderer_display;

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