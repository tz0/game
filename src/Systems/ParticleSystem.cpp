
#include "Systems/ParticleSystem.h"

namespace tjg {

    ParticleSystem::ParticleSystem(SpriteRenderSystem &render_system, PhysicsSystem &physics_system,
                                   const unsigned int particle_count,
                                   sf::Sprite sprite,
                                   const int sprite_depth,
                                   sf::BlendMode sprite_blend_mode,
                                   sf::Time lifetime,
                                   sf::Vector2f position_variation,
                                   const float angular_velocity_variation,
                                   std::function<sf::Color(float)> color_transformation,
                                   std::function<sf::Vector2f(float)> scale_transformation) :
            render_system(render_system),
            physics_system(physics_system),
            particle_count(particle_count),
            sprite(std::move(sprite)),
            sprite_depth(sprite_depth),
            sprite_blend_mode(sprite_blend_mode),
            // Todo(erik): velocity?
            color_transformation(std::move(color_transformation)),
            scale_transformation(std::move(scale_transformation)),
            gen(rd()),
            lifetime_dist(lifetime.asSeconds() * 0.5f, lifetime.asSeconds() * 1.5f),
            x_position_variation_dist(-position_variation.x, position_variation.x),
            y_position_variation_dist(-position_variation.y, position_variation.y),
            angular_velocity_dist(-angular_velocity_variation, angular_velocity_variation) {

    }

    void ParticleSystem::Initialize() {
        emitters.clear();
        emitters.shrink_to_fit();
        particles.clear();
        particles.shrink_to_fit();
    }

    void ParticleSystem::AddEntity(std::shared_ptr<Entity> entity) {
        emitters.push_back(entity);
    };

    void ParticleSystem::SpawnParticle(std::shared_ptr<Entity> particle, sf::Vector2f position) {
        // Lifetime exceeded, recycle entity.
        particle->GetComponent<Timer>()->Restart();
        auto body = particle->GetComponent<DynamicBody>();
        cpBodySetPosition(body->GetBody(),
                          cpv(position.x + x_position_variation_dist(rd), position.y + y_position_variation_dist(rd)));
        cpBodySetVelocity(body->GetBody(), cpvzero);
        cpBodySetAngularVelocity(body->GetBody(), angular_velocity_dist(rd));
    }

    void ParticleSystem::MakeParticle(const sf::Vector2f position) {
        auto entity = std::make_shared<Entity>();

        entity->AddComponent<Sprite>(sprite, sprite_depth, sprite_blend_mode);
        entity->GetComponent<Sprite>()->GetSprite().setColor(sf::Color::Transparent);


        entity->AddComponent<Timer>(sf::seconds(lifetime_dist(gen)));
        entity->AddComponent<Location>();

        auto dynamic_body = entity->AddComponent<DynamicBody>(physics_system.GetSpace(), sf::Vector2f(0, 0), 1,
                                                              sf::Vector2f(.1, .1));

        cpShapeSetSensor(entity->GetComponent<DynamicBody>()->GetShape(), cpTrue);

        physics_system.AddEntity(entity);
        render_system.AddEntity(entity);
        particles.emplace_back(entity);

        SpawnParticle(entity, position);
    }

    void ParticleSystem::Update() {

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
        std::uniform_int_distribution<int> emitter_dist(0, static_cast<int>(emitters.size() - 1));
        for (auto &particle : particles) {


            auto percent_lifetime = particle->GetComponent<Timer>()->GetPercentElapsed();

            // Respawn particles that have exceeded their lifetime.
            if ((percent_lifetime > 1.f) && emitters.size() > 0) {
                auto emitter_location = emitters[emitter_dist(rd)]->GetComponent<Location>();
                SpawnParticle(particle, emitter_location->GetPosition());
            }

            // Update particles sprite based on the system's color/scale transformation functions.
            auto sprite = particle->GetComponent<Sprite>();
            auto color = color_transformation(percent_lifetime);
            auto scale = scale_transformation(percent_lifetime);
            sprite->GetSprite().setColor(color);
            sprite->GetSprite().setScale(scale);

        }

        // Create new particles if there are less than needed.
        if (particles.size() < particle_count * emitters.size()) {
            auto emitter_location = emitters[emitter_dist(rd)]->GetComponent<Location>();
            MakeParticle(emitter_location->GetPosition());
        }
    }
}
