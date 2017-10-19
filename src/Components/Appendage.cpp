#include "Components/Appendage.h"

namespace tjg {

    Appendage::Appendage(cpSpace *space, cpBody *bodyA, cpBody *bodyB, const sf::Vector2f &offsetA,
                         const sf::Vector2f &offsetB, const float stiffness, const float rest_angle,
                         const double limit_amount) {

        // Setup spring rotary joint
        spring = cpDampedRotarySpringNew(bodyA, bodyB, rest_angle, stiffness, 5000);
        cpSpaceAddConstraint(space, spring);

        // Setup pivot joint
        pivot = cpPivotJointNew2(bodyA, bodyB, cpv(offsetA.x, offsetA.y), cpv(offsetB.x, offsetB.y));
        cpConstraintSetCollideBodies(pivot, cpFalse);
        cpSpaceAddConstraint(space, pivot);

        // Setup rotation limiter
        limiter = cpRotaryLimitJointNew(bodyB, bodyA, rest_angle - limit_amount, rest_angle + limit_amount);
        cpSpaceAddConstraint(space, limiter);
    }

    Appendage::~Appendage() {
        cpConstraintFree(pivot);
        cpConstraintFree(spring);
        cpConstraintFree(limiter);
    }

    cpConstraint *Appendage::GetPivot() {
        return pivot;
    }

    cpConstraint *Appendage::GetSpring() {
        return spring;
    }

    cpConstraint* Appendage::GetLimiter() {
        return limiter;
    }
}