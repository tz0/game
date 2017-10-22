
#include "View.h"

namespace tjg {
    View::View(ResourceManager &resource_manager) :
            resource_manager(resource_manager),
            physics_system(event_manager),
            entity_factory(resource_manager, physics_system, event_manager) {
    }

    void View::Initialize() {

        tech17 = entity_factory.MakeTech17();
        control_center.AddEntity(tech17);

        entrance = entity_factory.MakeEntrance(sf::Vector2f(0, 0));
        exit = entity_factory.MakeExit(sf::Vector2f(1000, 1000));

        event_manager.RegisterListener<ExitReached>([&](ExitReached &event){
            (void)event;
            did_exit = true;
        });

        // Create boundary walls using the entity factory.
        auto top_wall = entity_factory.MakeWall(sf::Vector2f(-1000, -1000), sf::Vector2f(1300, -1000), 40);
        auto bottom_wall = entity_factory.MakeWall(sf::Vector2f(1300, 1300), sf::Vector2f(-1000, 1300), 40);
        auto left_wall = entity_factory.MakeWall(sf::Vector2f(-1000, 1300), sf::Vector2f(-1000, -1000), 40);
        auto right_wall = entity_factory.MakeWall(sf::Vector2f(1300, -1000), sf::Vector2f(1300, 1300), 40);

        // Add the walls to the entities vector.
        walls.push_back(top_wall);
        walls.push_back(bottom_wall);
        walls.push_back(left_wall);
        walls.push_back(right_wall);

        //fans.push_back(entity_factory.MakeFan(sf::Vector2f(0, -500), 270, 200, 20000.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(500, -500), 45+90, 200, 600.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(-500, 500), -45, 200, 600.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(-500, -500), 45, 200, 600.0f));
        //fans.push_back(entity_factory.MakeFan(sf::Vector2f(500, 500), 45+180, 200, 600.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(0, -500), 90, 200, 600.0f));
        //fans.push_back(entity_factory.MakeFan(sf::Vector2f(0, 500), -90, 200, 600.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(-500, 0), 0, 200, 600.0f));
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(500, 0), 180, 200, 600.0f));

        // Call specific view's initialization method.
        initialize();
    }

    void View::Update() {
        auto elapsed = physics_clock.getElapsedTime();
        if (elapsed.asSeconds() > 1.f/60.f) {
            physics_system.Update(elapsed);
            update();
            physics_clock.restart();
        }
    }
    //Naive solution
    bool View::DidReachExit() {
        return did_exit;
    }
}
