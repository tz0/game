
#include "Systems/PhysicsParticleSystem.h"

namespace tjg {

    PhysicsParticleSystem::PhysicsParticleSystem(SpriteRenderSystem &render_system, PhysicsSystem &physics_system,
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
            ParticleSystem(render_system,
                           particle_count,
                           std::move(sprite),
                           sprite_depth,
                           sprite_blend_mode,
                           particle_rate,
                           lifetime,
                           position_variation,
                           velocity_variation,
                           angular_velocity_variation,
                           std::move(color_transformation),
                           std::move(scale_transformation)),

            physics_system(physics_system) {
    }

    void PhysicsParticleSystem::SpawnParticle(std::shared_ptr<Entity> particle, sf::Vector2f position) {
        // Lifetime exceeded, recycle entity.
        particle->GetComponent<Timer>()->Restart();
        auto body = particle->GetComponent<DynamicBody>();
        cpBodySetPosition(body->GetBody(),
                          cpv(position.x + x_position_variation_dist(gen),
                              position.y + y_position_variation_dist(gen)));
        cpBodySetVelocity(body->GetBody(), cpvzero);
        cpBodySetAngularVelocity(body->GetBody(), angular_velocity_dist(gen));
        cpBodySetVelocity(body->GetBody(), cpv(x_velocity_variation_dist(gen), y_velocity_variation_dist(gen)));
    }

    void PhysicsParticleSystem::MakeParticle(const sf::Vector2f position) {
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

    void PhysicsParticleSystem::PrepareParticleForRemoval(std::shared_ptr<Entity> particle) {
        auto dynamic_body = particle->GetComponent<DynamicBody>();
        auto body = dynamic_body->GetBody();
        auto shape = dynamic_body->GetShape();
        auto space = cpBodyGetSpace(body);
        cpSpaceRemoveBody(space, body);
        cpSpaceRemoveShape(space, shape);

    }
}
