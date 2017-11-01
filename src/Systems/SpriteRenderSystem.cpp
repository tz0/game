#include "Systems/SpriteRenderSystem.h"

namespace tjg {

    void SpriteRenderSystem::renderEntity(sf::RenderTarget &target, std::shared_ptr<Entity> entity) {
        auto location_component = entity->GetComponent<Location>();
        auto position = location_component ? location_component->GetPosition() : sf::Vector2f(0, 0);
        auto rotation = location_component ? location_component->GetRotation() : 0.0f;
        auto sprite = entity->GetComponent<Sprite>()->GetSprite();
        sprite.setPosition(position);
        sprite.setRotation(rotation);
        target.draw(sprite);
    }

    void SpriteRenderSystem::AddEntity(std::shared_ptr<Entity> entity) {
        auto sprite_component = entity->GetComponent<Sprite>();
        if (!sprite_component) {
            throw std::runtime_error("Missing sprite component");
        }
        layers[sprite_component->GetLayer()].push_back(entity);
    }


    void SpriteRenderSystem::render(sf::RenderTarget &target) {
        for (auto &layer : layers) {

            // Delete entities that have been flagged for removal.
            layer.second.erase(
                    std::remove_if(
                            layer.second.begin(),
                            layer.second.end(),
                            [&](std::shared_ptr<Entity> entity) {
                                if (entity->IsFlaggedForRemoval())
                                    return true;
                                renderEntity(target, entity);
                                return false;
                            }),
                    layer.second.end()
            );
        }

    }

    void SpriteRenderSystem::Reset() {
        layers.clear();
    }
}
