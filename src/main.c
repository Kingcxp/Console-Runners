#include "include/Game.c"

int main(int argc, char *argv[]) {
    Game *game = createGame();
    if (game == NULL) {
        printf("Game failed to initialize!\n");
        return EXIT_FAILURE;
    }
    game->loop(game);
    destroyGame(game);
    return EXIT_SUCCESS;
}