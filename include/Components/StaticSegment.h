
#ifndef GAME_STATICSEGMENT_H
#define GAME_STATICSEGMENT_H

#include <chipmunk.h>
#include <Component.h>
#include <SFML/Audio.hpp>

namespace tjg {

    class StaticSegment : public Component {
    private:
        cpShape *shape;
    public:
        // Constructors.
        StaticSegment(cpSpace *space, float x1, float y1, float x2, float y2, float radius);
        StaticSegment(cpSpace *space, sf::Vector2f a, sf::Vector2f b, float radius);
        // Destructor
        ~StaticSegment();
        // Get shape
        cpShape *GetShape();
    };
}

#endif //GAME_STATICSEGMENT_H
