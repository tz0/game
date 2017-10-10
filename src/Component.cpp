#include "Component.h"

namespace tjg {

// Store a pointer to the Entity this is a component of.
    void Component::SetEntity(Entity *entity) {
        this->entity = entity;
    }

}