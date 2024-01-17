#include "include/Game.c"

int main(int argc, char *argv[]) {
    Game *game = createGame();
    game->loop(game);
    destroyGame(game);
    return EXIT_SUCCESS;
}