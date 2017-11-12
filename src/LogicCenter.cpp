#include "LogicCenter.h"

namespace tjg {
    LogicCenter::LogicCenter(ResourceManager &resource_manager, EventManager &event_manager) :
            physics_system(),
            collision_center(physics_system.GetSpace()),
            entity_factory(resource_manager, physics_system),
            event_manager(event_manager)
    {
    }

    void LogicCenter::Initialize(const unsigned int level_number) {
        level.Read(level_number, true);
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
        event_manager.RegisterListener<HitLethalWall>([&](HitLethalWall &event){
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
            // If the fuel clock has started, check for a loss.
            if (out_of_fuel_clock_started) {
                if  (out_of_fuel_clock.getElapsedTime().asSeconds() >= seconds_to_wait_after_fuel_expired) {
                    game_state = State::FAILED;
                }
            }
            // If the fuel clock hasn't started, start it.
            else {
                std::cout << "Out of fuel! Starting countdown." << std::endl;
                out_of_fuel_clock.restart();
                out_of_fuel_clock_started = true;
            }
        });

        //Iterate wall information record from level's walls vector, create walls and add them to the walls vector.
        for (auto wall : level.GetWalls()) {            
            walls.push_back(entity_factory.MakeWall(sf::Vector2f(wall.origin_x, wall.origin_y), sf::Vector2f(wall.endpoint_x, wall.endpoint_y), wall.radius, wall.lethal));
        }
                        
        //Iterate fan information record from level's fans vector, create fans and add them to the fans vector.
        for (auto fan : level.GetFans()) {
            fans.push_back(entity_factory.MakeFan(sf::Vector2f(fan.origin_x, fan.origin_y), sf::Vector2f(fan.endpoint_x, fan.endpoint_y), fan.width, fan.origin_strength, fan.endpoint_strength));
        }

        // Make shock boxes.
        for (auto shock_box : level.GetShockBoxes()) {
            shock_boxes.push_back(entity_factory.MakeShockBox(sf::Vector2f(shock_box.x, shock_box.y)));
        }

        // Create a collision center handler that will fire a HitLethalWall event when TECH17 hits a wall.
        collision_center.AddHandler(
            CollisionGroup::TECH17,
            CollisionGroup::LETHAL,
            [&](cpArbiter *arb, cpSpace *space) {
                (void)arb;
                (void)space;
                event_manager.Fire<HitLethalWall>();
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
        fuel_tracker = entity_factory.MakeResourceTracker(level.GetFuel(), tracker_texture_path, sf::Color(255, 100, 0));
        oxygen_tracker = entity_factory.MakeResourceTracker(level.GetOxygen(), tracker_texture_path, sf::Color(0, 100, 255));

        // Link the fuel resource to the control center.
        auto fuel_resource = fuel_tracker->GetComponent<FiniteResource>();
        control_center.SetFuelResource(fuel_resource);

        // Set up out_of_fuel_clock.
        out_of_fuel_clock_started = false;
        seconds_to_wait_after_fuel_expired = 3.f;
    }

    void LogicCenter::Update(const sf::Time &elapsed) {
        // Update physics system.
        physics_system.Update(elapsed);

        // Countdown timer - start counting. To be more fair, do not start to count during initialization.
        auto oxygen_finite_resource = oxygen_tracker->GetComponent<FiniteResource>();
        oxygen_finite_resource->ExpendResource(elapsed.asSeconds());

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
        walls.clear();
        fans.clear();
        shock_boxes.clear();
        physics_system.Reset();
        collision_center.Reset(physics_system.GetSpace());
        game_state = State::PLAYING;
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

    PhysicsSystem& LogicCenter::GetPhysicsSystem() {
        return physics_system;
    }

    Level& LogicCenter::GetLevel() {
        return level;
    }

    std::vector<std::shared_ptr<Entity>> &LogicCenter::GetShockBoxes() {
        return shock_boxes;
    }
}
