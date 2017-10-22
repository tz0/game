
#include "Systems/PhysicsSystem.h"

namespace tjg {

    PhysicsSystem::PhysicsSystem(EventManager &event_manager) :
            space(cpSpaceNew()),
            event_manager(event_manager),
            collision_center(space)
    {
        // Set zero gravity
        cpSpaceSetGravity(space, cpvzero);

        // Set some friction
        cpSpaceSetDamping(space, 0.9);

        // Create a collision center handler that will fire an event when TECH17 hits a wall.
        collision_center.AddHandler(
            CollisionGroup::TECH17,
            CollisionGroup::WALL,
            [&](cpArbiter *arb, cpSpace *space) -> cpBool {
                (void)arb;
                (void)space;
                event_manager.Fire<HitWall>();
                return cpTrue;
            });

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

            // Check if the entity has a sensor shape
            auto sensor = entity->GetComponent<SensorShape>();
            if (sensor) {
                sensor->Query(space);
            }

        }

        // Update the physical simulation
        cpSpaceStep(space, elapsed.asSeconds());
    }

    cpSpace* PhysicsSystem::GetSpace() {
        return space;
    }

}
