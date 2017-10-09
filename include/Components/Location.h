
#ifndef GAME_LOCATION_H
#define GAME_LOCATION_H

#include "Component.h"

namespace tjg {

    class Location : public Component {
    public:
        // Fields
        sf::Vector2f position;
        float rotation = 0.0f;
        // Constructors
        Location() = default;
        explicit Location(sf::Vector2f pos);
        Location(float x, float y);
        // Component methods
        void ConnectComponents() override;
    };

}
#endif //GAME_LOCATION_H
