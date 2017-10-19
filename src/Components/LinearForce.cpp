
#include <SFML/Graphics/Rect.hpp>
#include "Components/LinearForce.h"

namespace tjg {

    LinearForce::LinearForce(cpSpace *space, const sf::Vector2f a, const sf::Vector2f b, const float width, const float strength) {
        shape = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(a.x, a.y), cpv(b.x, b.y), width / 2.f);
        cpShapeSetSensor(shape, cpTrue);
        cpSpaceAddShape(space, shape);

        this->strength = strength;
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

}