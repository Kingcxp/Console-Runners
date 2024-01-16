#include "Game.h"

void Game_loop(Game *game) {
    clock_t now = clock();
    while (game->isLooping) {
        // Event handling process
        while (bc_kbhit()) {
            int ch = bc_getchar();
            // Handle event
            printf("%d\n", ch);
            if (ch == 'q') {
                game->isLooping = false;
            }
        }
        // Update process
        float deltaTime = (clock() - now) / 1000.f;

        // Render process
    }
}

Game *createGame() {
    Game *game = (Game *)malloc(sizeof(Game));
    
    // initialize methods
    bc_init();
    srand(time(NULL));
    setlocale(LC_ALL, "en_US.UTF-8");
    game->loop = Game_loop;
    game->globals = (Globals *)malloc(sizeof(Globals));
    game->isLooping = true;

    return game;
}

void destroyGame(Game *game) {
    // free game objects
    bc_end();
    setlocale(LC_ALL, "");
    free(game->globals);

    free(game);
}