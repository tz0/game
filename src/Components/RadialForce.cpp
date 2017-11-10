
#include "Components/RadialForce.h"

namespace tjg {

    RadialForce::RadialForce(cpSpace *space, const sf::Vector2f origin, const float radius, const float origin_strength, const float end_strength) {

        // Create chipmunk shape.
        body = cpBodyNewStatic();
        cpBodySetPosition(body, cpv(origin.x, origin.y));
        shape = cpCircleShapeNew(body, radius, cpvzero);
        cpShapeSetSensor(shape, cpTrue);
        cpSpaceAddBody(space, body);
        cpSpaceAddShape(space, shape);

        // Set strengths.
        this->origin_strength = origin_strength;
        this->end_strength = end_strength;

    }

    RadialForce::~RadialForce() {
        cpShapeFree(shape);
        cpBodyFree(body);
    }

    cpShape *RadialForce::GetShape() {
        return shape;
    }

    cpBody* RadialForce::GetBody() {
        return body;
    }

    float RadialForce::GetOriginStrength() {
        return origin_strength;
    }

    float RadialForce::GetEndStrength() {
        return end_strength;
    }
}