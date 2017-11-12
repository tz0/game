
#ifndef GAME_PHYSICSPARTICLESYSTEM_H
#define GAME_PHYSICSPARTICLESYSTEM_H

#include "Components/Timer.h"
#include "PhysicsSystem.h"
#include "SpriteRenderSystem.h"
#include "Systems/ParticleSystem.h"

namespace tjg {

    class PhysicsParticleSystem : public ParticleSystem {
    private:
        PhysicsSystem &physics_system;

    protected:
        // Initializes specified particle at position
        void SpawnParticle(std::shared_ptr<Entity> particle, sf::Vector2f position) override;

        // Creates a new particle and adds it to the particles vector
        void MakeParticle(sf::Vector2f position) override;

        void PrepareParticleForRemoval(std::shared_ptr<Entity> particle) override;

    public:

        /**
         * Create a physical particle system. Refer to ParticleSystem.h for details on these parameters.
         * In addition to the parameters required for any particle system, PhysicsParticleSystems require a
         * PhysicsSystem in which to add particles.
         * @param render_system the render system that the particles will be added to
         */
        PhysicsParticleSystem(SpriteRenderSystem &render_system, PhysicsSystem &physics_system,
                              unsigned int particle_count,
                              sf::Sprite sprite,
                              int sprite_depth,
                              sf::BlendMode sprite_blend_mode,
                              sf::Time particle_rate,
                              sf::Time lifetime,
                              sf::Vector2f position_variation,
                              sf::Vector2f velocity_variation,
                              float angular_velocity_variation,
                              std::function<sf::Color(float)> color_transformation = [](float x) {
                                  (void) x;
                                  return sf::Color::White;
                              },
                              std::function<sf::Vector2f(float)> scale_transformation = [](float x) {
                                  (void) x;
                                  return sf::Vector2f(1.f, 1.f);
                              });
    };

}

#endif //GAME_PHYSICSPARTICLESYSTEM_H
