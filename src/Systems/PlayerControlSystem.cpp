#include "Systems/PlayerControlSystem.h"

namespace tjg {

    void PlayerControlSystem::AddEntity(std::shared_ptr<Entity> entity) {
        player_entity = entity;
    }

    void PlayerControlSystem::RotateClockwise() {
        auto body = player_entity->GetComponent<DynamicBody>()->GetBody();
        cpBodySetAngularVelocity(body, 0.75);
    }

    void PlayerControlSystem::RotateCounterClockwise() {
        auto body = player_entity->GetComponent<DynamicBody>()->GetBody();
        cpBodySetAngularVelocity(body, -0.75);
    }

    void PlayerControlSystem::FireJetpack() {
        auto body = player_entity->GetComponent<DynamicBody>()->GetBody();
        cpBodyApplyImpulseAtLocalPoint(body, cpv(0, -7.5), cpv(0, 0));
    }

    std::shared_ptr<Entity> PlayerControlSystem::GetPlayerEntity() {
        return player_entity;
    }

}
