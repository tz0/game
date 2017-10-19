
#include "View.h"

namespace tjg {
    View::View(ResourceManager &resource_manager) :
            resource_manager(resource_manager),
            entity_factory(resource_manager, physics_system) {

    }

    void View::Initialize() {

        tech17 = entity_factory.MakeTech17(sf::Vector2f(-500, -500));
        control_center.AddEntity(tech17);

        entrance = entity_factory.MakeEntrance(sf::Vector2f(-500, -500));
        exit = entity_factory.MakeExit(sf::Vector2f(500, 500));
        exitpoint = entity_factory.MakeExitPoint(sf::Vector2f(500, 500));

        // Create boundary walls using the entity factory.
        auto top_wall = entity_factory.MakeWall(sf::Vector2f(-800, -800), sf::Vector2f(800, -800), 40);
        auto bottom_wall = entity_factory.MakeWall(sf::Vector2f(800, 800), sf::Vector2f(-800, 800), 40);
        auto left_wall = entity_factory.MakeWall(sf::Vector2f(-800, 800), sf::Vector2f(-800, -800), 40);
        auto right_wall = entity_factory.MakeWall(sf::Vector2f(800, -800), sf::Vector2f(800, 800), 40);

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
        if (!did_exit && std::abs(tech17->GetComponent<Location>()->getPosition().x - exitpoint->GetComponent<Location>()->getPosition().x) < 30 &&
                std::abs(tech17->GetComponent<Location>()->getPosition().y - exitpoint->GetComponent<Location>()->getPosition().y) < 30){
            printf("Reached Exit!\n");
            did_exit = true;
        }
        return did_exit;
    }
}
