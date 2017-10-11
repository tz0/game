#ifndef GAME_SPRITERENDERSYSTEM_H
#define GAME_SPRITERENDERSYSTEM_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <map>

#include "Entity.h"
#include "System.h"

namespace tjg {

    class SpriteRenderSystem : public System {
    private:
        std::map<int, std::vector<std::shared_ptr<Entity>>> layers;
        void renderEntity(sf::RenderTarget &target, std::shared_ptr<Entity> entity);
    public:
        void AddEntity(std::shared_ptr<Entity> entity);
        void render(sf::RenderTarget &target);
    };
}


#endif //GAME_SPRITERENDERSYSTEM_H
