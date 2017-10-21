
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
        if (!entity->GetComponent<DynamicBody>() && !entity->GetComponent<LinearForce>())
            throw std::runtime_error("missing Dynamic Body or Linear Force component");
        if (!entity->GetComponent<Location>())
            throw std::runtime_error("missing location component");

        if (entity->GetComponent<DynamicBody>()) bodies.push_back(entity);
        if (entity->GetComponent<LinearForce>()) linear_forces.push_back(entity);
    }

    void PhysicsSystem::Update(const sf::Time elapsed) {
        for (auto &entity : bodies) {
            // Get the required components (Location + Dynamic Body)
            auto location = entity->GetComponent<Location>();
            auto body = entity->GetComponent<DynamicBody>()->GetBody();
            auto body_position = cpBodyGetPosition(body);
            auto body_angle = cpBodyGetAngle(body);

            // Set the location (position + rotation) to exactly match the position and rotation of the physical body.
            location->SetPosition(sf::Vector2f(body_position.x, body_position.y));
            location->SetRotation(body_angle * 180.0f / M_PI);
        }
        for (auto &linear_force : linear_forces) {

            // Perform a space query to get all (non-static) shapes that are overlapping the linear force's area.
            cpSpaceShapeQuery(space, linear_force->GetComponent<LinearForce>()->GetShape(), [](cpShape *shape, cpContactPointSet *points, void *linear_force_data){
                // Avoid compiler warning about unused points variable.
                (void)points;

                // Cast the void* user data to an entity pointer. This is used because lambda's with reference captures can't be passed as C function pointers.
                auto linear_force_entity = static_cast<Entity*>(linear_force_data);

                //convert the location's sf::Vector2f to a cpVect
                auto force_origin = [=](sf::Vector2f sf_pos) {
                    return cpv(sf_pos.x, sf_pos.y);
                }(linear_force_entity->GetComponent<Location>()->GetPosition());

                auto force_direction = linear_force_entity->GetComponent<LinearForce>()->GetForce();
                auto strength = linear_force_entity->GetComponent<LinearForce>()->GetStrength();
                auto shape_position = cpBodyGetPosition(cpShapeGetBody(shape));
                auto force = force_direction * std::max(0., (strength - cpvdist(force_origin, shape_position)));

                // Apply a force to each shape overlapping with this linear force shape.
                // Calculate force to be applied by normalizing the sum of the linear forces position, and
                // shapes position, then multiplying by the linear force strength
                cpBodyApplyForceAtWorldPoint(cpShapeGetBody(shape), force, cpBodyGetPosition(cpShapeGetBody(shape)));

                // Pass in a pointer to the linear force
            }, linear_force.get());

        }

        // Update the physical simulation
        cpSpaceStep(space, elapsed.asSeconds());
    }

    cpSpace* PhysicsSystem::GetSpace() {
        return space;
    }

}
