
#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "Component.h"
#include <SFML/Graphics/Sprite.hpp>

namespace tjg {

    class Sprite : public Component {
    private:
        sf::Sprite sprite;
        int layer;
    public:
        // Constructor
        explicit Sprite(sf::Sprite sprite, const int layer = 0);
        // Component methods
        void ConnectComponents() override;
        // Sprite methods
        sf::Sprite & GetSprite();
        sf::FloatRect GetBounds();
        int GetLayer();
    };
}
#endif //GAME_SPRITE_H
