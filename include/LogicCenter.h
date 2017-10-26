
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <SFML/System/Time.hpp>
#include <Systems/PhysicsSystem.h>

#include "Systems/ControlCenter.h"
#include "EntityFactory.h"
#include "EventManager.h"
#include "Events/ReachedExit.h"
#include "Events/TimeExpired.h"
#include "Components/FiniteResource.h"

namespace tjg {

    class LogicCenter {

    private:
        // Resource manager
        ResourceManager &resource_manager;

        // Systems
        PhysicsSystem physics_system;
        ControlCenter control_center;
        CollisionCenter collision_center;

        // Entity factory
        EntityFactory entity_factory;

        // Event manager
        EventManager event_manager;

        // Entities
        std::shared_ptr<Entity> tech17;
        std::shared_ptr<Entity> entrance;
        std::shared_ptr<Entity> exit;
        std::shared_ptr<Entity> fuel_tracker;
        std::shared_ptr<Entity> oxygen_tracker;

        // Flags
        bool did_exit = false;

        // Temporary for testing purposes.
        std::vector<std::shared_ptr<Entity>> walls;
        std::vector<std::shared_ptr<Entity>> fans;

        // Countdown timer set
        sf::Clock oxygen_clock;

    public:
        LogicCenter(ResourceManager &resource_manager);

        /**
         * Initialize creates and configures necessary entities before the game begins
         */
        void Initialize();

        /**
         * Update will cause the physical center to be updated.
         */
        void Update(const sf::Time &elapsed);

        /**
         * @return if tech17 reach the exit
         */
        bool DidReachExit();

        // Accessors
        EntityFactory& GetEntityFactory();
        ControlCenter& GetControlCenter();
        std::shared_ptr<Entity> GetTech17();
        std::vector<std::shared_ptr<Entity>>& GetWalls();
        std::vector<std::shared_ptr<Entity>>& GetFans();
        std::shared_ptr<Entity> GetEntrance();
        std::shared_ptr<Entity> GetExit();
        std::shared_ptr<Entity> GetFuelTracker();
        std::shared_ptr<Entity> GetOxygenTracker();

    };

}
#endif //GAME_LOGIC_H
