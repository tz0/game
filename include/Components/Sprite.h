
#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "Component.h"

namespace tjg {

    class Sprite : public Component {
    private:
        sf::Sprite sprite;
    public:
        Sprite(sf::Sprite sprite) : sprite(sprite) {
            auto bounds = this->sprite.getLocalBounds();
            this->sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        }

        void ConnectComponents() {
        }

        sf::Sprite & GetSprite() {
            return sprite;
        }

        sf::FloatRect getBounds() {
            return sprite.getGlobalBounds();
        }
    };
}
#endif //GAME_SPRITE_H
