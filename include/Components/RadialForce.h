
#ifndef GAME_RADIALFORCE_H
#define GAME_RADIALFORCE_H

// Make M_PI work on Windows.
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include <chipmunk.h>
#include <SFML/System/Vector2.hpp>

#include "Component.h"

namespace tjg {

    class RadialForce : public Component {

    private:
        cpBody *body;
        cpShape *shape;
        float origin_strength;
        float end_strength;

    public:
        RadialForce(cpSpace *space, sf::Vector2f origin, float radius, float origin_strength, float end_strength);
        ~RadialForce();
        cpShape *GetShape();
        cpBody *GetBody();
        float GetOriginStrength();
        float GetEndStrength();
        cpVect GetForce();
    };

}

#endif //GAME_RADIALFORCE_H
