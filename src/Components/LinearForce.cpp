
#include "Components/LinearForce.h"

namespace tjg {

    LinearForce::LinearForce(cpSpace *space, const sf::Vector2f origin_point, const sf::Vector2f end_point, const float width, const float origin_strength, const float end_strength) {

        // Create chipmunk shape.
        shape = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(origin_point.x, origin_point.y), cpv(end_point.x, end_point.y), width / 2.f);
        cpShapeSetSensor(shape, cpTrue);
        cpSpaceAddShape(space, shape);

        // Set strengths.
        this->origin_strength = origin_strength;
        this->end_strength = end_strength;

        // Create normalized force vector.
        force = cpvnormalize(cpv(end_point.x, end_point.y) - cpv(origin_point.x, origin_point.y));
    }

    LinearForce::~LinearForce() {
        cpShapeFree(shape);
    }

    cpShape *LinearForce::GetShape() {
        return shape;
    }

    float LinearForce::GetOriginStrength() {
        return origin_strength;
    }

    float LinearForce::GetEndStrength() {
        return end_strength;
    }

    cpVect LinearForce::GetForce() {
        return force;
    }

}