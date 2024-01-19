#include "Game.h"

void renderBorder(const Renderer *renderer) {
    Vector2i position;
    position.x = 0, position.y = 0;
    for (int i = 1; i < RENDER_WIDTH; ++i) {
        renderer->renderCharAt(renderer, L'─', NULL, &position);
        position.y = RENDER_HEIGHT - 1;
        renderer->renderCharAt(renderer, L'─', NULL, &position);
        position.y = 0;
        position.x++;
    }
    position.x = 0;
    for (int i = 1; i < RENDER_HEIGHT; ++i) {
        renderer->renderCharAt(renderer, L'│', NULL, &position);
        position.x = RENDER_WIDTH - 1;
        renderer->renderCharAt(renderer, L'│', NULL, &position);
        position.x = 0;
        position.y++;
    }
    position.y = 0;
    renderer->renderCharAt(renderer, L'┌', NULL, &position);
    position.y = RENDER_HEIGHT - 1;
    renderer->renderCharAt(renderer, L'└', NULL, &position);
    position.x = RENDER_WIDTH - 1;
    renderer->renderCharAt(renderer, L'┘', NULL, &position);
    position.y = 0;
    renderer->renderCharAt(renderer, L'┐', NULL, &position);
    position.x = (RENDER_WIDTH >> 1) - (wcslen(TITLE) >> 1);
    Color color = Color_Yellow;
    renderer->renderStringAt(renderer, TITLE, &color, &position, true);
    position.y = RENDER_HEIGHT - 1;
    position.x = (RENDER_WIDTH >> 1) - (wcslen(COPYRIGHT) >> 1);
    renderer->renderStringAt(renderer, COPYRIGHT, &color, &position, true);
}

void Game_loop(Game *this) {
    clock_t now = clock();
    this->stack->pushState(this->stack, MenuState);

    while (!this->stack->isEmpty(this->stack)) {
        // Event handling process
        int ch = 0;
        while (keyboardHit()) {
            ch = termGetch();
            // Handle event
            this->stack->handleEvent(this->stack, ch);
        }
        // Update process
        float deltaTime = (clock() - now) / 1000.f;
        now = clock();
        this->stack->update(this->stack, deltaTime);

        // Render process
        this->globals.renderer->clear(this->globals.renderer);
        renderBorder(this->globals.renderer);
        this->stack->render(this->stack, this->globals.renderer);
        this->globals.renderer->display(this->globals.renderer);
    }
}

Game *createGame() {
    Game *game = (Game *)malloc(sizeof(Game));
    
    // initialize methods
    initConsole();
    srand(time(NULL));
    game->loop = Game_loop;
    game->globals.renderer = createRenderer(0, 0, RENDER_WIDTH, RENDER_HEIGHT);
    game->globals.scoreBoard = createScoreBoard();
    game->stack = createStateStack(&game->globals);

    return game;
}

void destroyGame(Game *game) {
    // free game objects
    endConsole();
    setlocale(LC_ALL, "");
    destroyStateStack(game->stack);
    destroyRenderer(game->globals.renderer);
    destroyScoreBoard(game->globals.scoreBoard);

    free(game);
}