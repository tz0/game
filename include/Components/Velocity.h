
#ifndef GAME_VELOCITY_H
#define GAME_VELOCITY_H

#include "Component.h"
#include "Components/Location.h"

class Velocity : public Component {
private:
    std::shared_ptr<Location> location;
public:
    Velocity() : velocity(0.0f, 0.0f) {}
    Velocity(const sf::Vector2f velocity) : velocity(velocity) {}
    Velocity(const float x, const float y) : velocity(x, y) {}
    sf::Vector2f velocity;
    void Update(sf::Time elapsed) {
        location->position += velocity * static_cast<float>(elapsed.asMilliseconds());
    }
    void ConnectComponents(){
        location = entity->GetComponent<Location>();
    }
};

#endif //GAME_VELOCITY_H
