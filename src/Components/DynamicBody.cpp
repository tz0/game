#include "Components/DynamicBody.h"

namespace tjg {
    DynamicBody::DynamicBody(cpSpace *space, const sf::Vector2f &position, float mass, const sf::Vector2f &size,
                                  bool infiniteMoment) {

        body = cpSpaceAddBody(space, cpBodyNew(mass, infiniteMoment ? INFINITY : cpMomentForBox(mass, size.x, size.y)));
        cpBodySetPosition(body, cpv(position.x, position.y));
        shape = cpSpaceAddShape(space, cpBoxShapeNew(body, size.x, size.y, 0));
    }

    DynamicBody::DynamicBody(cpSpace *space, const sf::Vector2f &position, float mass, float radius) {
        body = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForCircle(mass, 0, radius, cpvzero)));
        cpBodySetPosition(body, cpv(position.x, position.y));
        shape = cpSpaceAddShape(space, cpCircleShapeNew(body, radius, cpvzero));
    }

    DynamicBody::~DynamicBody() {
        cpShapeFree(shape);
        cpBodyFree(body);
    }

    cpBody *DynamicBody::GetBody() {
        return body;
    }

    cpShape *DynamicBody::GetShape() {
        return shape;
    }
}