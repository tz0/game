
#ifndef GAME_VELOCITY_H
#define GAME_VELOCITY_H

#include <SFML/Audio.hpp>
#include "Component.h"

namespace tjg {

    class Velocity : public Component {
    private:
        // Fields
        sf::Vector2f velocity;
    public:
        // Constructors
        Velocity() = default;
        explicit Velocity(sf::Vector2f velocity);
        Velocity(float x, float y);
        // Accessors
        sf::Vector2f GetVelocity();
        void SetVelocity(sf::Vector2f velocity);
    };

}
#endif //GAME_VELOCITY_H
