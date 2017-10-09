#include "Components/Location.h"
#include <SFML/Audio.hpp>

tjg::Location::Location(sf::Vector2f pos) {
    position = pos;
}

tjg::Location::Location(const float x, const float y) {
    position = sf::Vector2f(x, y);
}

void tjg::Location::ConnectComponents() {
    // TODO ?
}
