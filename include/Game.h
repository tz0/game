
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <chipmunk.h>
#include <Views/PlayerView.h>
#include "StateManager.h"

namespace tjg {

    class Game {
    public:
        Game();
        ~Game();
        void Run();
    private:
        ResourceManager resource_manager;
        LogicCenter logic_center;
//        PlayerView view;
        StateManager state_manager;

        sf::Clock update_clock;
    };
}
#endif //GAME_H
