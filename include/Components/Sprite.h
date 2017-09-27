
#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "Component.h"

class Sprite : public Component {
private:
    sf::Sprite sprite;
    sf::CircleShape shape; // used to draw a little dot in places for debugging purposes.
    std::shared_ptr<Location> pos;
public:
    Sprite(sf::Sprite sprite) : sprite(sprite) {
        shape.setRadius(5);
        shape.setFillColor(sf::Color::Red);

        auto bounds = this->sprite.getLocalBounds();
        this->sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    }

    void ConnectComponents() {
        pos = entity->GetComponent<Location>();
    }

    void Draw(sf::RenderTarget &target) {
        sprite.setPosition(pos->position.x, pos->position.y);
        sprite.setRotation(pos->rotation);
        target.draw(sprite);

/*
        shape.setPosition(pos->position.x, pos->position.y);
        target.draw(shape);

        auto bounds = sprite.getGlobalBounds();

        shape.setPosition(bounds.left, bounds.top);
        target.draw(shape);
        shape.setPosition(bounds.left + bounds.width, bounds.top);
        target.draw(shape);
        shape.setPosition(bounds.left, bounds.top + bounds.height);
        target.draw(shape);
        shape.setPosition(bounds.left + bounds.width, bounds.top + bounds.height);
        target.draw(shape);
*/
    }

    sf::FloatRect getBounds() {
        return sprite.getGlobalBounds();
    }
};

#endif //GAME_SPRITE_H
