
#include "Systems/ParticleSystem.h"

namespace tjg {

    ParticleSystem::ParticleSystem(SpriteRenderSystem &render_system,
                                   const unsigned int particle_count,
                                   sf::Sprite sprite,
                                   const int sprite_depth,
                                   sf::BlendMode sprite_blend_mode,
                                   sf::Time particle_rate,
                                   sf::Time lifetime,
                                   sf::Vector2f position_variation,
                                   sf::Vector2f velocity_variation,
                                   const float angular_velocity_variation,
                                   std::function<sf::Color(float)> color_transformation,
                                   std::function<sf::Vector2f(float)> scale_transformation) :
            render_system(render_system),
            particle_count(particle_count),
            sprite(std::move(sprite)),
            sprite_depth(sprite_depth),
            sprite_blend_mode(sprite_blend_mode),
            color_transformation(std::move(color_transformation)),
            scale_transformation(std::move(scale_transformation)),
            particle_rate(particle_rate),
            gen(rd()),
            lifetime_dist(lifetime.asSeconds() * 0.5f, lifetime.asSeconds() * 1.5f),
            x_position_variation_dist(-position_variation.x, position_variation.x),
            y_position_variation_dist(-position_variation.y, position_variation.y),
            x_velocity_variation_dist(-velocity_variation.x, velocity_variation.x),
            y_velocity_variation_dist(-velocity_variation.y, velocity_variation.y),
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
        particle->GetComponent<Location>()->SetPosition(position);
        particle->GetComponent<Velocity>()->SetVelocity(sf::Vector2f(x_velocity_variation_dist(gen), y_velocity_variation_dist(gen)));
    }

    void ParticleSystem::MakeParticle(const sf::Vector2f position) {
        auto entity = std::make_shared<Entity>();

        entity->AddComponent<Sprite>(sprite, sprite_depth, sprite_blend_mode);
        entity->GetComponent<Sprite>()->GetSprite().setColor(sf::Color::Transparent);

        entity->AddComponent<Timer>(sf::seconds(lifetime_dist(gen)));
        entity->AddComponent<Location>();
        entity->AddComponent<Velocity>(x_velocity_variation_dist(gen), y_velocity_variation_dist(gen));

        render_system.AddEntity(entity);
        particles.emplace_back(entity);

        SpawnParticle(entity, position);
    }

    void ParticleSystem::Update(const sf::Time &elapsed) {

        // Check if any emitters need to be deleted.
        emitters.erase(
                std::remove_if(
                        emitters.begin(),
                        emitters.end(),
                        [](std::shared_ptr<Entity> emitter) {
                            return emitter->IsFlaggedForRemoval();
                        }),
                emitters.end()
        );

        // Update the particles, recycling if necessary
        std::uniform_int_distribution<unsigned int> emitter_dist(0, emitters.size() > 0 ? emitters.size() - 1 : 0);

        const auto needed_particles = static_cast<unsigned int>(particle_count * emitters.size());

        particles.erase(
                std::remove_if(
                        particles.begin(),
                        particles.end(),
                        [&](std::shared_ptr<Entity> particle) {

                            auto percent_lifetime = particle->GetComponent<Timer>()->GetPercentElapsed();

                            // Respawn particles that have exceeded their lifetime.
                            if ((percent_lifetime > 1.f)) {
                                // Check if the particle should be deleted instead of respawned.
                                if (particles.size() > needed_particles ||
                                    particle->IsFlaggedForRemoval() ||
                                    !enabled ||
                                    emitters.empty() ||
                                    particle_timer.getElapsedTime() < particle_rate) {
                                    PrepareParticleForRemoval(particle);
                                    particle->FlagForRemoval();
                                    return true;
                                }

                                particle_timer.restart();
                                auto emitter_location = emitters[emitter_dist(gen)]->GetComponent<Location>();
                                SpawnParticle(particle, emitter_location->GetPosition());
                            }

                            // Update particles sprite based on the system's color/scale transformation functions.
                            auto sprite = particle->GetComponent<Sprite>();
                            auto color = color_transformation(percent_lifetime);
                            auto scale = scale_transformation(percent_lifetime);
                            sprite->GetSprite().setColor(color);
                            sprite->GetSprite().setScale(scale);

                            auto location = particle->GetComponent<Location>();
                            auto velocity = particle->GetComponent<Velocity>();

                            // This check is necessary because physical particles do not have a velocity component.
                            if (velocity != nullptr) {
                                auto pos = location->GetPosition();
                                location->SetPosition(pos + elapsed.asSeconds() * velocity->GetVelocity());
                            }
                            return false;
                        }),
                particles.end()
        );

        // Create new particles if there are less than needed.
        if (particles.size() < needed_particles && enabled && particle_timer.getElapsedTime() > particle_rate) {
            particle_timer.restart();
            auto emitter_location = emitters[emitter_dist(gen)]->GetComponent<Location>();
            MakeParticle(emitter_location->GetPosition());
        }
    }

    void ParticleSystem::Enable() {
        enabled = true;
    }

    void ParticleSystem::Disable() {
        enabled = false;
    }
}
