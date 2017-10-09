
#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "Component.h"
#include <SFML/Graphics/Sprite.hpp>

namespace tjg {

    class Sprite : public Component {
    private:
        sf::Sprite sprite;
    public:
        // Constructor
        explicit Sprite(sf::Sprite sprite);
        // Component methods
        void ConnectComponents() override;
        // Sprite methods
        sf::Sprite & GetSprite();
        sf::FloatRect getBounds();
    };
}
#endif //GAME_SPRITE_H
