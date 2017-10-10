#include "Components/DynamicBody.h"

tjg::DynamicBody::DynamicBody(cpSpace *space, const sf::Vector2f &position, float mass, const sf::Vector2f &size,
                              bool infiniteMoment) {

    body = cpSpaceAddBody(space, cpBodyNew(mass, infiniteMoment ? INFINITY : cpMomentForBox(mass, size.x, size.y)));
    cpBodySetPosition(body, cpv(position.x, position.y));
    shape = cpSpaceAddShape(space, cpBoxShapeNew(body, size.x, size.y, 0));
}

tjg::DynamicBody::DynamicBody(cpSpace *space, const sf::Vector2f &position, float mass, float radius) {
    body = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForCircle(mass, 0, radius, cpvzero)));
    cpBodySetPosition(body, cpv(position.x, position.y));
    shape = cpSpaceAddShape(space, cpCircleShapeNew(body, radius, cpvzero));
}

tjg::DynamicBody::~DynamicBody() {
    cpShapeFree(shape);
    cpBodyFree(body);
}

void tjg::DynamicBody::Update() {
    auto bodyPosition = cpBodyGetPosition(body);
    location->position = sf::Vector2f(bodyPosition.x, bodyPosition.y);

    auto bodyAngle = cpBodyGetAngle(body);
    location->rotation = bodyAngle * 180.0f / M_PI;
}

void tjg::DynamicBody::ConnectComponents() {
    location = entity->GetComponent<Location>();
}

cpBody *tjg::DynamicBody::GetBody() {
    return body;
}

cpShape *tjg::DynamicBody::GetShape() {
    return shape;
}
