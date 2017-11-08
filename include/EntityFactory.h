
#ifndef GAME_ENTITYFACTORY_H
#define GAME_ENTITYFACTORY_H

// Need these two lines for M_PI to work on Windows.
#define _USE_MATH_DEFINES
#include <cmath>

#include "Entity.h"
#include "ResourceManager.h"

#include "EventManager.h"
#include "Events/ReachedExit.h"

#include "Components/Appendage.h"
#include "Components/DynamicBody.h"
#include "Components/LinearForce.h"
#include "Components/Location.h"
#include "Components/SensorShape.h"
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
        std::shared_ptr<Entity> MakeWall(const sf::Vector2f &origin_point, const sf::Vector2f &end_point, float radius, bool lethal = false);
        std::shared_ptr<Entity> MakeStaticDecoration(sf::Sprite sprite, const sf::Vector2f &position, float rotation = 0);
        std::shared_ptr<Entity> MakeTiledBackground(const std::string &texture_path);
        std::shared_ptr<Entity> MakeTech17(const float & tech17_x, const float &tech17_y);
        std::shared_ptr<Entity> MakeFan(const sf::Vector2f &origin_point, const sf::Vector2f &end_point, float width, float origin_strength, float end_strength);
        std::shared_ptr<Entity> MakeEntrance(const sf::Vector2f &position);
        std::shared_ptr<Entity> MakeExit(const sf::Vector2f &position);
        std::shared_ptr<Entity> MakeResourceTracker(float max_value, std::string &texture_path, const sf::Color &color);
    };

}

#endif //GAME_ENTITYFACTORY_H
