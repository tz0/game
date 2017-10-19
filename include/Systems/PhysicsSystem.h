
#ifndef GAME_PHYSICSSYSTEM_H
#define GAME_PHYSICSSYSTEM_H

#include <chipmunk.h>
#include <SFML/System/Time.hpp>

#include "Components/DynamicBody.h"
#include "Components/LinearForce.h"
#include "System.h"

namespace tjg {
    class PhysicsSystem : public System {
    private:
        cpSpace* space;
        std::vector<std::shared_ptr<Entity>> bodies;
        std::vector<std::shared_ptr<Entity>> linear_forces;
    public:
        // Constructor
        PhysicsSystem();
        // Destructor
        ~PhysicsSystem();

        /**
         * Add an entity to be simulated. Requires DynamicBody and Location components to be present
         * @param entity
         */
        void AddEntity(std::shared_ptr<Entity> entity);

        /**
         * @return a pointer to the system's Chipmunk2D space object
         */
        cpSpace* GetSpace();

        /**
         * Updates the positions of all entities in the system, and step forward the physical simulation
         */
        void Update(sf::Time elapsed);
    };
}

#endif //GAME_PHYSICSSYSTEM_H
