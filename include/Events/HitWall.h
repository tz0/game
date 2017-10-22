#ifndef GAME_HITWALL_H
#define GAME_HITWALL_H

#include "Event.h"

namespace tjg {
    class HitWall : public Event {
    private:
        //  - time elapsed
    public:
        explicit HitWall();
    };
}

#endif //GAME_HITWALL_H
