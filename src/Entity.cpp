#include "Entity.h"

/* TODO(Erik): This will be going away as more systems are developed.
 * Currently, only the SpriteRenderSystem exists, but eventually, components will not contain logic,
 * and will not be able to communicate with eachother.
 */
void tjg::Entity::ConnectComponents() {
    for (auto component : components) {
        component.second->ConnectComponents();
    }
}

/**
 * AddChild
 * @param child entity to add as a child entity
 */
void tjg::Entity::AddChild(std::shared_ptr<tjg::Entity> child) {
    children.push_back(child);
}

/**
 * HasChildren
 * @return whether the entity has any children entities
 */
bool tjg::Entity::HasChildren() {
    return !children.empty();
}

/**
 * ForEachChild
 * Performs an action on each child entity
 * @param f A callback to be called for each child entity
 */
void tjg::Entity::ForEachChild(std::function<void(std::shared_ptr<Entity>)> f) {
    for (auto child : children) {
        f(child);
    }
}
