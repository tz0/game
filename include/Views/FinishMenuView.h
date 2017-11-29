#ifndef GAME_FINISHMENUVIEW_H
#define GAME_FINISHMENUVIEW_H

#include <SFML/Graphics.hpp>
#include "View.h"

namespace tjg {
    class FinishMenuView : public View {
    private:
        sf::Sprite background_sprite;
        sf::RectangleShape selection_box;
        sf::Vector2f selection_box_position;
        unsigned int selection = 0;
        std::vector<ViewSwitch> options = {};

    public:
        FinishMenuView(sf::RenderWindow &window, ResourceManager &resource_manager, std::shared_ptr<SoundManager> &sound_manager);
        void Initialize();
        void Update();
        void Render();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_FINISHMENUVIEW_H
