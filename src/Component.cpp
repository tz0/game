#include "Component.h"

// Store a pointer to the Entity this is a component of.
void tjg::Component::SetEntity(tjg::Entity *entity) {
    this->entity = entity;
}
