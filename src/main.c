#include "include/Game.c"

#if defined(_WIN32) || defined(_WIN64)
    #include <KnownFolders.h>
    #include <shlobj.h>
#elif defined(__linux__)
    #include <pwd.h>
    #include <sys/types.h>
    #include <unistd.h>
#elif defined(__APPLE__)
    #include <unistd.h>
#endif

int main(int argc, char *argv[]) {

    // Generate save file path
    const char *filename = "/.console-runner.save";

#if defined(_WIN32) || defined(_WIN64)
    CoInitialize(NULL);
    PWSTR path = NULL;
    if (SUCCEEDED(SHGetKnownFolderPath(&FOLDERID_Documents, 0, NULL, &path))) {
        wcstombs(savePath, path, sizeof(savePath));
        CoTaskMemFree(path);
    } else {
        printf("Failed to retrieve Documents folder path!\n");
        return EXIT_FAILURE;
    }
#elif defined(__linux__)
    const char *homeDir = getenv("HOME");
    if (!homeDir) {
        uid_t uid = geteuid();
        struct passwd *pw = getpwuid(uid);
        if (pw) {
            homeDir = pw->pw_dir;
        }
    }
    if (!homeDir) {
        printf("Failed to retrieve home directory path!\n");
        return EXIT_FAILURE;
    }
    strncpy(savePath, homeDir, sizeof(savePath));
#elif defined(__APPLE__)
    const char *homeDir = getenv("HOME");
    if (!homeDir) {
        uid_t uid = getuid();
        struct passwd *pw = getpwuid(uid);
        if (pw) {
            homeDir = pw->pw_dir;
        }
    }
    if (!homeDir) {
        printf("Failed to retrieve home directory path!\n");
        return EXIT_FAILURE;
    }
#endif
    strncat(savePath, filename, sizeof(savePath) - strlen(savePath) * sizeof(char) - 1);

    Game *game = createGame();
    game->loop(game);
    destroyGame(game);
    return EXIT_SUCCESS;
}
