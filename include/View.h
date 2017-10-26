
#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/Graphics.hpp>

#include "ResourceManager.h"
//#include "LogicCenter.h"

namespace tjg {
    class View {

    protected:
//        LogicCenter &logic_center;
        sf::RenderWindow &window;
        ResourceManager resource_manager;

    public:
//        View(LogicCenter &logic_center) : logic_center(logic_center) {};
        View(sf::RenderWindow &window, ResourceManager &resourceManager) :
                window(window),
                resource_manager(resourceManager){};
        virtual void Initialize() = 0;

        /**
         * @return whether the view is still running
         */
//        virtual bool Running() = 0;
    };
}
#endif //GAME_VIEW_H
