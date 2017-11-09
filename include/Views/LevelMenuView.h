#ifndef GAME_LEVELMENUVIEW_H
#define GAME_LEVELMENUVIEW_H

#include <SFML/Graphics.hpp>
#include "View.h"

namespace tjg {
    class LevelMenuView : public View {
    private:
        sf::Text message;
        sf::RectangleShape selection_box;
        sf::Vector2f selection_box_position;
        unsigned int selection = 1;
        unsigned int unlocked = 2;
    public:
        LevelMenuView(ResourceManager &resource_manager, sf::RenderWindow &window);
        void Initialize();
        void Update();
        void Render();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_LEVELMENUVIEW_H
