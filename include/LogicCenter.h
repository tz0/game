
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <SFML/System/Time.hpp>
#include <Systems/PhysicsSystem.h>

#include "Systems/ControlCenter.h"
#include "EntityFactory.h"
#include "EventManager.h"
#include "Events/ReachedExit.h"
#include "Events/TimeExpired.h"

namespace tjg {

    class LogicCenter {

    private:
        ResourceManager &resource_manager;

        // Systems
        PhysicsSystem physics_system;
        ControlCenter control_center;
        CollisionCenter collision_center;

        EntityFactory entity_factory;
        EventManager event_manager;

        // Entities
        std::shared_ptr<Entity> tech17;
        std::shared_ptr<Entity> entrance;
        std::shared_ptr<Entity> exit;
        bool did_exit = false;

        // Temporary for testing purposes.
        std::vector<std::shared_ptr<Entity>> walls;
        std::vector<std::shared_ptr<Entity>> fans;

        // Countdown timer set
        sf::Clock countdown_clock;
        sf::Time time_countdown;
        unsigned int max_countdown = 30;
        unsigned int remaining_seconds = max_countdown;

    public:
        LogicCenter(ResourceManager &resource_manager);

        /**
         * Initialize creates and configures necessary entities before the game begins
         */
        void Initialize();

        /**
         * Update will cause the physical center to be updated.
         */
        void Update(sf::Time elapsed);

        /**
         * @return if tech17 reach the exit
         */
        bool DidReachExit();

        /**
         *  Resets the logic center
         */
        void Reset();

        // Accessors
        EntityFactory& GetEntityFactory();
        ControlCenter& GetControlCenter();
        std::shared_ptr<Entity> GetTech17();
        std::vector<std::shared_ptr<Entity>>& GetWalls();
        std::vector<std::shared_ptr<Entity>>& GetFans();
        std::shared_ptr<Entity> GetEntrance();
        std::shared_ptr<Entity> GetExit();
        unsigned int GetRemainingSeconds();

    };

}
#endif //GAME_LOGIC_H
