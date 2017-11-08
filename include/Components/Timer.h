#ifndef GAME_TIMER_H
#define GAME_TIMER_H

#include <SFML/System/Clock.hpp>
#include "Component.h"

namespace tjg {

    /**
     * Wrapper component around sfml Clocks that can be used to track time value in an entity.
     */

    class Timer : public Component {
    private:
        // Fields
        sf::Clock clock;
        sf::Time duration;

    public:
        // Constructors
        explicit Timer(sf::Time duration) : duration(duration) {}
        // Accessors
        float GetPercentElapsed();
        sf::Time GetElapsed();
        sf::Time Restart();
    };

}

#endif //GAME_TIMER_H
