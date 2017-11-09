#ifndef GAME_PAUSEMENU_H
#define GAME_PAUSEMENU_H

#include <SFML/Graphics.hpp>
#include "View.h"

namespace tjg {
    class PauseMenuView : public View {
    private:
        sf::Text message;
        sf::RectangleShape selection_box;
        sf::Vector2f selection_box_position;
        unsigned int current_level;
        unsigned int selection = 0;
        std::vector<ViewSwitch> options = {};
    public:
        PauseMenuView(ResourceManager &resource_manager, sf::RenderWindow &window);
        void Initialize(ViewSwitch view_switch);
        void Update();
        void Render();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_PAUSEMENU_H
