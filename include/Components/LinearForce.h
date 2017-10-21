
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

        // normalized vector representing the direction of air flow
        cpVect force;

    public:
        LinearForce(cpSpace *space, const sf::Vector2f position, float angle, float width, float strength);
        ~LinearForce();
        cpShape *GetShape();
        float GetStrength();
        cpVect GetForce();
    };

}

#endif //GAME_LINEARFORCE_H
