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
        // TODO: Overrride AddEntity
        void AddEntity(std::shared_ptr<Entity> entity) override;
        // Player controls.
        void rotateClockwise();
        void rotateCounterclockwise();
        void jetpack();
    };

}

#endif //GAME_PLAYERCONTROLSYSTEM_H
