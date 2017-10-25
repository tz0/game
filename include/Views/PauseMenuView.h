#ifndef GAME_PAUSEMENU_H
#define GAME_PAUSEMENU_H

#include <SFML/Graphics.hpp>

#include "LogicCenter.h"
#include "ResourceManager.h"


namespace tjg {
    class PauseMenuView{
    private:
        ResourceManager &resource_manager;
        void CheckKeys();
        void HandleWindowEvents();
        sf::RenderWindow window;
        bool running = true;
        sf::Text message;
    public:
        void Initialize();
        void Draw();
    };
}
#endif //GAME_PAUSEMENU_H
