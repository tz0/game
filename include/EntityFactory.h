
#ifndef GAME_ENTITYFACTORY_H
#define GAME_ENTITYFACTORY_H

#include "System.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "Components/Appendage.h"
#include "Components/DynamicBody.h"
#include "Components/Location.h"
#include "Components/Sprite.h"
#include "Components/StaticSegment.h"

namespace tjg {

    class EntityFactory {
    private:
        ResourceManager &resource_manager;
        SpriteRenderSystem &sprite_render_system;
        cpSpace *space = nullptr;
        /**
         * Calculate the angle between two points.
         * @return angle in degrees
         */
        float calculateAngle(sf::Vector2f p1, sf::Vector2f p2);
        /**
         * Calculate the distance between two points.
         * @return distance in pixels
         */
        float calculateDistance(sf::Vector2f p1, sf::Vector2f p2);
    public:
        // Constructor
        EntityFactory(ResourceManager &resource_manager, SpriteRenderSystem &sprite_render_system, cpSpace *space) :
                resource_manager(resource_manager),
                sprite_render_system(sprite_render_system),
                space(space) {}

        // Entity factory methods.
        std::shared_ptr<Entity> MakeWall(const sf::Vector2f &a, const sf::Vector2f &b, const float width);
        std::shared_ptr<Entity> MakeStaticSprite(sf::Sprite sprite, const sf::Vector2f &position);
        std::shared_ptr<Entity> MakeTiledBackground(const std::string &path);
        std::shared_ptr<Entity> MakeTech17();
    };

}

#endif //GAME_ENTITYFACTORY_H
