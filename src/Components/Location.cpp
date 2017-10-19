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

    float Location::GetRotation() {
        return rotation;
    }

    void Location::SetRotation(float degrees) {
        this->rotation = degrees;
    }

    sf::Vector2f Location::GetPosition() {
        return position;
    }

    void Location::SetPosition(sf::Vector2f position) {
        this->position = position;
    }
}