
#ifndef GAME_PLAYERINPUT_H
#define GAME_PLAYERINPUT_H

#include "Component.h"
#include "Components/Velocity.h"

class PlayerInput : public Component {
private:
    std::shared_ptr<Velocity> velocity;
public:
    void Update(sf::Time elapsed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity->velocity.x -= .01 * elapsed.asMilliseconds();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity->velocity.x += .01 * elapsed.asMilliseconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            velocity->velocity.y -= .01 * elapsed.asMilliseconds();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            velocity->velocity.y += .01 * elapsed.asMilliseconds();
        }
    }
    void GetComponents(){
        velocity = entity->GetComponent<Velocity>();
    }
};

#endif //GAME_PLAYERINPUT_H
