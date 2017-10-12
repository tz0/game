#include "Systems/ControlCenter.h"

namespace tjg {

    void ControlCenter::AddEntity(std::shared_ptr<Entity> entity) {
        player_entity = entity;
    }

    void ControlCenter::RotateClockwise() {
        auto body = player_entity->GetComponent<DynamicBody>()->GetBody();
        cpBodySetTorque(body, 30000.f);
    }

    void ControlCenter::RotateCounterClockwise() {
        auto body = player_entity->GetComponent<DynamicBody>()->GetBody();
        cpBodySetTorque(body, -30000.f);
    }

    void ControlCenter::FireJetpack() {
        auto body = player_entity->GetComponent<DynamicBody>()->GetBody();
        cpBodyApplyImpulseAtLocalPoint(body, cpv(0, -7.5), cpv(0, 0));
    }

    std::shared_ptr<Entity> ControlCenter::GetPlayerEntity() {
        return player_entity;
    }

}
