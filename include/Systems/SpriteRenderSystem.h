#ifndef GAME_SPRITERENDERSYSTEM_H
#define GAME_SPRITERENDERSYSTEM_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <map>

#include "Entity.h"
#include "System.h"
#include "Components/Hidden.h"

namespace tjg {

    class SpriteRenderSystem : public System {
    private:
        std::map<int, std::vector<std::shared_ptr<Entity>>> layers;

        /**
         * Render the specified entity to the given target.
         * @param target
         * @param entity
         */
        void renderEntity(sf::RenderTarget &target, std::shared_ptr<Entity> entity);

    public:

        /**
         * Add an entity to be drawn. Requires a Sprite component.
         * @param entity
         */
        void AddEntity(std::shared_ptr<Entity> entity);

        /**
         * Draw all of the entities to the specified target
         * @param target
         */
        void render(sf::RenderTarget &target);

        /**
         * Clear all layers
         */
        void Reset();
    };
}

#endif //GAME_SPRITERENDERSYSTEM_H
