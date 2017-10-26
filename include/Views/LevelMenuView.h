#ifndef GAME_LEVELMENUVIEW_H
#define GAME_LEVELMENUVIEW_H

#define WINDOW_WIDTH 1280u
#define WINDOW_HEIGHT 720u

#include <SFML/Graphics.hpp>

#include "LogicCenter.h"
#include "ResourceManager.h"
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
        void HandleWindowEvents(sf::Event event) override;
    };
}

#endif //GAME_LEVELMENUVIEW_H
