#ifndef GAME_MAINMENUVIEW_H
#define GAME_MAINMENUVIEW_H

#include <SFML/Graphics.hpp>
#include <LogicCenter.h>
#include "View.h"

namespace tjg {
    class MainMenuView : public View {
    private:
        sf::Text message;
        sf::Sprite background_sprite;
        sf::RectangleShape selection_box;
        sf::Vector2f selection_box_position;
        unsigned int selection = 0;
        std::vector<ViewSwitch> options = {ViewSwitch {State::LEVEL_MENU, 0}, ViewSwitch {State::EXIT, 0}};

        LogicCenter &logic_center;
        sf::View camera;

        // Sprite render systems.
        SpriteRenderSystem main_render_system;

    public:
        MainMenuView(ResourceManager &resource_manager, sf::RenderWindow &window,  LogicCenter &logic_center);
        void Initialize();
        void Update();
        void Render();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_MAINMENUVIEW_H
