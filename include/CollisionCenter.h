
#ifndef GAME_COLLISIONCENTER_H
#define GAME_COLLISIONCENTER_H

#include <functional>
#include <vector>

#include <chipmunk.h>


namespace tjg {

    // Used to identify collision types involved in a collision
    enum class CollisionGroup : cpCollisionType {
        DEFAULT = 0,
        TECH17,
        WALL,
        EXIT
    };

    class CollisionCenter {
    private:
        cpSpace *space;
        std::vector<std::pair<cpCollisionHandler *, std::function<cpBool(cpArbiter *arb, cpSpace *space)>>> handlers;

    public:
        explicit CollisionCenter(cpSpace* space) : space(space) {};
        void AddHandler(CollisionGroup, CollisionGroup, std::function<cpBool(cpArbiter *arb, cpSpace *space)> callback);
    };

}

#endif //GAME_COLLISIONCENTER_H
