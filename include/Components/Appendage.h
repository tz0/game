
#ifndef GAME_APPENDAGE_H
#define GAME_APPENDAGE_H

#include "Component.h"
#include <chipmunk.h>
#include <SFML/Audio.hpp>

namespace tjg {

    class Appendage : public Component {
    private:
        cpConstraint *pivot;
        cpConstraint *limiter;
        cpConstraint *spring;
    public:
        // Constructor
        Appendage(cpSpace *space, cpBody *bodyA, cpBody *bodyB, const sf::Vector2f &offsetA,
                  const sf::Vector2f &offsetB, float stiffness = 0.0f, float restAngle = 0.0f, double limit_amount = M_PI);
        // Destructor
        ~Appendage();
        // Physics
        cpConstraint* GetPivot();
        cpConstraint* GetSpring();
        cpConstraint* GetLimiter();
    };
}
#endif //GAME_APPENDAGE_H
