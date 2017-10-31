#ifndef GAME_LEVELMENUVIEW_H
#define GAME_LEVELMENUVIEW_H

#include <SFML/Graphics.hpp>
#include "View.h"

namespace tjg {
    class LevelMenuView : public View {
    private:
        sf::Text message;
    public:
        LevelMenuView(ResourceManager &resource_manager, sf::RenderWindow &window);
        void Initialize() override;
        void Update();
        void Render();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_LEVELMENUVIEW_H
