#ifndef GAME_FAILMENUVIEW_H
#define GAME_FAILMENUVIEW_H

#include <SFML/Graphics.hpp>
#include "View.h"

namespace tjg {
    class FailMenuView : public View {
    private:
        sf::Text message;
        sf::Sprite background_sprite;
        sf::RectangleShape selection_box;
        sf::Vector2f selection_box_position;
        unsigned int current_level;
        unsigned int selection = 0;
        std::vector<ViewSwitch> options = {};
    public:
        FailMenuView(sf::RenderWindow &window, ResourceManager &resource_manager, std::shared_ptr<SoundManager> &sound_manager);
        void Initialize(unsigned int level_number);
        void Update();
        void Render();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_FAILMENUVIEW_H
