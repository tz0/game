#include "Event.h"

namespace tjg {
    KeyPress::KeyPress(sf::Keyboard::Key key) {
        this->key = key;
    }

    sf::Keyboard::Key KeyPress::GetKey() {
        return this->key;
    }
}