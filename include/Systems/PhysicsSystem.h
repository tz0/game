
#ifndef GAME_PHYSICSSYSTEM_H
#define GAME_PHYSICSSYSTEM_H

// Make M_PI work on Windows.
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include <chipmunk.h>
#include <SFML/System/Time.hpp>

#include "CollisionCenter.h"

#include "Components/DynamicBody.h"
#include "Components/LinearForce.h"
#include "Components/SensorShape.h"

#include "EventManager.h"
#include "Events/HitLethalWall.h"

#include "System.h"

namespace tjg {

    class PhysicsSystem : public System {
    private:
        cpSpace* space;

        std::vector<std::shared_ptr<Entity>> entities;

        void InitializeSpace();

    public:
        // Constructor
        PhysicsSystem();
        // Destructor
        ~PhysicsSystem();

        /**
         * Add an entity to be simulated. Requires DynamicBody and Location components to be present
         * @param entity
         */
        void AddEntity(std::shared_ptr<Entity> entity) override;

        /**
         * @return a pointer to the system's Chipmunk2D space object
         */
        cpSpace* GetSpace();

        /**
         * Updates the positions of all entities in the system, and step forward the physical simulation
         */
        void Update(sf::Time elapsed);

        /**
         * Clear all entities
         */
        void Reset();

    };
}

#endif //GAME_PHYSICSSYSTEM_H
