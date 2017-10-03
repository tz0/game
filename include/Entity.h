
#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <typeindex>
#include <unordered_map>

#include "Component.h"

namespace JPG {

    class Entity {
    private:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> components;

    public:

        template<typename T, typename... Args>
        std::shared_ptr<T> AddComponent(Args &&... args) {
            auto component = std::make_shared<T>(std::forward<Args>(args)...);
            components.insert({std::type_index(typeid(T)), component});
            component->SetEntity(this);
            return component;
        }

        void ConnectComponents() {
            for (auto component : components) {
                component.second->ConnectComponents();
            }
        }

        template<typename T>
        std::shared_ptr<T> GetComponent() {
            return std::static_pointer_cast<T>(components[std::type_index(typeid(T))]);
        }
    };
}
#endif //GAME_ENTITY_H
