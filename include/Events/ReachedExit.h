
#ifndef GAME_REACHEDEXIT_H
#define GAME_REACHEDEXIT_H

#include "Event.h"

namespace tjg {
    class ReachedExit : public Event {
    private:
        // could possible contain information such as:
        //  - time elapsed
        //  - fuel remaining
    public:
        explicit ReachedExit();
    };
}

#endif //GAME_REACHEDEXIT_H
