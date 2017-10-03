
#ifndef GAME_LOCATION_H
#define GAME_LOCATION_H

#include "Component.h"

namespace JPG {

    class Location : public Component {
    public:
        Location(){};
        Location(sf::Vector2f pos) : position(pos) {}
        Location(const float x, const float y) : position(x, y) {}
        sf::Vector2f position;
        float rotation = 0.0f;
        void ConnectComponents() {}
    };

}
#endif //GAME_LOCATION_H
