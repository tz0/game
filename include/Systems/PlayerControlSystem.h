//
// Created by cullen on 10/10/17.
//

#ifndef GAME_PLAYERCONTROLSYSTEM_H
#define GAME_PLAYERCONTROLSYSTEM_H

#include <System.h>

namespace tjg {

    class PlayerControlSystem : public System {
    public:
        // TODO: Overrride AddEntity
        // Player controls.
        void torqueClockwise();
        void torqueCounterclockwise();
        void jetpack();
    };

}

#endif //GAME_PLAYERCONTROLSYSTEM_H
