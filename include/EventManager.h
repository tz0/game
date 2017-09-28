
// TODO: implement a RemoveListener method.

#ifndef GAME_EVENTMANAGER_H
#define GAME_EVENTMANAGER_H

#include <typeindex>
#include <unordered_map>
#include "Event.h"

class EventManager {
private:
    using ListenerMap = std::unordered_map<std::type_index, std::vector<std::function<void(Event &)>>>;

    ListenerMap listeners;
    ListenerMap one_time_listeners;

public:
    template<typename T, typename... Args>
    void Fire(Args &&... args) {
        T event(std::forward<Args>(args)...);
        for (auto listener : listeners[std::type_index(typeid(T))]) {
            listener(event);
        }

        auto once = one_time_listeners[std::type_index(typeid(T))];
        while (!once.empty())
        {
            once.back()(event);
            once.pop_back();
        }
    }

    template<typename T>
    void RegisterListener(std::function<void(T &)> f) {
        listeners[std::type_index(typeid(T))].push_back([=](Event &e) {
            f(static_cast<T &>(e));
        });
    };

    // Will register a callback for the next occurrence of the given event.
    template<typename T>
    void RegisterOnce(std::function<void(T &)> f){
        one_time_listeners[std::type_index(typeid(T))].push_back([=](Event &e) {
            f(static_cast<T &>(e));
        });
    }
};


#endif //GAME_EVENTMANAGER_H
