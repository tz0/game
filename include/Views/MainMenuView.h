#ifndef GAME_MAINMENUVIEW_H
#define GAME_MAINMENUVIEW_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u

#include <SFML/Graphics.hpp>

#include "LogicCenter.h"
#include "ResourceManager.h"
#include "View.h"

namespace tjg {
        class MainMenuView {
        private:
            ResourceManager &resource_manager;
            sf::RenderWindow &window;
            sf::Text message;
        public:
            MainMenuView(ResourceManager &resource_manager, sf::RenderWindow &window);
            void Initialize();
            void Update();
            void Render();
        };
}
#endif //GAME_MAINMENUVIEW_H
