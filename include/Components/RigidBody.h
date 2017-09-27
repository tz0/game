//
// Created by erik on 9/25/17.
//

#ifndef GAME_RIGIDBODY_H
#define GAME_RIGIDBODY_H

#include "chipmunk.h"
#include "Components/Location.h"

class RigidBody : public Component {
private:
    cpBody *body;
    cpShape *shape;

    std::shared_ptr<Location> location;

public:
    RigidBody(cpSpace *space, float x, float y, float mass, float width, float height){
        body = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForBox(mass, width, height)));
        shape = cpSpaceAddShape(space, cpBoxShapeNew(body, width, height, 0));
        cpBodySetPosition(body, cpv(x, y));
    }
    RigidBody(cpSpace *space, float x, float y, float mass, float radius){
        body = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForCircle(mass, 0, radius, cpvzero)));
        shape = cpSpaceAddShape(space, cpCircleShapeNew(body, radius, cpvzero));
        cpBodySetPosition(body, cpv(x, y));
    }
    ~RigidBody(){
        cpBodyFree(body);
        cpShapeFree(shape);
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

#endif //GAME_RIGIDBODY_H
