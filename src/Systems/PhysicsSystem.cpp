
#include <iostream>
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
        if (!entity->GetComponent<DynamicBody>() && !entity->GetComponent<SensorShape>())
            throw std::runtime_error("missing Dynamic Body or Sensor Shape component");
        if (!entity->GetComponent<Location>())
            throw std::runtime_error("missing location component");

        entities.push_back(entity);
        //if (entity->GetComponent<DynamicBody>()) bodies.push_back(entity);
        //if (entity->GetComponent<LinearForce>()) linear_forces.push_back(entity);
    }

    void PhysicsSystem::Update(const sf::Time elapsed) {
        for (auto &entity : entities) {
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

            auto sensor = entity->GetComponent<SensorShape>();
            if (sensor) {
                cpSpaceShapeQuery(space, sensor->GetShape(), sensor->GetCallback(), entity.get());
            }

        }

        // Update the physical simulation
        cpSpaceStep(space, elapsed.asSeconds());
    }

    cpSpace* PhysicsSystem::GetSpace() {
        return space;
    }

}
