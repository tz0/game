#include "Components/StaticSegment.h"

namespace tjg {

    StaticSegment::StaticSegment(cpSpace *space, sf::Vector2f a, sf::Vector2f b, float width) {
        shape = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(a.x, a.y), cpv(b.x, b.y), width / 2.f);
        cpShapeSetFriction(shape, .7);
        cpShapeSetElasticity(shape, 0.5);
        cpSpaceAddShape(space, shape);
    }

    StaticSegment::StaticSegment(cpSpace *space, float x1, float y1, float x2, float y2, float width) {
        shape = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(x1, y1), cpv(x2, y2), width / 2.f);
        cpShapeSetFriction(shape, .7);
        cpShapeSetElasticity(shape, 0.5);
        cpSpaceAddShape(space, shape);
    }

    StaticSegment::~StaticSegment() {
        cpShapeFree(shape);
    }

    cpShape *StaticSegment::GetShape() {
        return shape;
    }

    void StaticSegment::ConnectComponents() {
        // TODO ?
    }
}