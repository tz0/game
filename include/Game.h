
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <chipmunk.h>
#include <Views/PlayerView.h>

namespace tjg {

    class Game {
    public:
        Game();
        ~Game();
        void Run();
    private:

        ResourceManager resource_manager;
        PlayerView view;
    };
}
#endif //GAME_H
