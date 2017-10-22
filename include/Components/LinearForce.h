
#ifndef GAME_LINEARFORCE_H
#define GAME_LINEARFORCE_H

// Make M_PI work on Windows.
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include <chipmunk.h>
#include <SFML/System/Vector2.hpp>

#include "Component.h"

namespace tjg {

    class LinearForce : public Component {

    private:
        cpShape *shape;
        float origin_strength;
        float end_strength;

        // normalized vector representing the direction of air flow
        cpVect force;

    public:
        LinearForce(cpSpace *space, sf::Vector2f origin_point, sf::Vector2f end_point, float width, float origin_strength, float end_strength);
        ~LinearForce();
        cpShape *GetShape();
        float GetOriginStrength();
        float GetEndStrength();
        cpVect GetForce();
    };

}

#endif //GAME_LINEARFORCE_H
