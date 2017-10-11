//
// Created by cullen on 10/10/17.
//

#ifndef GAME_PLAYERCONTROLSYSTEM_H
#define GAME_PLAYERCONTROLSYSTEM_H

#include "System.h"
#include "Components/DynamicBody.h"

#include <chipmunk.h>

namespace tjg {

    class PlayerControlSystem : public System {
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

#endif //GAME_PLAYERCONTROLSYSTEM_H
