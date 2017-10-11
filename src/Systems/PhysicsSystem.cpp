
#include <Components/DynamicBody.h>
#include "Systems/PhysicsSystem.h"

namespace tjg {

    PhysicsSystem::PhysicsSystem() : space(cpSpaceNew()) {
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
            entity->GetComponent<DynamicBody>()->Update();
        }
        cpSpaceStep(space, elapsed.asSeconds() * 2);
    }

    cpSpace* PhysicsSystem::GetSpace() {
        return space;
    }

}
