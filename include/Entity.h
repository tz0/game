
#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <iostream>

#include "Component.h"

namespace tjg {

    class Entity {
    private:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
        std::vector<std::shared_ptr<Entity>> children;
        bool remove = false;

    public:

        // Child methods.
        void AddChild(std::shared_ptr<Entity> child);

        bool HasChildren();

        void ForEachChild(std::function<void(std::shared_ptr<Entity>)> f);

        // Component methods. Since these are templates, they stay in the header file.

        // Tag an entity for removal from systems.
        void FlagForRemoval();

        bool IsFlaggedForRemoval();

        /**
         * AddComponent
         * @tparam T The type of Component being added
         * @tparam Args
         * @param args The constructor arguments for the Component being added
         * @return A shared ptr to the component that was just added
         */
        template<typename T, typename... Args>
        std::shared_ptr<T> AddComponent(Args &&... args) {
            if (components.find(std::type_index(typeid(T))) != components.end()) {
                throw std::runtime_error("Entity can not contain multiple components of the same type.");
            }
            auto component = std::make_shared<T>(std::forward<Args>(args)...);
            components.insert({std::type_index(typeid(T)), component});
            return component;
        }

        /**
+         * SetComponent sets a type of component to a new component, replacing the existing one if present.
+         * @tparam T The type of Component being added
+         * @tparam Args
+         * @param args The constructor arguments for the Component being added
+         * @return A shared ptr to the component that was just added
+         */
        template<typename T, typename... Args>
        std::shared_ptr<T> SetComponent(Args &&... args) {
            auto component = std::make_shared<T>(std::forward<Args>(args)...);
            components[std::type_index(typeid(T))] = component;
            return component;
        }

        /**
         * Remove component removes the specified component.
         * WARNING: if this entity was added to a system that requires the removed component to function, mis-use
         * of this method can lead to run-time errors.
         * @tparam T the type of component to be removed
         */
        template<typename T>
        void RemoveComponent() {
            components.erase(std::type_index(typeid(T)));
        }

        /**
         * GetComponent
         * @tparam T The component which is being requested
         * @return shared pointer to the requested Component, or nullptr if not present
         */
        template<typename T>
        std::shared_ptr<T> GetComponent() {
            return std::static_pointer_cast<T>(components[std::type_index(typeid(T))]);
        }

        /**
         * HasComponent
         * @tparam T The Component which is being checked for
         * @return whether the entity has the specified Component
         */
        template<typename T>
        bool HasComponent() {
            return std::static_pointer_cast<T>(components[std::type_index(typeid(T))]) != nullptr;
        }
    };
}

#endif //GAME_ENTITY_H
