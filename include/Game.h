
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <chipmunk.h>

#include "ViewManager.h"
#include "Constants.h"
#include "Level.h"

namespace tjg {

    class Game {
    public:
        Game();
        ~Game();
        void Run();
    private:
        ResourceManager resource_manager;
        LogicCenter logic_center;
        ViewManager view_manager;
        Level level;
        sf::Clock update_clock;
    };
}
#endif //GAME_H
