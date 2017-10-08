//
// Created by erik on 9/27/17.
//

#ifndef GAME_CIRCLESHAPE_H
#define GAME_CIRCLESHAPE_H

#include "Component.h"
#include "Components/Location.h"

namespace tjg {

    class CircleShape : public Component {
        sf::CircleShape circle;
        std::shared_ptr<Location> location;
    public:
        CircleShape(float radius) {
            circle.setRadius(radius);
            auto bounds = circle.getLocalBounds();
            circle.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        }

        void Render(sf::RenderTarget &target) {
            circle.setRotation(location->rotation);
            circle.setPosition(location->position);
            target.draw(circle);
        }

        float GetSize() {
            return circle.getRadius();
        }

        void ConnectComponents() {
            location = entity->GetComponent<Location>();
        }
    };

}

#endif //GAME_CIRCLESHAPE_H
