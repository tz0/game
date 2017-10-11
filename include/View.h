
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
        PhysicsSystem physics_system;
        ControlCenter control_center;

        ResourceManager &resource_manager;
        EntityFactory entity_factory;
        EventManager event_manager;

        // Entities
        std::shared_ptr<Entity> tech17;
        std::vector<std::shared_ptr<Entity>> walls;
        std::vector<std::shared_ptr<Entity>> asteroids;

    public:
        View(ResourceManager&);

        void Initialize();
        void Update(const sf::Time);
        virtual bool Running() = 0;

    };

}
#endif //GAME_VIEW_H
