#include "LogicCenter.h"

namespace tjg {
    LogicCenter::LogicCenter(ResourceManager &resource_manager) :
            resource_manager(resource_manager),
            physics_system(),
            collision_center(physics_system.GetSpace()),
            entity_factory(resource_manager, physics_system) {
    }

    void LogicCenter::Initialize() {
        // Make TECH-17
        tech17 = entity_factory.MakeTech17();
        control_center.AddEntity(tech17);

        // Make entrance and exit.
        entrance = entity_factory.MakeEntrance(sf::Vector2f(0, 0));
        exit = entity_factory.MakeExit(sf::Vector2f(-1400, -200));

        // Register listeners.
        event_manager.RegisterListener<ReachedExit>([&](ReachedExit &event){
            (void)event;
            did_exit = true;
        });
        event_manager.RegisterListener<HitWall>([&](HitWall &event){
            (void)event;
            std::cout << "Hit a wall!" << std::endl;
        });
        event_manager.RegisterListener<OxygenExpired>([&](OxygenExpired &event) {
            (void)event;
            std::cout << "Out of oxygen!" << std::endl;
        });
        event_manager.RegisterListener<FuelExpired>([&](FuelExpired &event) {
            (void)event;
            std::cout << "Out of fuel!" << std::endl;
        });

        // Create boundary walls using the entity factory.
        auto top_wall = entity_factory.MakeWall(sf::Vector2f(-1540, -600), sf::Vector2f(540, -600), 80);
        auto bottom_wall = entity_factory.MakeWall(sf::Vector2f(-1540, 600), sf::Vector2f(540, 600), 80);
        auto left_wall = entity_factory.MakeWall(sf::Vector2f(-1500, -600), sf::Vector2f(-1500, 600), 80);
        auto right_wall = entity_factory.MakeWall(sf::Vector2f(500, -600), sf::Vector2f(500, 600), 80);

        // Add the walls to the entities vector.
        walls.push_back(top_wall);
        walls.push_back(bottom_wall);
        walls.push_back(left_wall);
        walls.push_back(right_wall);

        // Create fans and add them to the fans vector.
        // Top fan above span
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(0, -600), sf::Vector2f(0, 600), 200, 250.0f, 0.f));
        // Bottom fan below spawn
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(0, 600), sf::Vector2f(0, -600), 200, 250.0f, 0.f));
        // Top fan to right of spawn.
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(300, -600), sf::Vector2f(300, 600), 200, 250.0f, 0.f));
        // Right fan below spawn.
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(500, 400), sf::Vector2f(-1500, 400), 200, 250.0f, 50.f));
        // Bottom fan near exit.
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(-1000, 600), sf::Vector2f(-1000, -600), 200, 250.0f, 0.f));
        // Top fan near exit.
        fans.push_back(entity_factory.MakeFan(sf::Vector2f(-1300, -600), sf::Vector2f(-1300, 600), 200, 300.0f, 0.f));

        // Create a collision center handler that will fire a HitWall event when TECH17 hits a wall.
        collision_center.AddHandler(
            CollisionGroup::TECH17,
            CollisionGroup::WALL,
            [&](cpArbiter *arb, cpSpace *space) {
                (void)arb;
                (void)space;
                event_manager.Fire<HitWall>();
            }
        );

        // Check if Tech17's chest overlaps with the exit door
        collision_center.AddHandler(
            CollisionGroup::TECH17,
            CollisionGroup::EXIT,
            [&](cpArbiter *arb, cpSpace *space) {
                (void)arb;
                (void)space;
                event_manager.Fire<ReachedExit>();
            }
        );

        // Build resource trackers.
        std::string tracker_texture_path = "white-texture.jpg";
        fuel_tracker = entity_factory.MakeResourceTracker(3, tracker_texture_path, sf::Color(255, 100, 0));
        oxygen_tracker = entity_factory.MakeResourceTracker(30, tracker_texture_path, sf::Color(0, 100, 255));

        // Link the fuel resource to the control center.
        auto fuel_resource = fuel_tracker->GetComponent<FiniteResource>();
        control_center.SetFuelResource(fuel_resource);
    }

    void LogicCenter::Update(const sf::Time &elapsed) {
        // Update physics system.
        physics_system.Update(elapsed);

        // Countdown timer - start counting. To be more fair, do not start to count during initialization.
        auto elapsed_seconds = oxygen_clock.getElapsedTime().asSeconds();
        auto oxygen_finite_resource = oxygen_tracker->GetComponent<FiniteResource>();
        auto max_oxygen = oxygen_finite_resource->GetMaxLevel();
        oxygen_finite_resource->SetCurrentLevel(max_oxygen - elapsed_seconds);

        // If out of oxygen, fire an event.
        if (oxygen_finite_resource->IsDepleted()){
            event_manager.Fire<OxygenExpired>();
        }

        // If out of fuel, fire an event.
        auto fuel_finite_resource = fuel_tracker->GetComponent<FiniteResource>();
        if (fuel_finite_resource->IsDepleted()){
            event_manager.Fire<FuelExpired>();
        }
    }

    bool LogicCenter::DidReachExit() {
        return did_exit;
    }

    std::shared_ptr<Entity> LogicCenter::GetTech17() {
        return tech17;
    }

    std::vector<std::shared_ptr<Entity>>& LogicCenter::GetWalls() {
        return walls;
    }

    std::shared_ptr<Entity> LogicCenter::GetEntrance() {
        return entrance;
    }

    std::shared_ptr<Entity> LogicCenter::GetExit() {
        return exit;
    }

    std::shared_ptr<Entity> LogicCenter::GetFuelTracker() {
        return fuel_tracker;
    }

    std::shared_ptr<Entity> LogicCenter::GetOxygenTracker() {
        return oxygen_tracker;
    }

    std::vector<std::shared_ptr<Entity>>& LogicCenter::GetFans() {
        return fans;
    }

    EntityFactory& LogicCenter::GetEntityFactory() {
        return entity_factory;
    }

    ControlCenter& LogicCenter::GetControlCenter() {
        return control_center;
    }
}
