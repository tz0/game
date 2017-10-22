
#include <SFML/Graphics/Rect.hpp>
#include "Components/LinearForce.h"

namespace tjg {

    LinearForce::LinearForce(cpSpace *space, const sf::Vector2f position, const float angle, const float width, const float strength) {

        const auto angle_radians = angle * M_PI / 180.0f;
        auto end_point = sf::Vector2f(position.x + cos(angle_radians) * strength, position.y + sin(angle_radians) * strength);

        shape = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(position.x, position.y), cpv(end_point.x, end_point.y), width / 2.f);
        cpShapeSetSensor(shape, cpTrue);
        cpSpaceAddShape(space, shape);

        this->strength = strength;
        force = cpvnormalize(cpv(end_point.x, end_point.y) - cpv(position.x, position.y));
    }

    LinearForce::~LinearForce() {
        cpShapeFree(shape);
    }

    cpShape *LinearForce::GetShape() {
        return shape;
    }

    float LinearForce::GetStrength() {
        return strength;
    }

    cpVect LinearForce::GetForce() {
        return force;
    }

}