
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

    void View::Update() {
        auto elapsed = physics_clock.getElapsedTime();
        if (elapsed.asSeconds() > 1.f/60.f) {
            std::cout << elapsed.asSeconds() << std::endl;
            physics_system.Update(elapsed);
            update(elapsed);
            physics_clock.restart();
        }
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
