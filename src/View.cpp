
#include "View.h"

namespace tjg {
    View::View(ResourceManager &resource_manager) :
            resource_manager(resource_manager),
            entity_factory(resource_manager, physics_system) {

    }

    void View::Initialize() {

        tech17 = entity_factory.MakeTech17();
        control_center.AddEntity(tech17);

        entrance = entity_factory.MakeEntrance(sf::Vector2f(0, 0));

        // Create boundary walls using the entity factory.
        auto top_wall = entity_factory.MakeWall(sf::Vector2f(-500, -500), sf::Vector2f(500, -500), 40);
        auto bottom_wall = entity_factory.MakeWall(sf::Vector2f(500, 500), sf::Vector2f(-500, 500), 40);
        auto left_wall = entity_factory.MakeWall(sf::Vector2f(-500, 500), sf::Vector2f(-500, -500), 40);
        auto right_wall = entity_factory.MakeWall(sf::Vector2f(500, -500), sf::Vector2f(500, 500), 40);

        // Add the walls to the entities vector.
        walls.push_back(top_wall);
        walls.push_back(bottom_wall);
        walls.push_back(left_wall);
        walls.push_back(right_wall);

        fans.push_back(entity_factory.MakeFan(sf::Vector2f(0, -500), sf::Vector2f(0,0), 200, 100.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(0, 500), sf::Vector2f(0,0), 200, 100.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(500, 0), sf::Vector2f(0,0), 200, 100.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(-500, 0), sf::Vector2f(0,0), 200, 100.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(-500, -500), sf::Vector2f(0,0), 200, 100.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(500, 500), sf::Vector2f(0,0), 200, 100.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(500, -500), sf::Vector2f(0,0), 200, 100.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(-500, 500), sf::Vector2f(0,0), 200, 100.0f));

        // Call specific view's initialization method.
        initialize();
    }

    void View::Update(const sf::Time elapsed) {
        physics_system.Update(elapsed);
        update(elapsed);
    }

}
