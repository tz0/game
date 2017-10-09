
#ifndef GAME_APPENDAGE_H
#define GAME_APPENDAGE_H

#include "Component.h"
#include <chipmunk.h>
#include <SFML/Audio.hpp>

namespace tjg {

    class Appendage : public Component {
    private:
        cpConstraint *pivot;
        cpConstraint *spring;
    public:
        // Constructor
        Appendage(cpSpace *space, cpBody *bodyA, cpBody *bodyB, const sf::Vector2f &offsetA,
                  const sf::Vector2f &offsetB, float stiffness = 0.0f, float restAngle = 0.0f);
        // Destructor
        ~Appendage();
        // Physics
        cpConstraint* GetPivot();
        cpConstraint* GetSpring();
        // Component methods
        void ConnectComponents() override;
    };
}
#endif //GAME_APPENDAGE_H
