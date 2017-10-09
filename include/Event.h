
#ifndef GAME_EVENT_H
#define GAME_EVENT_H

#include <SFML/Window/Keyboard.hpp>

namespace tjg {

    class Event {
    };

    class KeyPress : public Event {
    private:
        sf::Keyboard::Key key;
    public:
        explicit KeyPress(sf::Keyboard::Key key);
        sf::Keyboard::Key GetKey();
    };
}
#endif //GAME_EVENT_H
