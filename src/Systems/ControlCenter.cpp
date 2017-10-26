#include <utility>

#include "Systems/ControlCenter.h"

namespace tjg {

    void ControlCenter::AddEntity(std::shared_ptr<Entity> entity) {
        player_entity = entity;
    }

    void ControlCenter::SetFuelResource(std::shared_ptr<FiniteResource> &fuel_resource) {
        fuel = fuel_resource;
    }

    void ControlCenter::RotateClockwise(const sf::Time &elapsed) {
        if (!fuel->IsDepleted()) {
            // Get body.
            auto body = player_entity->GetComponent<DynamicBody>()->GetBody();

            // Set clockwise torque.
            cpBodySetTorque(body, 250000.f);

            // Expend a small amount of fuel.
            useFuel(elapsed.asSeconds() / 8.f);
        }
    }

    void ControlCenter::RotateCounterClockwise(const sf::Time &elapsed) {
        if (!fuel->IsDepleted()) {
            // Get body.
            auto body = player_entity->GetComponent<DynamicBody>()->GetBody();

            // Set counterclockwise torque.
            cpBodySetTorque(body, -250000.f);

            // Expend a small amount of fuel.
            useFuel(elapsed.asSeconds() / 8.f);
        }
    }

    void ControlCenter::FireJetpack(const sf::Time &elapsed) {
        if (!fuel->IsDepleted()) {
            // Get body.
            auto body = player_entity->GetComponent<DynamicBody>()->GetBody();

            // Apply impulse.
            cpBodyApplyImpulseAtLocalPoint(body, cpv(0, -35), cpv(0, 0));

            // Expend the proper amount of fuel.
            useFuel(elapsed.asSeconds());
        }
    }

    std::shared_ptr<Entity> ControlCenter::GetPlayerEntity() {
        return player_entity;
    }

    void ControlCenter::useFuel(float amount) {
        if (fuel) {
            fuel->ExpendResource(amount);
        }
    }

}
