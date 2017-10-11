#include "Systems/SpriteRenderSystem.h"

namespace tjg {

    void SpriteRenderSystem::renderEntity(sf::RenderTarget &target, std::shared_ptr<Entity> entity) {
        auto location_component = entity->GetComponent<Location>();
        auto position = location_component ? location_component->getPosition() : sf::Vector2f(0, 0);
        auto rotation = location_component ? location_component->getRotation() : 0.0f;
        auto sprite = entity->GetComponent<Sprite>()->GetSprite();
        sprite.setPosition(position);
        sprite.setRotation(rotation);
        target.draw(sprite);
    }

    void SpriteRenderSystem::AddEntity(std::shared_ptr<Entity> entity) {
        auto sprite_component = entity->GetComponent<Sprite>();
        if (!sprite_component) {
            throw std::runtime_error("missing sprite component");
        }
        layers[sprite_component->GetLayer()].push_back(entity);
    }

    void SpriteRenderSystem::render(sf::RenderTarget &target) {
        for (auto layer : layers) {
            for (auto &entity : layer.second) {
                renderEntity(target, entity);
            }
        }
    }
}