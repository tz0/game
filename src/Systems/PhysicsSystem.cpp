
#include <Components/DynamicBody.h>
#include "Systems/PhysicsSystem.h"

namespace tjg {

    PhysicsSystem::PhysicsSystem() : space(cpSpaceNew()) {
        // Set zero gravity
        cpSpaceSetGravity(space, cpvzero);
    }

    PhysicsSystem::~PhysicsSystem() {
        // Free all memory used by Chipmunk.
        cpSpaceFree(space);
    }

    void PhysicsSystem::AddEntity(std::shared_ptr<Entity> entity) {
        // Check for required components (Location + Dynamic Body)
        if (!entity->GetComponent<DynamicBody>())
            throw std::runtime_error("missing dynamic body component");
        if (!entity->GetComponent<Location>())
            throw std::runtime_error("missing location component");

        entities.push_back(entity);
    }

    void PhysicsSystem::Update(const sf::Time elapsed) {
        for (auto entity : entities) {
            // Get the required components (Location + Dynamic Body)
            auto location = entity->GetComponent<Location>();
            auto body = entity->GetComponent<DynamicBody>()->GetBody();
            auto bodyPosition = cpBodyGetPosition(body);
            auto bodyAngle = cpBodyGetAngle(body);

            // Set the location (position + rotation) to exactly match the position and rotation of the physical body.
            location->setPosition(sf::Vector2f(bodyPosition.x, bodyPosition.y));
            location->setRotation(bodyAngle * 180.0f / M_PI);
        }

        // Update the physical simulation
        cpSpaceStep(space, elapsed.asSeconds());
    }

    cpSpace* PhysicsSystem::GetSpace() {
        return space;
    }

}
