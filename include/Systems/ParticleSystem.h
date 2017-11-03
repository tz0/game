
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

        int particle_count;

        sf::Sprite sprite;
        int sprite_depth;

        std::function<sf::Color(float)> color_transformation;
        std::function<sf::Vector2f(float)> scale_transformation;

        // number of seconds specifying average lifetime of a particle
        // the actual lifetime of a particle will be 50% - 150% of this value.



        // Vector of entities which are used as the particle emitters.
        // The x/y positions of these entities specify where particles can be born
        std::vector<std::shared_ptr<Entity>> emitters;

        // Vector of entities which are used as the particles.
        // These are created/managed/recycled by the particle system
        std::vector<std::shared_ptr<Entity>> particles;

        std::random_device rd;
        std::default_random_engine gen;

        std::uniform_real_distribution<float> lifetime_dist;

        void SpawnParticle(std::shared_ptr<Entity> particle, sf::Vector2f position) {

            // Lifetime exceeded, recycle entity.
            auto body = particle->GetComponent<DynamicBody>();
            //if (body) {
            //    cpSpaceRemoveShape(physics_system.GetSpace(), body->GetShape());
            //    cpSpaceRemoveBody(physics_system.GetSpace(), body->GetBody());
            //}

            particle->GetComponent<Timer>()->Restart();
            auto size = sprite.getGlobalBounds();
            cpBodySetPosition(body->GetBody(), cpv(position.x, position.y));
            //body = particle->SetComponent<DynamicBody>(physics_system.GetSpace(), position, 1,
                   //                                    sf::Vector2f(size.width, size.height));
            //cpShapeSetSensor(body->GetShape(), cpTrue);
        }

    public:

        /**
         *
         * @param render_system
         * @param physics_system
         * @param sprite
         * @param color_transformation
         * @param scale_transformation
         */
        ParticleSystem(SpriteRenderSystem &render_system, PhysicsSystem &physics_system,
                       const int particle_count,
                       sf::Sprite sprite,
                       const int sprite_depth,
                       sf::Time lifetime,
                       std::function<sf::Color(float)> color_transformation = [](float x){
                           (void)x;
                           return sf::Color::White;
                       },
                       std::function<sf::Vector2f(float)> scale_transformation = [](float x){
                           (void)x;
                           return sf::Vector2f(1.f, 1.f);
                       }) :
            render_system(render_system),
            physics_system(physics_system),
            particle_count(particle_count),
            sprite(std::move(sprite)),
            sprite_depth(sprite_depth),
            // Todo(erik): velocity?
            color_transformation(color_transformation),
            scale_transformation(scale_transformation),
            gen(rd()),
            lifetime_dist(lifetime.asSeconds() * 0.5f, lifetime.asSeconds() * 1.5f)
        {

        }

        void Initialize() {
            emitters.clear();
            emitters.shrink_to_fit();
            particles.clear();
            particles.shrink_to_fit();

            // Create particle entities
            for (auto i = 0; i < particle_count; ++i) {
                auto entity = std::make_shared<Entity>();

                entity->AddComponent<Sprite>(sprite, sprite_depth);
                entity->AddComponent<Timer>(sf::seconds(lifetime_dist(gen)));
                entity->AddComponent<Location>();

                auto size = sprite.getGlobalBounds();
                auto dynamic_body = entity->AddComponent<DynamicBody>(physics_system.GetSpace(), sf::Vector2f(-300, 100), 1,
                                                                      sf::Vector2f(size.width, size.height));

                cpShapeSetCollisionType(dynamic_body->GetShape(), 0);
                cpShapeSetFilter(dynamic_body->GetShape(), );
                //cpShapeSetSensor(entity->GetComponent<DynamicBody>()->GetShape(), cpTrue);

                SpawnParticle(entity, sf::Vector2f(0, -200));

                physics_system.AddEntity(entity);
                render_system.AddEntity(entity);
                particles.push_back(entity);
            }
        }

        // Specify an entity to be used as an emitter
        void AddEntity(std::shared_ptr<Entity> entity) override {
            emitters.push_back(entity);
        };

        void Update() {

            // Check if any emitters need to be deleted.
            emitters.erase(
                    std::remove_if(
                            emitters.begin(),
                            emitters.end(),
                            [&](std::shared_ptr<Entity> emitter) {
                                return emitter->IsFlaggedForRemoval();
                            }),
                    emitters.end()
            );

            // Update the particles, recycling if necessary
            // TODO
            std::uniform_int_distribution<int> emitter_dist(0, static_cast<int>(emitters.size() - 1));
            for (auto &particle : particles) {
                auto percent_lifetime = particle->GetComponent<Timer>()->GetPercentElapsed();
                if ((percent_lifetime > 1.f) && emitters.size() > 0) {
                    // TODO(erik): randomly pick an emitter and get it's location
                    auto emitter_location = emitters[emitter_dist(rd)]->GetComponent<Location>();
                    SpawnParticle(particle, emitter_location->GetPosition());
                }

                auto sprite = particle->GetComponent<Sprite>();
                auto color = color_transformation(percent_lifetime);
                auto scale = scale_transformation(percent_lifetime);
                sprite->GetSprite().setColor(color);
                sprite->GetSprite().setScale(scale);
            }

        }
    };

}

#endif //GAME_PARTICLESYSTEM_H
