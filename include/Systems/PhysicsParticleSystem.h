
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
         * Create a particle system.
         * @param render_system the render system that the particles will be added to
         * @param physics_system the physics system that the particles will be added to
         * @param particle_count the max amount of particles per emitter
         * (Ex. A system with 2 emitters and a particle_count of 200 will run 400 particles)
         * @param sprite the sprite to use for the particles
         * @param sprite_depth the sprite render layer to use for the particles
         * @param sprite_blend_mode blend mode for particle sprites
         * @param particle_rate time between particles spawning (Ex: a value of 1 second here would mean when enabled,
         * 1 particle will be emitted every 1 second)
         * @param lifetime number of seconds specifying average lifetime of a particle the actual lifetime of a
         * particle will be 50% - 150% of this value.
         * @param position_variation particle will be spawned at a random emitter's location with +-x/+-y added to it's
         * position.
         * @param angular_velocity_variation particle will be given a random angular velocity between
         * +-angular_velocity_variation.
         * @param color_transformation function which maps the percent_lifetime (given as a value between 0.0 and 1.0)
         * and returns the current particle color at this point in life.
         * @param scale_transformation function which maps the percent_lifetime (given as a value between 0.0 and 1.0)
         * and returns the current particle scale at that point in life.
         */
        PhysicsParticleSystem(SpriteRenderSystem &render_system, PhysicsSystem &physics_system,
                              unsigned int particle_count,
                              sf::Sprite sprite,
                              int sprite_depth,
                              sf::BlendMode sprite_blend_mode,
                              sf::Time particle_rate,
                              sf::Time lifetime,
                              sf::Vector2f position_variation,
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
