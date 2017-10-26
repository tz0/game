#ifndef GAME_TIMEEXPIRED_H
#define GAME_TIMEEXPIRED_H

#include "Event.h"

namespace tjg {
    class OxygenExpired : public Event {
           
    public:
        explicit OxygenExpired();
        // trigger intermediate menu
    };
}

#endif //GAME_TIMEEXPIRED_H
