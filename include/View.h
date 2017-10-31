
#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "ResourceManager.h"

#include "Level.h"

namespace tjg {
    class View {

    protected:
        sf::RenderWindow &window;
        ResourceManager &resource_manager;

    public:
        View(sf::RenderWindow &window, ResourceManager &resourceManager) :
                window(window),
                resource_manager(resourceManager){};

        virtual ViewSwitch HandleWindowEvents(sf::Event event) = 0;
      
        //TODO(Tao): move this level parameter to LogicCenter::Initialize
        virtual void Initialize(Level &level) = 0;
    };
}
#endif //GAME_VIEW_H
