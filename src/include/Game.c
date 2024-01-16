#include "Game.h"

void Game_loop(Game *game) {
    clock_t now = clock();
    while (game->mIsLooping) {
        // Event handling process
        while (bc_kbhit()) {
            int ch = bc_getchar();
            // Handle event
            printf("%d\n", ch);
            if (ch == 'q') {
                game->mIsLooping = false;
            }
        }
        // Update process
        // float deltaTime = (clock() - now) / 1000.f;

        // Render process
    }
}

Game *createGame() {
    Game *game = malloc(sizeof(Game));
    
    // initialize methods
    bc_init();
    game->loop = Game_loop;
    game->mGlobals = malloc(sizeof(Globals));
    game->mIsLooping = true;

    return game;
}

void destroyGame(Game *game) {
    // free game objects
    free(game->mGlobals);

    free(game);
    bc_end();
}