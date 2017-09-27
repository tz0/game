
#ifndef GAME_STATICSEGMENT_H
#define GAME_STATICSEGMENT_H

#include "chipmunk.h"

class StaticSegment : public Component {
private:
    cpShape *shape;


public:
    StaticSegment(cpSpace *space, float x1, float y1, float x2, float y2) :
            StaticSegment(space, sf::Vector2f(x1, y1), sf::Vector2f(x2, y2)) {}

    StaticSegment(cpSpace *space, sf::Vector2f a, sf::Vector2f b) {
        shape = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(a.x, a.y), cpv(b.x, b.y), 1);
        cpShapeSetFriction(shape, .7);
        cpShapeSetElasticity(shape, 0.5);
        cpSpaceAddShape(space, shape);
    }

    ~StaticSegment() {
        cpShapeFree(shape);
    }

    void ConnectComponents() {
    }

    cpShape *GetShape() {
        return shape;
    }
};


#endif //GAME_STATICSEGMENT_H
