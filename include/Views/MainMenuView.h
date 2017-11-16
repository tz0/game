#ifndef GAME_MAINMENUVIEW_H
#define GAME_MAINMENUVIEW_H

#include <SFML/Graphics.hpp>
#include <LogicCenter.h>
#include "View.h"

namespace tjg {
    class MainMenuView : public View {
    private:
        sf::Sprite background_sprite;
        sf::Sprite animation_sprite;
        sf::RectangleShape selection_box;
        sf::Vector2f selection_box_position;
        unsigned int selection = 0;
        std::vector<ViewSwitch> options = {ViewSwitch {State::LEVEL_MENU, 0}, ViewSwitch {State::EXIT, 0}};

    public:
        MainMenuView(sf::RenderWindow &window, ResourceManager &resource_manager, SoundManager &sound_manager);
        void Initialize();
        void Update();
        void Render();
        void RenderAnimation();  //cut animation between menus
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_MAINMENUVIEW_H
