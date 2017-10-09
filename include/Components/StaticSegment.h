
#ifndef GAME_STATICSEGMENT_H
#define GAME_STATICSEGMENT_H

#include <chipmunk.h>

namespace tjg {

    class StaticSegment : public Component {
    private:
        cpShape *shape;
    public:
        // Constructors.
        StaticSegment(cpSpace *space, float x1, float y1, float x2, float y2);
        StaticSegment(cpSpace *space, sf::Vector2f a, sf::Vector2f b);
        // Destructor
        ~StaticSegment();
        // Component methods
        void ConnectComponents() override;
        // Get shape
        cpShape *GetShape();
    };
}

#endif //GAME_STATICSEGMENT_H
