#ifndef PROGRESSBAR
#define PROGRESSBAR


#include <math.h>
#include "../basics/Renderer.h"

#define SCROLL_SPEED 100.f

typedef struct ProgressBar {
    // Methods

    void            (*update)(struct ProgressBar *this, float deltaTime);
    void            (*render)(const struct ProgressBar *this, const Renderer *renderer);
    void            (*setProgress)(struct ProgressBar *this, const float progress);
    void            (*forceProgress)(struct ProgressBar *this, const float progress);

    // Variables

    float           progress,
                    target,
                    *follow,
                    total;

    Color           color;

    Vector2i        size,
                    position;
} ProgressBar;

ProgressBar *createProgressBar(Color color, int width, int height, float progress, float total);
void destroyProgressBar(ProgressBar *bar);

#endif // PROGRESSBAR