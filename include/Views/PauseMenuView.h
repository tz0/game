#ifndef GAME_PAUSEMENU_H
#define GAME_PAUSEMENU_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u

#include <SFML/Graphics.hpp>

#include "LogicCenter.h"
#include "ResourceManager.h"


namespace tjg {
    class PauseMenuView{
    private:
        ResourceManager &resource_manager;
//        void HandleWindowEvents();
        sf::RenderWindow &window;
        bool running = true;
        sf::Text message;
    public:
        PauseMenuView(ResourceManager &resource_manager, sf::RenderWindow &window);
        void Initialize();
        void Update();
        void Render();
        bool Running();
    };
}
#endif //GAME_PAUSEMENU_H
