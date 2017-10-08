
#ifndef GAME_APPENDAGE_H
#define GAME_APPENDAGE_H

#include "chipmunk.h"
#include "Components/RectangleShape.h"
#include "Components/DynamicBody.h"

namespace tjg {

    class Appendage : public Component {
    private:
        cpConstraint *pivot;
        cpConstraint *spring;

    public:
        Appendage(cpSpace *space, cpBody *bodyA, cpBody *bodyB, const sf::Vector2f &offsetA, const sf::Vector2f &offsetB, const float stiffness = 0.0f, const float restAngle = 0.0f) {

            spring = cpDampedRotarySpringNew(bodyA, bodyB, restAngle, stiffness, 1000);
            cpSpaceAddConstraint(space, spring);

            pivot = cpPivotJointNew2(bodyA, bodyB, cpv(offsetA.x, offsetA.y), cpv(offsetB.x, offsetB.y));
            cpConstraintSetCollideBodies(pivot, cpFalse);
            cpSpaceAddConstraint(space, pivot);
        }

        ~Appendage(){
            cpConstraintFree(pivot);
            cpConstraintFree(spring);
        }

        void ConnectComponents(){
        }
        cpConstraint* GetPivot() {
            return pivot;
        }
        cpConstraint* GetSpring() {
            return spring;
        }
    };
}
#endif //GAME_APPENDAGE_H
