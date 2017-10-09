#include "System.h"
#include "Components/Location.h"

void tjg::SpriteRenderSystem::renderEntity(sf::RenderTarget &target, std::shared_ptr<tjg::Entity> entity) {
    auto location_component = entity->GetComponent<Location>();
    auto position = location_component ? location_component->position : sf::Vector2f(0, 0);
    auto rotation = location_component ? location_component->rotation : 0.0f;
    auto sprite = entity->GetComponent<Sprite>()->GetSprite();
    sprite.setPosition(position);
    sprite.setRotation(rotation);
    target.draw(sprite);
}

void tjg::SpriteRenderSystem::AddEntity(std::shared_ptr<tjg::Entity> entity, int layer) {
    if (!entity->GetComponent<Sprite>()) {
        throw std::runtime_error("missing sprite component");
    }
    layers[layer].push_back(entity);
}

void tjg::SpriteRenderSystem::render(sf::RenderTarget &target) {
    for (auto layer : layers) {
        for (auto &entity : layer.second) {
            renderEntity(target, entity);
        }
    }
}
