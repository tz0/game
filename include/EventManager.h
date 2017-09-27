
#ifndef GAME_EVENTMANAGER_H
#define GAME_EVENTMANAGER_H

#include <typeindex>
#include <unordered_map>
#include "Event.h"

class EventManager {
private:
    std::unordered_map<std::type_index, std::vector<std::function<void(Event &)>>> listeners;

public:
    EventManager() {};

    template<typename T, typename... Args>
    void TriggerEvent(Args &&... args) {
        T event(std::forward<Args>(args)...);
        for (auto listener : listeners[std::type_index(typeid(T))]) {
            listener(event);
        }
    }

    template<typename T>
    void RegisterListener(std::function<void(T &)> f) {
        listeners[std::type_index(typeid(T))].push_back([&](Event &e) {
            f(static_cast<T &>(e));
        });
    };
};


#endif //GAME_EVENTMANAGER_H
