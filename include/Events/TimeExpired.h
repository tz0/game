#ifndef TIME_EXPIRED_H
#define TIME_EXPIRED_H

#include "Event.h"

namespace tjg {
    class TimeExpired : public Event {
           
    public:
        explicit TimeExpired();
        // trigger intermediate menu
    };
}

#endif // !TIME_EXPIRED_H
