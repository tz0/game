#ifndef GAME_PAUSEMENU_H
#define GAME_PAUSEMENU_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u

#include <SFML/Graphics.hpp>

#include "View.h"

namespace tjg {
    class PauseMenuView : public View {
    private:
        sf::Text message;
    public:
        PauseMenuView(ResourceManager &resource_manager, sf::RenderWindow &window);
        void Initialize() override;
        void Initialize(State state);
        void Update();
        void Render();
        ViewSwitch HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_PAUSEMENU_H
