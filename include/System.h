
#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include "Entity.h"

namespace tjg {

    class System {
    protected:

    public:
        virtual void AddEntity(std::shared_ptr<Entity> entity) = 0;
    };

    class SpriteRenderSystem {
    private:
        std::map<int, std::vector<std::shared_ptr<Entity>>> layers;

        void renderEntity(sf::RenderTarget &target, std::shared_ptr<Entity> entity) {
            auto location_component = entity->GetComponent<Location>();
            auto position = location_component ? location_component->position : sf::Vector2f(0, 0);
            auto rotation = location_component ? location_component->rotation : 0.0f;
            auto sprite = entity->GetComponent<Sprite>()->GetSprite();
            sprite.setPosition(position);
            sprite.setRotation(rotation);
            target.draw(sprite);
        }

    public:
        void AddEntity(std::shared_ptr<Entity> entity, int layer = 0) {
            if (!entity->GetComponent<Sprite>()) {
                throw std::runtime_error("missing sprite component");
            }
            layers[layer].push_back(entity);
        }

        void render(sf::RenderTarget &target) {
            for (auto layer : layers) {
                for (auto entity : layer.second) {
                    renderEntity(target, entity);
                }
            }
        }

    };
}

#endif //GAME_SYSTEM_H
