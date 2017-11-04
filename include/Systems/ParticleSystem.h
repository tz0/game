
#ifndef GAME_PARTICLESYSTEM_H
#define GAME_PARTICLESYSTEM_H

#include "Components/Timer.h"
#include "PhysicsSystem.h"
#include "SpriteRenderSystem.h"
#include "System.h"

namespace tjg {

    class ParticleSystem : public System {
    private:
        SpriteRenderSystem &render_system;
        PhysicsSystem &physics_system;

        // max particles per emitter
        unsigned int particle_count;

        sf::Sprite sprite;
        int sprite_depth;
        sf::BlendMode sprite_blend_mode;

        std::function<sf::Color(float)> color_transformation;
        std::function<sf::Vector2f(float)> scale_transformation;

        // Vector of entities which are used as the particle emitters.
        // The x/y positions of these entities specify where particles can be born
        std::vector<std::shared_ptr<Entity>> emitters;

        // Vector of entities which are used as the particles.
        // These are created/managed/recycled by the particle system
        std::vector<std::shared_ptr<Entity>> particles;

        std::random_device rd;
        std::default_random_engine gen;

        // Used to generate random variation within the particle system
        std::uniform_real_distribution<float> lifetime_dist;
        std::uniform_real_distribution<float> x_position_variation_dist;
        std::uniform_real_distribution<float> y_position_variation_dist;
        std::uniform_real_distribution<float> angular_velocity_dist;

        // Initializes specified particle at position
        void SpawnParticle(std::shared_ptr<Entity> particle, sf::Vector2f position);
        // Creates a new particle and adds it to the particles vector
        void MakeParticle(sf::Vector2f position);

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
        ParticleSystem(SpriteRenderSystem &render_system, PhysicsSystem &physics_system,
                       unsigned int particle_count,
                       sf::Sprite sprite,
                       int sprite_depth,
                       sf::BlendMode sprite_blend_mode,
                       sf::Time lifetime,
                       sf::Vector2f position_variation,
                       float angular_velocity_variation,
                       std::function<sf::Color(float)> color_transformation = [](float x){
                           (void)x;
                           return sf::Color::White;
                       },
                       std::function<sf::Vector2f(float)> scale_transformation = [](float x){
                           (void)x;
                           return sf::Vector2f(1.f, 1.f);
                       });

        // Reset the particles/emitters vectors
        void Initialize();
        // Specify an entity to be used as an emitter. Note that a particle system with no emitters will not produce
        // particles.
        void AddEntity(std::shared_ptr<Entity> entity) override;
        // Updates particle properties, respawning as needed
        void Update();
    };

}

#endif //GAME_PARTICLESYSTEM_H
