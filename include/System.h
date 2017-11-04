
#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include <map>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Components/Sprite.h"
#include "Components/Location.h"

namespace tjg {

    class System {
    public:
        virtual void AddEntity(std::shared_ptr<Entity> entity) = 0;
    };

}

#endif //GAME_SYSTEM_H
