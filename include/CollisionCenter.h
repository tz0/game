
#ifndef GAME_COLLISIONCENTER_H
#define GAME_COLLISIONCENTER_H

#include <iostream>
#include <chipmunk.h>
#include <functional>
#include <unordered_map>

namespace tjg {

    // Used to identify collision types involved in a collision
    enum class CollisionGroup : cpCollisionType {
        DEFAULT = 0,
        TECH17,
        WALL,
        LETHAL,
        EXIT
    };

    class CollisionCenter {
    private:
        cpSpace *space;
        std::unordered_map<cpCollisionHandler *, std::function<void(cpArbiter *arb, cpSpace *space)>> callbacks;

    public:
        explicit CollisionCenter(cpSpace* space) : space(space) {};
        void AddHandler(CollisionGroup, CollisionGroup, std::function<void(cpArbiter *arb, cpSpace *space)> callback);
        void Reset(cpSpace* space);
    };

}

#endif //GAME_COLLISIONCENTER_H
