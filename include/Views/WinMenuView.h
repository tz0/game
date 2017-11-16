#ifndef GAME_WINMENUVIEW_H
#define GAME_WINMENUVIEW_H

#include <SFML/Graphics.hpp>
#include "View.h"

namespace tjg {
    class WinMenuView : public View {
    private:
        sf::Sprite background_sprite;
        sf::RectangleShape selection_box;
        sf::Vector2f selection_box_position;
        unsigned int current_level;
        unsigned int selection = 0;
        std::vector<ViewSwitch> options = {};
    public:
        WinMenuView(sf::RenderWindow &window, ResourceManager &resource_manager, SoundManager &sound_manager);
        void Initialize(unsigned int level_number);
        void Update();
        void Render();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_WINMENUVIEW_H
