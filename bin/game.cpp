

#include <cstdlib>

#include "Game.h"
#include "LevelReader.h"

// Entry point
int main()
{
    tjg::Game game;
    game.Run();
    tjg::LevelReader lr("data");
    lr.JsonTest();

    return EXIT_SUCCESS;
}

