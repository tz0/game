#include "Components/Timer.h"

namespace tjg {
    sf::Time Timer::GetElapsed() {
        return clock.getElapsedTime();
    }
    sf::Time Timer::Restart() {
        return clock.restart();
    }
    float Timer::GetPercentElapsed() {
        return GetElapsed() / duration;
    }
}
