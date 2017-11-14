#ifndef GAME_LEVELMENUVIEW_H
#define GAME_LEVELMENUVIEW_H

#include <SFML/Graphics.hpp>
#include "View.h"

namespace tjg {
    class LevelMenuView : public View {
    private:
        sf::Text level_1, level_2, level_3, level_4, level_5, level_6, level_7, level_8, level_9, level_10, level_11, level_12;
        sf::Sprite background_sprite;
        sf::Sprite animation_sprite;
        std::vector<sf::Text *> menu = {&level_1, &level_2, &level_3, &level_4, &level_5, &level_6, &level_7, &level_8, &level_9, &level_10, &level_11, &level_12};
        unsigned int selection = 1;
        unsigned int unlocked_;
    public:
        LevelMenuView(ResourceManager &resource_manager, sf::RenderWindow &window);
        void Initialize(unsigned int unlocked);
        void Update();
        void Render();
        void RenderAnimation();  //cut animation between menus
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_LEVELMENUVIEW_H
