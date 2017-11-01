
#include "Systems/PhysicsSystem.h"

namespace tjg {

    PhysicsSystem::PhysicsSystem() :
            space(cpSpaceNew())
    {
        // Set zero gravity
        cpSpaceSetGravity(space, cpvzero);

        // Set some friction
        cpSpaceSetDamping(space, 0.7);

    }

    PhysicsSystem::~PhysicsSystem() {
        // Free all memory used by Chipmunk.
        cpSpaceFree(space);
    }

    void PhysicsSystem::AddEntity(std::shared_ptr<Entity> entity) {
        // Check for required components (Location + Dynamic Body / Sensor Shape)
        if (!entity->GetComponent<DynamicBody>() && !entity->GetComponent<SensorShape>())
            throw std::runtime_error("missing Dynamic Body or Sensor Shape component");
        if (!entity->GetComponent<Location>())
            throw std::runtime_error("missing location component");

        entities.push_back(entity);
    }

    void PhysicsSystem::Update(const sf::Time elapsed) {
        // Traverse entities, and delete the ones that have been flagged for removal.
        entities.erase(
                std::remove_if(
                        entities.begin(),
                        entities.end(),
                        [&](std::shared_ptr<Entity> entity) {

                            if (entity->IsFlaggedForRemoval())
                                return true;

                            // Get the required components (Location + Dynamic Body)
                            auto body_component = entity->GetComponent<DynamicBody>();
                            if (body_component) {
                                auto body = body_component->GetBody();
                                auto location = entity->GetComponent<Location>();

                                auto body_position = cpBodyGetPosition(body);
                                auto body_angle = cpBodyGetAngle(body);

                                // Set the location (position + rotation) to exactly match the position and rotation of the physical body.
                                location->SetPosition(sf::Vector2f(body_position.x, body_position.y));
                                location->SetRotation(body_angle * 180.0f / M_PI);
                            }

                            // Check if the entity has a sensor shape
                            auto sensor = entity->GetComponent<SensorShape>();
                            if (sensor) {
                                sensor->Query(space);
                            }

                            return false;
                        }),
                entities.end()
        );

        // Update the physical simulation
        cpSpaceStep(space, elapsed.asSeconds());
    }

    cpSpace* PhysicsSystem::GetSpace() {
        return space;
    }

    void PhysicsSystem::Reset() {
        entities.clear();
        cpSpaceFree(space);
        space = cpSpaceNew();
        // Set zero gravity
        cpSpaceSetGravity(space, cpvzero);
        // Set some friction
        cpSpaceSetDamping(space, 0.7);
    }

}
