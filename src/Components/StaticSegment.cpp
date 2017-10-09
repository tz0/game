#include "Components/StaticSegment.h"
#include <SFML/Audio.hpp>

tjg::StaticSegment::StaticSegment(cpSpace *space, sf::Vector2f a, sf::Vector2f b) {
    shape = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(a.x, a.y), cpv(b.x, b.y), 10);
    cpShapeSetFriction(shape, .7);
    cpShapeSetElasticity(shape, 0.5);
    cpSpaceAddShape(space, shape);
}

tjg::StaticSegment::StaticSegment(cpSpace *space, float x1, float y1, float x2, float y2) {
    shape = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(x1, y1), cpv(x2, y2), 10);
    cpShapeSetFriction(shape, .7);
    cpShapeSetElasticity(shape, 0.5);
    cpSpaceAddShape(space, shape);
}

tjg::StaticSegment::~StaticSegment() {
    cpShapeFree(shape);
}

cpShape *tjg::StaticSegment::GetShape() {
    return shape;
}

void tjg::StaticSegment::ConnectComponents() {
    // TODO ?
}
