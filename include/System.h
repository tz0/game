
#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include "Entity.h"
#include "Components/Sprite.h"
#include "Components/Location.h"
#include <map>
#include <SFML/Graphics/RenderTarget.hpp>

namespace tjg {

    class System {
    public:
        virtual void AddEntity(std::shared_ptr<Entity> entity) = 0;
    };

    class SpriteRenderSystem {
    private:
        std::map<int, std::vector<std::shared_ptr<Entity>>> layers;
        void renderEntity(sf::RenderTarget &target, std::shared_ptr<Entity> entity);
    public:
        void AddEntity(std::shared_ptr<Entity> entity, int layer = 0);
        void render(sf::RenderTarget &target);
    };
}

#endif //GAME_SYSTEM_H
