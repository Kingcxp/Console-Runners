#include "Game.h"

void Game_loop(Game *this) {
    clock_t now = clock();
    this->stack->pushState(this->stack, GameState);

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
    game->stack = createStateStack(&game->globals);

    return game;
}

void destroyGame(Game *game) {
    // free game objects
    endConsole();
    setlocale(LC_ALL, "");
    destroyStateStack(game->stack);
    destroyRenderer(game->globals.renderer);

    free(game);
}