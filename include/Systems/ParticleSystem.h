
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

        std::uniform_real_distribution<float> lifetime_dist;
        std::uniform_real_distribution<float> x_position_variation_dist;
        std::uniform_real_distribution<float> y_position_variation_dist;
        std::uniform_real_distribution<float> angular_velocity_dist;

        void SpawnParticle(std::shared_ptr<Entity> particle, sf::Vector2f position);
        std::shared_ptr<Entity> MakeParticle();

    public:

        /**
         *
         * @param render_system
         * @param physics_system
         * @param particle_count
         * @param sprite
         * @param sprite_depth
         * @param sprite_blend_mode
         * @param lifetime number of seconds specifying average lifetime of a particle the actual lifetime of a
         * particle will be 50% - 150% of this value.
         * @param position_variation
         * @param angular_velocity_variation
         * @param color_transformation
         * @param scale_transformation
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

        void Initialize();
        // Specify an entity to be used as an emitter
        void AddEntity(std::shared_ptr<Entity> entity) override;
        void Update();
    };

}

#endif //GAME_PARTICLESYSTEM_H
