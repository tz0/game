
#include "View.h"

namespace tjg {
    View::View(ResourceManager &resource_manager) :
            resource_manager(resource_manager),
            entity_factory(resource_manager, physics_system) {

    }

    void View::Initialize() {

        tech17 = entity_factory.MakeTech17(sf::Vector2f(0, 0));
        control_center.AddEntity(tech17);

        entrance = entity_factory.MakeEntrance(sf::Vector2f(0, 0));
        exit = entity_factory.MakeExit(sf::Vector2f(1000, 1000));

        // Create boundary walls using the entity factory.
        auto top_wall = entity_factory.MakeWall(sf::Vector2f(-300, -300), sf::Vector2f(1300, -300), 40);
        auto bottom_wall = entity_factory.MakeWall(sf::Vector2f(1300, 1300), sf::Vector2f(-300, 1300), 40);
        auto left_wall = entity_factory.MakeWall(sf::Vector2f(-300, 1300), sf::Vector2f(-300, -300), 40);
        auto right_wall = entity_factory.MakeWall(sf::Vector2f(1300, -300), sf::Vector2f(1300, 1300), 40);

        // Add the walls to the entities vector.
        walls.push_back(top_wall);
        walls.push_back(bottom_wall);
        walls.push_back(left_wall);
        walls.push_back(right_wall);


        // Create many asteroids
        // Temporary just for testing.
//        for (auto i = 0; i < 10; ++i) {
//            auto asteroid_entity = std::make_shared<Entity>();
//            asteroid_entity->AddComponent<Location>();
//            asteroid_entity->AddComponent<DynamicBody>(
//                    physics_system.GetSpace(),
//                    sf::Vector2f(floor(i / 4) * 100 + 50, 100 * (i % 4)),
//                    3,
//                    sf::Vector2f(100, 100));
//            asteroids.push_back(asteroid_entity);
//            physics_system.AddEntity(asteroid_entity);
//        }

        // Call specific view's initialization method.
        initialize();
    }

    void View::Update(const sf::Time elapsed) {
        physics_system.Update(elapsed);
        update(elapsed);
    }
    //Naive solution
    bool View::DidReachExit() {
        if (!did_exit && std::abs(tech17->GetComponent<Location>()->getPosition().x - exit->GetComponent<Location>()->getPosition().x) < 30 &&
                std::abs(tech17->GetComponent<Location>()->getPosition().y - exit->GetComponent<Location>()->getPosition().y) < 30){
            printf("Reached Exit!\n");
            did_exit = true;
        }
        return did_exit;
    }
}
