
#ifndef GAME_ENTITYFACTORY_H
#define GAME_ENTITYFACTORY_H

// Need these two lines for M_PI to work on Windows.
#define _USE_MATH_DEFINES
#include <cmath>

#include "Entity.h"
#include "ResourceManager.h"
#include "Components/Appendage.h"
#include "Components/DynamicBody.h"
#include "Components/LinearForce.h"
#include "Components/Location.h"
#include "Components/Sprite.h"
#include "Components/StaticSegment.h"

#include "Systems/SpriteRenderSystem.h"
#include "Systems/PhysicsSystem.h"

namespace tjg {

    class EntityFactory {
    private:
        ResourceManager &resource_manager;
        PhysicsSystem &physics_system;
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
        EntityFactory(ResourceManager &resource_manager, PhysicsSystem &physics_system) :
                resource_manager(resource_manager),
                physics_system(physics_system) {}

        // Entity factory methods.
        std::shared_ptr<Entity> MakeWall(const sf::Vector2f &a, const sf::Vector2f &b, float width);
        std::shared_ptr<Entity> MakeStaticSprite(sf::Sprite sprite, const sf::Vector2f &position);
        std::shared_ptr<Entity> MakeTiledBackground(const std::string &path);
        std::shared_ptr<Entity> MakeTech17();
        std::shared_ptr<Entity> MakeFan(const sf::Vector2f &a, const sf::Vector2f &b, float width, float strength);
        std::shared_ptr<Entity> MakeEntrance(const sf::Vector2f &a);
        std::shared_ptr<Entity> MakeExit(const sf::Vector2f &a);
    };

}

#endif //GAME_ENTITYFACTORY_H
