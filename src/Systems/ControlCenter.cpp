#include <utility>

#include "Systems/ControlCenter.h"

namespace tjg {

    void ControlCenter::AddEntity(std::shared_ptr<Entity> entity) {
        player_entity = entity;
    }

    void ControlCenter::SetFuelResource(std::shared_ptr<FiniteResource> &fuel_resource) {
        fuel = fuel_resource;
    }

    void ControlCenter::RotateClockwise() {
        // Get body.
        auto body = player_entity->GetComponent<DynamicBody>()->GetBody();
        // Set clockwise torque.
        cpBodySetTorque(body, 250000.f);
    }

    void ControlCenter::RotateCounterClockwise() {
        // Get body.
        auto body = player_entity->GetComponent<DynamicBody>()->GetBody();
        // Set counterclockwise torque.
        cpBodySetTorque(body, -250000.f);
    }

    void ControlCenter::FireJetpack(const sf::Time &elapsed) {
        // Get body.
        auto body = player_entity->GetComponent<DynamicBody>()->GetBody();

        // Apply impulse.
        cpBodyApplyImpulseAtLocalPoint(body, cpv(0, -40), cpv(0, 0));

        // Expend the proper amount of fuel.
        if (fuel) {
            fuel->ExpendResource(elapsed.asSeconds());
        }
    }

    std::shared_ptr<Entity> ControlCenter::GetPlayerEntity() {
        return player_entity;
    }

}
