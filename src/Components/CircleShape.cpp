#include "Components/CircleShape.h"

namespace tjg {

    CircleShape::CircleShape(float radius) {
        circle.setRadius(radius);
        auto bounds = circle.getLocalBounds();
        circle.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    }

    void CircleShape::Render(sf::RenderTarget &target) {
        circle.setRotation(location->getRotation());
        circle.setPosition(location->getPosition());
        target.draw(circle);
    }

    float CircleShape::GetSize() {
        return circle.getRadius();
    }

    void CircleShape::ConnectComponents() {
        location = entity->GetComponent<Location>();
    }
}