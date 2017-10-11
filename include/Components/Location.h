
#ifndef GAME_LOCATION_H
#define GAME_LOCATION_H

#include <SFML/Audio.hpp>
#include "Component.h"

namespace tjg {

    class Location : public Component {
    private:
        // Fields
        float rotation;
        sf::Vector2f position;
    public:
        // Constructors
        Location() = default;
        explicit Location(sf::Vector2f pos);
        Location(float x, float y);
        // Accessors
        float getRotation();
        void setRotation(float degrees);
        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f position);
    };

}
#endif //GAME_LOCATION_H
