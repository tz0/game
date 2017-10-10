#include "Components/Location.h"

tjg::Location::Location(sf::Vector2f pos) {
    position = pos;
    rotation = 0.f;
}

tjg::Location::Location(const float x, const float y) {
    position = sf::Vector2f(x, y);
    rotation = 0.f;
}

void tjg::Location::ConnectComponents() {
    // TODO ?
}

float tjg::Location::getRotation() {
    return rotation;
}

void tjg::Location::setRotation(float degrees) {
    this->rotation = degrees;
}

sf::Vector2f tjg::Location::getPosition() {
    return position;
}

void tjg::Location::setPosition(sf::Vector2f position) {
    this->position = position;
}
