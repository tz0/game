//
// Created by erik on 9/23/17.
//

#ifndef GAME_GRAVITY_H
#define GAME_GRAVITY_H

#include "Component.h"
#include "Components/Velocity.h"

class Gravity : public Component {
private:
    std::shared_ptr<Velocity> velocity;
public:
    void Update(sf::Time elapsed) {
        velocity->velocity.y = std::min(5.0f, velocity->velocity.y + 1.98f * elapsed.asSeconds());
    }
    void GetComponents(){
        velocity = entity->GetComponent<Velocity>();
    }
};

#endif //GAME_GRAVITY_H
