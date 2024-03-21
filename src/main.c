#include "include/Game.c"

int main(int argc, char *argv[]) {
    // Generate save file path
    realpath(argv[0], savePath);
    int len = strlen(savePath), pos = -1;
    for (int i = len - 1; i >= 0; --i) {
        if (savePath[i] == '/' || savePath[i] == '\\') {
            pos = i;
            break;
        }
    }
    savePath[pos + 1] = '.';
    savePath[pos + 2] = 's';
    savePath[pos + 3] = 'a';
    savePath[pos + 4] = 'v';
    savePath[pos + 5] = 'e';
    savePath[pos + 6] = '\0';

    Game *game = createGame();
    game->loop(game);
    destroyGame(game);
    return EXIT_SUCCESS;
}
