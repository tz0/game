#include "Components/RectangleShape.h"

namespace tjg {
    RectangleShape::RectangleShape(sf::Vector2f size) {
        rect.setSize(size);
        auto bounds = rect.getLocalBounds();
        rect.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    }

    const sf::Vector2f &RectangleShape::GetSize() {
        return rect.getSize();
    }

    void RectangleShape::Render(sf::RenderTarget &target) {
        rect.setRotation(location->getRotation());
        rect.setPosition(location->getPosition());
        target.draw(rect);
    }

    void RectangleShape::ConnectComponents() {
        location = entity->GetComponent<Location>();
    }
}