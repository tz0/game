//
// Created by erik on 9/27/17.
//

#ifndef GAME_RECTANGLESHAPE_H
#define GAME_RECTANGLESHAPE_H

#include "Component.h"
#include "Components/Location.h"

namespace tjg {

    class RectangleShape : public Component {
    private:
        sf::RectangleShape rect;
        std::shared_ptr<Location> location;
    public:
        RectangleShape(sf::Vector2f size) {
            rect.setSize(size);
            auto bounds = rect.getLocalBounds();
            rect.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        }

        const sf::Vector2f & GetSize() {
            return rect.getSize();
        }

        void Render(sf::RenderTarget &target) {
            rect.setRotation(location->rotation);
            rect.setPosition(location->position);
            target.draw(rect);
        }

        void ConnectComponents() {
            location = entity->GetComponent<Location>();
        }
    };

}

#endif //GAME_RECTANGLESHAPE_H
