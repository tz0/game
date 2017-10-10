#include "Components/Sprite.h"

namespace tjg {
    Sprite::Sprite(sf::Sprite sprite) {
        this->sprite = sprite;
        auto bounds = this->sprite.getLocalBounds();
        this->sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    }

    void Sprite::ConnectComponents() {
        // TODO No longer needed, except because of the interface. Will be removed soon.
    }

    sf::Sprite &Sprite::GetSprite() {
        return sprite;
    }

    sf::FloatRect Sprite::getBounds() {
        return sprite.getGlobalBounds();
    }
}