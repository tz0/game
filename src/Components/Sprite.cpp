#include "Components/Sprite.h"

tjg::Sprite::Sprite(sf::Sprite sprite) {
    this->sprite = sprite;
    auto bounds = this->sprite.getLocalBounds();
    this->sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void tjg::Sprite::ConnectComponents() {
    // TODO ?
}

sf::Sprite &tjg::Sprite::GetSprite() {
    return sprite;
}

sf::FloatRect tjg::Sprite::getBounds() {
    return sprite.getGlobalBounds();
}
