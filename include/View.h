
#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/System/Time.hpp>
#include <Systems/PhysicsSystem.h>

#include "Systems/ControlCenter.h"
#include "EntityFactory.h"
#include "EventManager.h"

namespace tjg {

    class View {
    private:
        virtual void initialize() = 0;
        virtual void update(const sf::Time) = 0;
    protected:
        // Systems
        // All views need a physical center and control center.
        PhysicsSystem physics_system;
        ControlCenter control_center;

        ResourceManager &resource_manager;
        EntityFactory entity_factory;
        EventManager event_manager;

        // Entities
        std::shared_ptr<Entity> tech17;
        std::shared_ptr<Entity> entrance;
        std::shared_ptr<Entity> exit;
        std::shared_ptr<Entity> exitpoint;

        // Temporary for testing purposes.
        std::vector<std::shared_ptr<Entity>> walls;
        std::vector<std::shared_ptr<Entity>> asteroids;
        bool did_exit = false;

    public:
        View(ResourceManager&);

        /**
         * Initialize creates and configures necessary entities before the game begins
         */
        void Initialize();

        /**
         * Update will cause the physical center to be updated.
         */
        void Update(const sf::Time);

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
