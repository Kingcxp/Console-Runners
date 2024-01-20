#include "ProgressBar.h"

void ProgressBar_update(ProgressBar *this, float deltaTime) {
    if (this->follow) {
        this->setProgress(this, *this->follow);
    }
    if (this->progress > this->target) {
        this->progress -= SCROLL_SPEED * deltaTime;
        if (this->progress < this->target) {
            this->progress = this->target;
        }
    } else if (this->progress < this->target) {
        this->progress += SCROLL_SPEED * deltaTime;
        if (this->progress > this->target) {
            this->progress = this->target;
        }
    }
}

void ProgressBar_render(const ProgressBar *this, const Renderer *renderer) {
    // render border
    Vector2i position = this->position;
    renderer->renderCharAt(renderer, L'╔', &this->color, &position);
    position.x = this->position.x + this->size.x - 1;
    renderer->renderCharAt(renderer, L'╗', &this->color, &position);
    position.y = this->position.y + this->size.y - 1;
    renderer->renderCharAt(renderer, L'╝', &this->color, &position);
    position.x = this->position.x;
    renderer->renderCharAt(renderer, L'╚', &this->color, &position);
    position = this->position;
    for (int i = 0; i < this->size.y - 2; ++i) {
        position.y += 1;
        renderer->renderCharAt(renderer, L'║', &this->color, &position);
        position.x = this->position.x + this->size.x - 1;
        renderer->renderCharAt(renderer, L'║', &this->color, &position);
        position.x = this->position.x;
    }
    position = this->position;
    for (int i = 0; i < this->size.x - 2; ++i) {
        position.x += 1;
        renderer->renderCharAt(renderer, L'═', &this->color, &position);
        position.y = this->position.y + this->size.y - 1;
        renderer->renderCharAt(renderer, L'═', &this->color, &position);
        position.y = this->position.y;
    }

    // render progress
    int progressAt = floor((this->size.x - 2) * this->progress / this->total);
    position.x = this->position.x + 1, position.y = this->position.y + 1;
    for (int j = 0; j <= progressAt; ++j) {
        renderer->renderCharAt(renderer, L'█', &this->color, &position);
        position.x += 1;
    }
}

void ProgressBar_setProgress(ProgressBar *this, const float progress) {
    this->target = progress;
}

void ProgressBar_forceProgress(ProgressBar *this, const float progress) {
    this->target = this->progress = progress;
}

ProgressBar *createProgressBar(Color color, int width, int height, float progress, float total) {
    ProgressBar *bar = (ProgressBar *)malloc(sizeof(ProgressBar));

    bar->update = ProgressBar_update;
    bar->render = ProgressBar_render;
    bar->setProgress = ProgressBar_setProgress;
    bar->forceProgress = ProgressBar_forceProgress;

    bar->position = (Vector2i){0, 0};
    bar->size = (Vector2i){width, height};
    bar->progress = progress;
    bar->total = total;
    bar->follow = NULL;
    bar->color = color;

    return bar;
}

void destroyProgressBar(ProgressBar *bar) {
    free(bar);
}