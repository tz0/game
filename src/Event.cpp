#include "Event.h"

tjg::KeyPress::KeyPress(sf::Keyboard::Key key) {
    this->key = key;
}

sf::Keyboard::Key tjg::KeyPress::GetKey() {
    return this->key;
}
