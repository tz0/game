
#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/Graphics.hpp>

#include "Systems/SoundManager.h"
#include "Constants.h"
#include "ResourceManager.h"

namespace tjg {
    class View {

    protected:
        sf::RenderWindow &window;
        ResourceManager &resource_manager;
        SoundManager &sound_manager;

    public:
        View(sf::RenderWindow &window, ResourceManager &resource_manager, SoundManager &sound_manager) :
                window(window),
                resource_manager(resource_manager),
                sound_manager(sound_manager){};

        virtual ViewSwitch HandleWindowEvents(sf::Event event) = 0;
    };
}
#endif //GAME_VIEW_H
