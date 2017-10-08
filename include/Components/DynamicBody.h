
#ifndef GAME_DYNAMICBODY_H
#define GAME_DYNAMICBODY_H

#include "chipmunk.h"
#include "Components/Location.h"

namespace tjg {

    class DynamicBody : public Component {
    private:
        cpBody *body;
        cpShape *shape;

        std::shared_ptr<Location> location;

    public:
        DynamicBody(cpSpace *space, const sf::Vector2f &position, float mass, const sf::Vector2f &size, bool infiniteMoment = false) {
            body = cpSpaceAddBody(space, cpBodyNew(mass, infiniteMoment ? INFINITY : cpMomentForBox(mass, size.x, size.y)));
            cpBodySetPosition(body, cpv(position.x, position.y));
            shape = cpSpaceAddShape(space, cpBoxShapeNew(body, size.x, size.y, 0));
        }
        DynamicBody(cpSpace *space, const sf::Vector2f &position, float mass, float radius) {
            body = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForCircle(mass, 0, radius, cpvzero)));
            cpBodySetPosition(body, cpv(position.x, position.y));
            shape = cpSpaceAddShape(space, cpCircleShapeNew(body, radius, cpvzero));
        }
        ~DynamicBody(){
            cpShapeFree(shape);
            cpBodyFree(body);
        }
        void Update() {
            auto bodyPosition = cpBodyGetPosition(body);
            location->position = sf::Vector2f(bodyPosition.x, bodyPosition.y);

            auto bodyAngle = cpBodyGetAngle(body);
            location->rotation = bodyAngle * 180.0f / M_PI;
        }
        void ConnectComponents(){
            location = entity->GetComponent<Location>();
        }
        cpBody* GetBody() {
            return body;
        }
        cpShape* GetShape() {
            return shape;
        }
    };
}
#endif //GAME_DYNAMICBODY_H
