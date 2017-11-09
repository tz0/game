#ifndef GAME_MAINMENUVIEW_H
#define GAME_MAINMENUVIEW_H

#include <SFML/Graphics.hpp>
#include "View.h"

namespace tjg {
    class MainMenuView : public View {
    private:
        sf::Text message;
        sf::RectangleShape selection_box;
        sf::Vector2f selection_box_position;
        unsigned int selection = 0;
        std::vector<ViewSwitch> options = {ViewSwitch {State::LEVEL_MENU, 0}, ViewSwitch {State::EXIT, 0}};
    public:
        MainMenuView(ResourceManager &resource_manager, sf::RenderWindow &window);
        void Initialize();
        void Update();
        void Render();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_MAINMENUVIEW_H
