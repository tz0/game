
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <SFML/System/Time.hpp>

#include "Systems/PhysicsSystem.h"
#include "Systems/ControlCenter.h"
#include "EntityFactory.h"
#include "EventManager.h"
#include "Events/FuelExpired.h"
#include "Events/OxygenExpired.h"
#include "Events/ReachedExit.h"
#include "Events/ViewChanged.h"
#include "Constants.h"
#include "Components/FiniteResource.h"
#include "Level.h"


namespace tjg {

    class LogicCenter {

    private:
        // Systems
        PhysicsSystem physics_system;
        ControlCenter control_center;
        CollisionCenter collision_center;

        // Entity factory
        EntityFactory entity_factory;

        // Event manager
        EventManager &event_manager;

        // Entities
        std::shared_ptr<Entity> tech17;
        std::shared_ptr<Entity> entrance;
        std::shared_ptr<Entity> exit;

        State game_state = State::PLAYING;
        std::shared_ptr<Entity> fuel_tracker;
        std::shared_ptr<Entity> oxygen_tracker;

        // Temporary for testing purposes.
        std::vector<std::shared_ptr<Entity>> walls;
        std::vector<std::shared_ptr<Entity>> fans;

        Level level;

    public:
        LogicCenter(ResourceManager &resource_manager, EventManager &event_manager);

        /**
         * Initialize creates and configures necessary entities before the game begins
         */
        void Initialize(unsigned int level_number);

        /**
         * Update will cause the physical center to be updated.
         */
        void Update(const sf::Time &elapsed);

        /**
         *  Resets the logic center
         */
        void Reset();

        // Accessors
        State GetGameState(); //result of game
        EntityFactory& GetEntityFactory();
        ControlCenter& GetControlCenter();
        PhysicsSystem& GetPhysicsSystem();
        std::shared_ptr<Entity> GetTech17();
        std::vector<std::shared_ptr<Entity>>& GetWalls();
        std::vector<std::shared_ptr<Entity>>& GetFans();
        std::shared_ptr<Entity> GetEntrance();
        std::shared_ptr<Entity> GetExit();
        std::shared_ptr<Entity> GetFuelTracker();
        std::shared_ptr<Entity> GetOxygenTracker();
        Level &GetLevel();

    };

}
#endif //GAME_LOGIC_H
