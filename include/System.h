
#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include <map>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Components/Sprite.h"
#include "Components/Location.h"

namespace tjg {

    class System {
    public:
        virtual void AddEntity(std::shared_ptr<Entity> entity) = 0;
    };

    class SpriteRenderSystem : public System {
    private:
        std::map<int, std::vector<std::shared_ptr<Entity>>> layers;
        void renderEntity(sf::RenderTarget &target, std::shared_ptr<Entity> entity);
    public:
        void AddEntity(std::shared_ptr<Entity> entity);
        void AddEntity(std::shared_ptr<Entity> entity, const int layer);
        void render(sf::RenderTarget &target);
    };
}

#endif //GAME_SYSTEM_H
