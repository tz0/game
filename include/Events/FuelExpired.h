#ifndef GAME_FUELEXPIRED_H
#define GAME_FUELEXPIRED_H


#include "Event.h"

namespace tjg {
    class FuelExpired : public Event {

    public:
        explicit FuelExpired() = default;
    };
}


#endif //GAME_FUELEXPIRED_H
