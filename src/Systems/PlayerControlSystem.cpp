#include "Systems/PlayerControlSystem.h"

namespace tjg {

    void PlayerControlSystem::AddEntity(std::shared_ptr<Entity> entity) {
        player_entity = entity;
    }

    void PlayerControlSystem::rotateClockwise() {
        auto body = player_entity->GetComponent<DynamicBody>()->GetBody();
        cpBodySetAngularVelocity(body, 0.75f);
    }

    void PlayerControlSystem::rotateCounterclockwise() {
        auto body = player_entity->GetComponent<DynamicBody>()->GetBody();
        cpBodySetAngularVelocity(body, -0.75f);
    }

    void PlayerControlSystem::jetpack() {
        auto body = player_entity->GetComponent<DynamicBody>()->GetBody();
        cpBodyApplyImpulseAtLocalPoint(body, cpv(0, -0.35f), cpv(0, 0));
    }

}
