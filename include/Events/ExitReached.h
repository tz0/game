
#ifndef GAME_EXITREACHED_H
#define GAME_EXITREACHED_H

#include "Event.h"

namespace tjg {
    class ExitReached : public Event {
    private:
        // could possible contain information such as:
        //  - time elapsed
        //  - fuel remaining
    public:
        explicit ExitReached();
    };
}

#endif //GAME_EXITREACHED_H
