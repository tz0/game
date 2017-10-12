#include "Components/Location.h"

namespace tjg {
    Location::Location(sf::Vector2f pos) {
        position = pos;
        rotation = 0.f;
    }

    Location::Location(const float x, const float y) {
        position = sf::Vector2f(x, y);
        rotation = 0.f;
    }

    float Location::getRotation() {
        return rotation;
    }

    void Location::setRotation(float degrees) {
        this->rotation = degrees;
    }

    sf::Vector2f Location::getPosition() {
        return position;
    }

    void Location::setPosition(sf::Vector2f position) {
        this->position = position;
    }
}