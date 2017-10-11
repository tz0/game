#include "Components/Sprite.h"

namespace tjg {

    Sprite::Sprite(sf::Sprite sprite, const int layer) {
        this->sprite = sprite;
        this->layer = layer;
        auto bounds = this->sprite.getLocalBounds();
        this->sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    }

    sf::Sprite &Sprite::GetSprite() {
        return sprite;
    }

    sf::FloatRect Sprite::GetBounds() {
        return sprite.getGlobalBounds();
    }

    int Sprite::GetLayer() {
        return layer;
    }
}