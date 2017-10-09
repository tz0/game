
#ifndef GAME_DYNAMICBODY_H
#define GAME_DYNAMICBODY_H

#include "Component.h"

namespace tjg {

    class DynamicBody : public Component {
    private:
        cpBody *body;
        cpShape *shape;
        std::shared_ptr<Location> location;
    public:
        // Constructors
        DynamicBody(cpSpace *space, const sf::Vector2f &position, float mass, const sf::Vector2f &size, bool infiniteMoment = false);
        DynamicBody(cpSpace *space, const sf::Vector2f &position, float mass, float radius);
        // Destructor
        ~DynamicBody();
        // Functions
        void Update();
        void ConnectComponents();
        // Physics
        cpBody* GetBody();
        cpShape* GetShape();
    };
}
#endif //GAME_DYNAMICBODY_H
