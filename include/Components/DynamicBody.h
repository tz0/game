
#ifndef GAME_DYNAMICBODY_H
#define GAME_DYNAMICBODY_H

// Need these two lines for M_PI to work on Windows.
#define _USE_MATH_DEFINES
#include <cmath>

#include <memory>
#include <chipmunk.h>

#include "Entity.h"
#include "Component.h"
#include "Location.h"

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
        void ConnectComponents() override;
        // Physics
        cpBody* GetBody();
        cpShape* GetShape();
    };
}
#endif //GAME_DYNAMICBODY_H
