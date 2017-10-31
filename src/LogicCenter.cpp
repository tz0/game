#include "LogicCenter.h"

namespace tjg {
    LogicCenter::LogicCenter(ResourceManager &resource_manager) :
            resource_manager(resource_manager),
            physics_system(),
            collision_center(physics_system.GetSpace()),
            entity_factory(resource_manager, physics_system) {
    }

    void LogicCenter::Initialize(Level &level) {
        // Make TECH-17
        tech17 = entity_factory.MakeTech17(level.GetEntrance().x, level.GetEntrance().y);
        control_center.AddEntity(tech17);

        // Make entrance and exit.        
        entrance = entity_factory.MakeEntrance(sf::Vector2f(level.GetEntrance().x, level.GetEntrance().y));     
        exit = entity_factory.MakeExit(sf::Vector2f(level.GetExit().x, level.GetExit().y));

        // Register listeners.
        event_manager.RegisterListener<ReachedExit>([&](ReachedExit &event){
            (void)event;
            game_state = State::WON;
        });
        event_manager.RegisterListener<HitWall>([&](HitWall &event){
            (void)event;
            std::cout << "Hit a wall!" << std::endl;
            game_state = State::FAILED;
        });
        event_manager.RegisterListener<OxygenExpired>([&](OxygenExpired &event) {
            (void)event;
            std::cout << "Out of oxygen!" << std::endl;
            game_state = State::FAILED;
        });
        event_manager.RegisterListener<FuelExpired>([&](FuelExpired &event) {
            (void)event;
            std::cout << "Out of fuel!" << std::endl;
            game_state = State::FAILED;
        });

        //Iterate wall information record from level's walls vector, create walls and add them to the walls vector.
        for (auto wall : level.GetWalls()) {            
            walls.push_back(entity_factory.MakeWall(sf::Vector2f(wall.origin_x, wall.origin_y), sf::Vector2f(wall.endpoint_x, wall.endpoint_y), wall.radius));
        }
                        
        //Iterate fan information record from level's fans vector, create fans and add them to the fans vector.
        for (auto fan : level.GetFans()) {            
            fans.push_back(entity_factory.MakeFan(sf::Vector2f(fan.origin_x, fan.origin_y), sf::Vector2f(fan.endpoint_x, fan.endpoint_y), fan.width, fan.origin_strength, fan.endpoint_strength));
        }

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
        fuel_tracker = entity_factory.MakeResourceTracker(level.GetTotalFuel(), tracker_texture_path, sf::Color(255, 100, 0));
        oxygen_tracker = entity_factory.MakeResourceTracker(level.GetTotalOxygen(), tracker_texture_path, sf::Color(0, 100, 255));

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


    void LogicCenter::Reset() {
        physics_system.Reset();
        collision_center.Reset(physics_system.GetSpace());
        game_state = State::PLAYING;
        oxygen_clock.restart();
    }


    State LogicCenter::GetGameState() {
        return game_state;
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
