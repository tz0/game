#ifndef GAME_TIMEEXPIRED_H
#define GAME_TIMEEXPIRED_H

#include "Event.h"

namespace tjg {
    class TimeExpired : public Event {
           
    public:
        explicit TimeExpired();
        // trigger intermediate menu
    };
}

#endif //GAME_TIMEEXPIRED_H
