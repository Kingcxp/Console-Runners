#ifndef GAME
#define GAME


#include "Globals.h"

#define RENDER_WIDTH    19
#define RENDER_HEIGHT   24

typedef struct Game {
    // Methods

    void        (*loop)(Game *this);

    // Variables

    Globals     globals;
    bool        isLooping;
} Game;


void Game_loop(Game *this) {
    clock_t now = clock();
    while (this->isLooping) {
        // Event handling process
        while (bc_kbhit()) {
            int ch = bc_getchar();
            // Handle event
            printf("%d\n", ch);
            if (ch == 'q') {
                this->isLooping = false;
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
    game->globals.renderer = createRenderer(0, 0, RENDER_WIDTH, RENDER_HEIGHT);
    game->isLooping = true;

    return game;
}

void destroyGame(Game *game) {
    // free game objects
    bc_end();
    setlocale(LC_ALL, "");
    destroyRenderer(game->globals.renderer);

    free(game);
}

#endif // GAME