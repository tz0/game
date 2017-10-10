#include "Components/CircleShape.h"

tjg::CircleShape::CircleShape(float radius) {
    circle.setRadius(radius);
    auto bounds = circle.getLocalBounds();
    circle.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void tjg::CircleShape::Render(sf::RenderTarget &target) {
    circle.setRotation(location->getRotation());
    circle.setPosition(location->getPosition());
    target.draw(circle);
}

float tjg::CircleShape::GetSize() {
    return circle.getRadius();
}

void tjg::CircleShape::ConnectComponents() {
    location = entity->GetComponent<Location>();
}
