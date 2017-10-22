
#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/System/Time.hpp>
#include <Systems/PhysicsSystem.h>

#include "Systems/ControlCenter.h"
#include "EntityFactory.h"
#include "EventManager.h"
#include "Events/ReachedExit.h"

namespace tjg {

    class View {
    private:
        virtual void initialize() = 0;
        virtual void update() = 0;
    protected:
        ResourceManager &resource_manager;

        // Systems
        // All views need a physical center and control center.
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

        // Used for fixed time step
        sf::Clock physics_clock;

        // Countdown timer set
        sf::Clock countdown_clock;
        sf::Time time_countdown;
        bool show_countdown = true;
        bool countdown_mode_binary = true; // set it to fasle for a regular decimal timer
        unsigned int max_countdown = 30;
        unsigned int remaining_seconds = max_countdown;

    public:
        View(ResourceManager&);

        /**
         * Initialize creates and configures necessary entities before the game begins
         */
        void Initialize();

        /**
         * Update will cause the physical center to be updated.
         */
        void Update();

        /**
         * @return whether the view is still running
         */
        virtual bool Running() = 0;

        /**
         * @return if tech17 reach the exit
         */
        bool DidReachExit();

    };

}
#endif //GAME_VIEW_H
