
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
        if (!entity->GetComponent<DynamicBody>())
            throw std::runtime_error("missing dynamic body component");
        if (!entity->GetComponent<Location>())
            throw std::runtime_error("missing location component");

        entities.push_back(entity);
    }

    void PhysicsSystem::Update(const sf::Time elapsed) {
        for (auto entity : entities) {
            auto body = entity->GetComponent<DynamicBody>()->GetBody();
            auto bodyPosition = cpBodyGetPosition(body);
            auto location = entity->GetComponent<Location>();
            location->setPosition(sf::Vector2f(bodyPosition.x, bodyPosition.y));

            auto bodyAngle = cpBodyGetAngle(body);
            location->setRotation(bodyAngle * 180.0f / M_PI);
        }
        cpSpaceStep(space, elapsed.asSeconds() * 2);
    }

    cpSpace* PhysicsSystem::GetSpace() {
        return space;
    }

}
