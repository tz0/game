
#ifndef GAME_CONTROLCENTER_H
#define GAME_CONTROLCENTER_H

#include <chipmunk.h>

#include "System.h"
#include "Components/DynamicBody.h"
#include "Components/FiniteResource.h"

namespace tjg {

    class ControlCenter : public System {
    private:
        std::shared_ptr<Entity> player_entity;
        std::shared_ptr<FiniteResource> fuel;

        // Use the given amount of fuel
        void useFuel(float amount);
    public:
        // Override System virtual methods
        void AddEntity(std::shared_ptr<Entity> entity) override;
        // Add fuel tracker.
        void SetFuelResource(std::shared_ptr<FiniteResource> &fuel_resource);
        // Player controls.
        void RotateClockwise(const sf::Time &elapsed);
        void RotateCounterClockwise(const sf::Time &elapsed);
        void FireJetpack(const sf::Time &elapsed);
        // Accessor methods
        std::shared_ptr<Entity> GetPlayerEntity();
    };

}

#endif //GAME_CONTROLCENTER_H
