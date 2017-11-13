
#include "Components/Velocity.h"

namespace tjg {

    Velocity::Velocity(float x, float y) : velocity(x, y) {}
    Velocity::Velocity(sf::Vector2f velocity) : velocity(velocity) {}

    void Velocity::SetVelocity(sf::Vector2f velocity) {
        this->velocity = velocity;
    }

    sf::Vector2f Velocity::GetVelocity() {
        return velocity;
    }

}
