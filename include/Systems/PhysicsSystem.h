
#ifndef GAME_PHYSICSSYSTEM_H
#define GAME_PHYSICSSYSTEM_H

#include <chipmunk.h>
#include <SFML/System/Time.hpp>

#include "System.h"

namespace tjg {
    class PhysicsSystem : public System {
    private:
        cpSpace* space;
        std::vector<std::shared_ptr<Entity>> entities;
    public:
        PhysicsSystem();
        ~PhysicsSystem();
        void AddEntity(std::shared_ptr<Entity> entity);
        cpSpace* GetSpace();
        void Update(const sf::Time elapsed);
    };
}

#endif //GAME_PHYSICSSYSTEM_H
