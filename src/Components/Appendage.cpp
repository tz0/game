#include "Components/Appendage.h"

tjg::Appendage::Appendage(cpSpace *space, cpBody *bodyA, cpBody *bodyB, const sf::Vector2f &offsetA,
                          const sf::Vector2f &offsetB, const float stiffness, const float restAngle) {

    spring = cpDampedRotarySpringNew(bodyA, bodyB, restAngle, stiffness, 1000);
    cpSpaceAddConstraint(space, spring);

    pivot = cpPivotJointNew2(bodyA, bodyB, cpv(offsetA.x, offsetA.y), cpv(offsetB.x, offsetB.y));
    cpConstraintSetCollideBodies(pivot, cpFalse);
    cpSpaceAddConstraint(space, pivot);
}

tjg::Appendage::~Appendage() {
    cpConstraintFree(pivot);
    cpConstraintFree(spring);
}

void tjg::Appendage::ConnectComponents() {
    // TODO ?
}

cpConstraint *tjg::Appendage::GetPivot() {
    return pivot;
}

cpConstraint *tjg::Appendage::GetSpring() {
    return spring;
}
