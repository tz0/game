
#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/Graphics.hpp>

#include "ResourceManager.h"

namespace tjg {
    class View {

    protected:
        sf::RenderWindow &window;
        ResourceManager &resource_manager;

    public:
        View(sf::RenderWindow &window, ResourceManager &resourceManager) :
                window(window),
                resource_manager(resourceManager){};
        virtual void Initialize() = 0;
        virtual void HandleWindowEvents(sf::Event event) = 0;
    };
}
#endif //GAME_VIEW_H
