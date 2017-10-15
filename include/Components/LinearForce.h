//
// Created by erik on 10/13/17.
//

#ifndef GAME_LINEARFORCE_H
#define GAME_LINEARFORCE_H

#include <chipmunk.h>
#include <SFML/System/Vector2.hpp>

#include "Component.h"

namespace tjg {

    class LinearForce : public Component {

    public:
        LinearForce(cpSpace *space, sf::Vector2f position, sf::Vector2f size, float rotation, float power);
    };

}

#endif //GAME_LINEARFORCE_H
