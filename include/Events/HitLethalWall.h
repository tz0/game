#ifndef GAME_HITWALL_H
#define GAME_HITWALL_H

#include "Event.h"

namespace tjg {
    class HitLethalWall : public Event {
    private:
        //  - time elapsed
    public:
        explicit HitLethalWall() = default;
    };
}

#endif //GAME_HITWALL_H
