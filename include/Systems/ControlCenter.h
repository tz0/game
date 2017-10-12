
#ifndef GAME_CONTROLCENTER_H
#define GAME_CONTROLCENTER_H

#include <chipmunk.h>

#include "System.h"
#include "Components/DynamicBody.h"

namespace tjg {

    class ControlCenter : public System {
    private:
        std::shared_ptr<Entity> player_entity;
    public:
        // Override System virtual methods
        void AddEntity(std::shared_ptr<Entity> entity) override;
        // Player controls.
        void RotateClockwise();
        void RotateCounterClockwise();
        void FireJetpack();
        // Accessor methods
        std::shared_ptr<Entity> GetPlayerEntity();
    };

}

#endif //GAME_CONTROLCENTER_H
