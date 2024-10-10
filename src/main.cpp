#include <game.hpp>

int main(int _argc, char **_argv) {
    Game game;
    game.Run();
    game.Cleanup();
    return 0;
}