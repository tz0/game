#include "Components/RectangleShape.h"

tjg::RectangleShape::RectangleShape(sf::Vector2f size) {
    rect.setSize(size);
    auto bounds = rect.getLocalBounds();
    rect.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

const sf::Vector2f &tjg::RectangleShape::GetSize() {
    return rect.getSize();
}

void tjg::RectangleShape::Render(sf::RenderTarget &target) {
    rect.setRotation(location->rotation);
    rect.setPosition(location->position);
    target.draw(rect);
}

void tjg::RectangleShape::ConnectComponents() {
    location = entity->GetComponent<Location>();
}
