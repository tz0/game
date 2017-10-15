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

    private:
        cpShape *shape;
        float strength;

    public:
        LinearForce(cpSpace *space, sf::Vector2f a, sf::Vector2f b, float width, float strength);
        ~LinearForce();
        cpShape *GetShape();
        float GetStrength();
    };

}

#endif //GAME_LINEARFORCE_H
