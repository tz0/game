#ifndef GAME_PAUSEMENU_H
#define GAME_PAUSEMENU_H

#include <SFML/Graphics.hpp>
#include "View.h"

namespace tjg {
    class PauseMenuView : public View {
    private:
        sf::Text message;
        unsigned int current_level;
    public:
        PauseMenuView(ResourceManager &resource_manager, sf::RenderWindow &window);
        void Initialize(ViewSwitch view_switch);
        void Update();
        void Render();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_PAUSEMENU_H
