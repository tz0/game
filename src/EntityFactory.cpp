#include "Components/FiniteResource.h"
#include "EntityFactory.h"

namespace tjg {

    std::shared_ptr<Entity>
    EntityFactory::MakeWall(const sf::Vector2f &origin_point, const sf::Vector2f &end_point, float radius,
                            const bool lethal) {

        // lethal walls/laser walls disregard the specified radius and use a constant radius value
        radius = lethal ? 16 : radius;

        // Create wall entity.
        auto wall = std::make_shared<Entity>();

        // Add location component
        auto wall_location = wall->AddComponent<Location>((origin_point.x + end_point.x) / 2.0f,
                                                          (origin_point.y + end_point.y) / 2.0f);
        wall_location->SetRotation(calculateAngle(origin_point, end_point));

        // Add static segment component
        auto static_segment = wall->AddComponent<StaticSegment>(physics_system.GetSpace(), origin_point.x,
                                                                origin_point.y, end_point.x, end_point.y, radius);
        cpShapeSetCollisionType(static_segment->GetShape(),
                                static_cast<cpCollisionType>(lethal ? CollisionGroup::LETHAL : CollisionGroup::WALL));

        // Load wall texture.
        auto wall_texture = resource_manager.LoadTexture(lethal ? "laser.jpg" : "white-tile.jpg");
        wall_texture->setRepeated(!lethal);

        // Get wall length.
        auto length = (int) calculateDistance(origin_point, end_point);

        // Add Sprite component so walls are visible
        sf::Sprite wall_sprite;
        wall_sprite.setTexture(*wall_texture);
        wall_sprite.setTextureRect(sf::IntRect(0, 0,
                                               (unsigned int) (length + radius * 2),
                                               lethal ? (*wall_texture).getSize().y : (unsigned int) radius * 2));
        wall_sprite.setColor(lethal ? sf::Color(255, 150, 150) : sf::Color(150, 150, 150)); // Dark gray
        wall->AddComponent<Sprite>(wall_sprite, 0, lethal ? sf::BlendAdd : sf::BlendAlpha);

        // Add endcaps if it's a laser wall
        if (lethal) {
            auto wall_angle_radians = atan2(end_point.y - origin_point.y, end_point.x - origin_point.x);
            auto perpendicular_radians = wall_angle_radians + M_PI / 2;
            auto wall_angle_degrees = wall_angle_radians * 180 / M_PI;
            auto origin_cap = std::make_shared<Entity>();
            auto end_cap = std::make_shared<Entity>();

            sf::Sprite cap_sprite(*resource_manager.LoadTexture("spritesheet.png"),
                                  sf::IntRect(289, 364, 382 - 289, 424 - 364));

            // Build origin cap
            origin_cap->AddComponent<Sprite>(cap_sprite);
            auto origin_cap_location = origin_cap->AddComponent<Location>(origin_point);
            origin_cap_location->SetRotation(static_cast<float>(90 + wall_angle_degrees));
            auto origin_cap_segment = origin_cap->AddComponent<StaticSegment>(physics_system.GetSpace(),
                                                    origin_point.x + radius * cos(perpendicular_radians),
                                                    origin_point.y + radius * sin(perpendicular_radians),
                                                    origin_point.x - radius * cos(perpendicular_radians),
                                                    origin_point.y - radius * sin(perpendicular_radians), 30);

            // Build end cap
            end_cap->AddComponent<Sprite>(cap_sprite);
            auto end_cap_location = end_cap->AddComponent<Location>(end_point);
            end_cap_location->SetRotation(static_cast<float>(90 + wall_angle_degrees + 180));
            auto end_cap_segment = end_cap->AddComponent<StaticSegment>(physics_system.GetSpace(),
                                                    end_point.x + radius * cos(perpendicular_radians),
                                                    end_point.y + radius * sin(perpendicular_radians),
                                                    end_point.x - radius * cos(perpendicular_radians),
                                                    end_point.y - radius * sin(perpendicular_radians), 30);

            // Add the endcaps to the WALL CollisionGroup so they work with collision checking.
            cpShapeSetCollisionType(origin_cap_segment->GetShape(), static_cast<cpCollisionType>(CollisionGroup::WALL));
            cpShapeSetCollisionType(end_cap_segment->GetShape(), static_cast<cpCollisionType>(CollisionGroup::WALL));

            wall->AddChild(origin_cap);
            wall->AddChild(end_cap);
        }

        return wall;
    }

    std::shared_ptr<Entity>
    EntityFactory::MakeStaticDecoration(sf::Sprite sprite, const sf::Vector2f &position, const float rotation) {
        auto rect = std::make_shared<Entity>();
        auto loc = rect->AddComponent<Location>(position.x, position.y);
        loc->SetRotation(rotation);
        rect->AddComponent<Sprite>(sprite, -30);
        return rect;
    }

    std::shared_ptr<Entity> EntityFactory::MakeTiledBackground(const std::string &texture_path) {
        // Load texture
        auto background_texture = resource_manager.LoadTexture(texture_path);
        background_texture->setRepeated(true);

        // Create entity
        auto background = std::make_shared<Entity>();
        background->AddComponent<Location>();
        sf::Sprite background_sprite;
        background_sprite.setTexture(*background_texture);
        background_sprite.setTextureRect(sf::IntRect(INT16_MIN, INT16_MIN, INT16_MAX, INT16_MAX));
        background_sprite.setColor(sf::Color(220, 220, 220)); // Light gray
        background->AddComponent<Sprite>(background_sprite, -1000);
        return background;
    }

/**
 * MakeTech17 Creates an Entity representing the player character.
 * Tech17 is a ragdoll and is constructed as follows:
 *      All limbs are attached directly/indirectly to the "chest"
 *      The "chest" has a Rotational "Moment" of INFINITY, preventing the entire body from spinning
 *      Body part sizes and characteristics are defined via the constants
 *
 *      The tech17 entity contains the components necessary for the chest.
 *      Other body parts are created and added as children entities.
 *          All of the body parts contain the following components:
 *              Sprite - represent its location
 *              DynamicBody - physics simulation
 *              Appendage - a physical constraint which links it to another body part (The chest does not have
 *                          an appendage component because it is the root object)
 *
 *      Defining sprites - The location of each body part sprite on the texture must be defined by adjusting
 *      the values of X_sprite_rect so that it corresponds to the correct rectangle on the texture.
 *
 *      SPRITE_SCALE_FACTOR - the size constants are used to set the size for both the physical objects as well
 *      as the sprites. The SPRITE_SCALE_FACTOR can be used to set an additional scaling to the sprites. This
 *      can be used to improve the appearance of the ragdoll by adjusting the sprites to be slightly bigger
 *      than the physical objects they represent.
 *
 *      TECH17_BASE_SPRITE_LAYER - used to define the SpriteRenderSystem layer at which to draw the sprites.
 *      The chest is rendered at this layer, and other body parts are placed in layers relative to this such
 *      that the parts are drawn in this order:
 *          HELMET
 *          CHEST
 *          BICEPS/THIGHS
 *          FOREARMS/SHINS
 *
 * The current poisition of Tech_17 is consistent with entrance location.  All body parts are automatically 
 * adaptive to the new entrance position when reading level files.
 * @return Tech17 Entity
 */
    std::shared_ptr<Entity> EntityFactory::MakeTech17(const float &tech17_x, const float &tech17_y) {
        auto spacesuit_texture = resource_manager.LoadTexture("spritesheet.png");
        auto tech17 = std::make_shared<Entity>();

        tech17->AddComponent<Location>();

        const auto CHEST_WIDTH = 50.0f;
        const auto CHEST_HEIGHT = 40.0f;
        const auto ABS_WIDTH = 40.0f;
        const auto ABS_HEIGHT = 30.0f;
        const auto HEAD_RADIUS = 30.0f;
        const auto LIMB_THICKNESS = 10.0f;
        const auto LIMB_LENGTH = 40.0f;
        const auto ARM_ANGLE = M_PI / 3.0f;
        // The limb's range of movement = its base angle +- LIMB_ROTATION_LIMIT
        const auto LIMB_ROTATION_LIMIT = M_PI / 10.0f;

        const auto LIMB_STIFFNESS = 5000.0f; // lower = more loose
        const auto SPRITE_SCALE_FACTOR = 1.2f;
        const auto TECH17_BASE_SPRITE_LAYER = 50;

        //
        // CREATE CHEST
        //
        sf::Sprite chest_sprite;
        chest_sprite.setTexture(*spacesuit_texture);
        auto chest_sprite_rect = sf::IntRect(160, 8, 304 - 160, 135 - 8);
        chest_sprite.setTextureRect(chest_sprite_rect);
        chest_sprite.setScale(SPRITE_SCALE_FACTOR * CHEST_WIDTH / static_cast<float>(chest_sprite_rect.width),
                              SPRITE_SCALE_FACTOR * CHEST_HEIGHT / static_cast<float>(chest_sprite_rect.height));
        tech17->AddComponent<Sprite>(chest_sprite, TECH17_BASE_SPRITE_LAYER);
        auto torso_body = tech17->AddComponent<DynamicBody>(
                physics_system.GetSpace(),
                sf::Vector2f(tech17_x, tech17_y), // sf::Vector2f(0, 0),
                1,
                sf::Vector2f(CHEST_WIDTH, CHEST_HEIGHT));
        cpShapeSetCollisionType(torso_body->GetShape(), static_cast<cpCollisionType>(CollisionGroup::TECH17));
        physics_system.AddEntity(tech17);

        //
        // CREATE ABS
        //
        auto abs_entity = std::make_shared<Entity>();
        abs_entity->AddComponent<Location>();
        sf::Sprite abs_sprite;
        abs_sprite.setTexture(*spacesuit_texture);
        auto abs_sprite_rect = sf::IntRect(316, 10, 432 - 316, 87 - 10);
        abs_sprite.setTextureRect(abs_sprite_rect);
        abs_sprite.setScale(SPRITE_SCALE_FACTOR * ABS_WIDTH / static_cast<float>(abs_sprite_rect.width),
                            SPRITE_SCALE_FACTOR * ABS_HEIGHT / static_cast<float>(abs_sprite_rect.height));
        abs_entity->AddComponent<Sprite>(abs_sprite, TECH17_BASE_SPRITE_LAYER - 1);
        auto abs_body = abs_entity->AddComponent<DynamicBody>(
                physics_system.GetSpace(),
                sf::Vector2f(tech17_x, tech17_y + ABS_HEIGHT),
                1,
                sf::Vector2f(CHEST_WIDTH, ABS_HEIGHT));
        abs_entity->AddComponent<Appendage>(
                physics_system.GetSpace(),
                abs_body->GetBody(),
                torso_body->GetBody(),
                sf::Vector2f(0, -1 * ABS_HEIGHT / 2.0f),
                sf::Vector2f(0, CHEST_HEIGHT / 2.0f),
                LIMB_STIFFNESS * 10.0f,
                0.0f,
                LIMB_ROTATION_LIMIT);
        cpShapeSetCollisionType(abs_body->GetShape(), static_cast<cpCollisionType>(CollisionGroup::TECH17));
        physics_system.AddEntity(abs_entity);
        tech17->AddChild(abs_entity);

        //
        // CREATE HEAD
        //
        auto head_entity = std::make_shared<Entity>();
        head_entity->AddComponent<Location>();
        sf::Sprite head_sprite;
        head_sprite.setTexture(*spacesuit_texture);
        auto head_sprite_rect = sf::IntRect(10, 10, 140, 140);
        head_sprite.setTextureRect(head_sprite_rect);
        head_sprite.setScale(SPRITE_SCALE_FACTOR * 2 * HEAD_RADIUS / static_cast<float>(head_sprite_rect.width),
                             SPRITE_SCALE_FACTOR * 2 * HEAD_RADIUS / static_cast<float>(head_sprite_rect.height));
        head_entity->AddComponent<Sprite>(head_sprite, TECH17_BASE_SPRITE_LAYER + 1);
        auto head_body = head_entity->AddComponent<DynamicBody>(
                physics_system.GetSpace(),
                sf::Vector2f(tech17_x, tech17_y - 1 * (CHEST_HEIGHT / 2.0f + HEAD_RADIUS)),
                1,
                HEAD_RADIUS);
        head_entity->AddComponent<Appendage>(
                physics_system.GetSpace(),
                head_body->GetBody(),
                torso_body->GetBody(),
                sf::Vector2f(0, HEAD_RADIUS),
                sf::Vector2f(0, -1 * CHEST_HEIGHT / 2.0f),
                LIMB_STIFFNESS,
                0.0f,
                LIMB_ROTATION_LIMIT);
        cpShapeSetCollisionType(head_body->GetShape(), static_cast<cpCollisionType>(CollisionGroup::TECH17));
        physics_system.AddEntity(head_entity);
        tech17->AddChild(head_entity);


        // BICEPS
        sf::Sprite bicep_sprite;
        bicep_sprite.setTexture(*spacesuit_texture);
        auto bicep_sprite_rect = sf::IntRect(114, 154, 221 - 114, 204 - 154);
        bicep_sprite.setTextureRect(bicep_sprite_rect);
        bicep_sprite.setScale(SPRITE_SCALE_FACTOR * LIMB_LENGTH / static_cast<float>(bicep_sprite_rect.width),
                              SPRITE_SCALE_FACTOR * LIMB_THICKNESS / static_cast<float>(bicep_sprite_rect.height));
        //
        // CREATE LEFT BICEP
        //
        auto left_bicep_entity = std::make_shared<Entity>();
        left_bicep_entity->AddComponent<Location>();
        left_bicep_entity->AddComponent<Sprite>(bicep_sprite, TECH17_BASE_SPRITE_LAYER - 1);
        auto left_bicep_body = left_bicep_entity->AddComponent<DynamicBody>(
                physics_system.GetSpace(),
                sf::Vector2f(tech17_x - 1 * (CHEST_WIDTH / 2.0f + LIMB_LENGTH / 2.0f),
                             tech17_y - 1 * (CHEST_HEIGHT / 2.0f)),
                1,
                sf::Vector2f(LIMB_LENGTH, LIMB_THICKNESS));
        left_bicep_entity->AddComponent<Appendage>(
                physics_system.GetSpace(),
                left_bicep_body->GetBody(),
                torso_body->GetBody(),
                sf::Vector2f(LIMB_LENGTH / 2.0f, 0),
                sf::Vector2f(-1 * CHEST_WIDTH / 2.0f, -1 * CHEST_HEIGHT / 2.0f),
                LIMB_STIFFNESS,
                // Set the angle to keep the arm at his side.
                -1 * ARM_ANGLE,
                LIMB_ROTATION_LIMIT);
        cpShapeSetCollisionType(left_bicep_body->GetShape(), static_cast<cpCollisionType>(CollisionGroup::TECH17));
        physics_system.AddEntity(left_bicep_entity);
        tech17->AddChild(left_bicep_entity);

        //
        // CREATE RIGHT BICEP
        //
        auto right_bicep_entity = std::make_shared<Entity>();
        right_bicep_entity->AddComponent<Location>();
        // Flip the sprite horizontally
        bicep_sprite.setScale(-1 * bicep_sprite.getScale().x, bicep_sprite.getScale().y);
        right_bicep_entity->AddComponent<Sprite>(bicep_sprite, TECH17_BASE_SPRITE_LAYER - 1);
        auto right_bicep_body = right_bicep_entity->AddComponent<DynamicBody>(
                physics_system.GetSpace(),
                sf::Vector2f(tech17_x + (CHEST_WIDTH / 2.0f + LIMB_LENGTH / 2.0f),
                             tech17_y - 1 * (CHEST_HEIGHT / 2.0f)),
                1,
                sf::Vector2f(LIMB_LENGTH, LIMB_THICKNESS));
        right_bicep_entity->AddComponent<Appendage>(
                physics_system.GetSpace(),
                right_bicep_body->GetBody(),
                torso_body->GetBody(),
                sf::Vector2f(-1 * LIMB_LENGTH / 2.0f, 0),
                sf::Vector2f(CHEST_WIDTH / 2.0f, -1 * CHEST_HEIGHT / 2.0f),
                LIMB_STIFFNESS,
                ARM_ANGLE,
                LIMB_ROTATION_LIMIT);
        cpShapeSetCollisionType(right_bicep_body->GetShape(), static_cast<cpCollisionType>(CollisionGroup::TECH17));
        physics_system.AddEntity(right_bicep_entity);
        tech17->AddChild(right_bicep_entity);

        // FOREARMS
        sf::Sprite forearm_sprite;
        forearm_sprite.setTexture(*spacesuit_texture);
        //TODO: These coordinates are not correct
        auto forearm_sprite_rect = sf::IntRect(114, 154, 221 - 114, 204 - 154);
        forearm_sprite.setTextureRect(forearm_sprite_rect);
        forearm_sprite.setScale(SPRITE_SCALE_FACTOR * LIMB_LENGTH / static_cast<float>(forearm_sprite_rect.width),
                                SPRITE_SCALE_FACTOR * LIMB_THICKNESS / static_cast<float>(forearm_sprite_rect.height));
        //
        // CREATE LEFT FOREARM
        //
        auto left_forearm_entity = std::make_shared<Entity>();
        left_forearm_entity->AddComponent<Location>();
        left_forearm_entity->AddComponent<Sprite>(forearm_sprite, TECH17_BASE_SPRITE_LAYER - 2);
        auto left_forearm_body = left_forearm_entity->AddComponent<DynamicBody>(
                physics_system.GetSpace(),
                sf::Vector2f(tech17_x - 1 * (CHEST_WIDTH / 2.0f + LIMB_LENGTH + LIMB_LENGTH / 2.0f),
                             tech17_y - 1 * (CHEST_HEIGHT / 2.0f)),
                1,
                sf::Vector2f(LIMB_LENGTH, LIMB_THICKNESS));
        left_forearm_entity->AddComponent<Appendage>(
                physics_system.GetSpace(),
                left_forearm_body->GetBody(),
                left_bicep_body->GetBody(),
                sf::Vector2f(LIMB_LENGTH / 2.0f, 0),
                sf::Vector2f(-1 * (LIMB_LENGTH / 2.0f), 0),
                LIMB_STIFFNESS,
                -1 * ARM_ANGLE / 2.0f,
                LIMB_ROTATION_LIMIT);
        cpShapeSetCollisionType(left_forearm_body->GetShape(), static_cast<cpCollisionType>(CollisionGroup::TECH17));
        physics_system.AddEntity(left_forearm_entity);
        tech17->AddChild(left_forearm_entity);

        //
        // CREATE RIGHT FOREARM
        //
        auto right_forearm_entity = std::make_shared<Entity>();
        right_forearm_entity->AddComponent<Location>();
        // Flip the sprite horizontally
        forearm_sprite.setScale(-1 * forearm_sprite.getScale().x, forearm_sprite.getScale().y);
        right_forearm_entity->AddComponent<Sprite>(forearm_sprite, TECH17_BASE_SPRITE_LAYER - 2);
        auto right_forearm_body = right_forearm_entity->AddComponent<DynamicBody>(
                physics_system.GetSpace(),
                sf::Vector2f(tech17_x + (CHEST_WIDTH / 2.0f + LIMB_LENGTH + LIMB_LENGTH / 2.0f),
                             tech17_y - 1 * (CHEST_HEIGHT / 2.0f)),
                1,
                sf::Vector2f(LIMB_LENGTH, LIMB_THICKNESS));
        right_forearm_entity->AddComponent<Appendage>(
                physics_system.GetSpace(),
                right_forearm_body->GetBody(),
                right_bicep_body->GetBody(),
                sf::Vector2f(-1 * (LIMB_LENGTH / 2.0f), 0),
                sf::Vector2f(LIMB_LENGTH / 2.0f, 0),
                LIMB_STIFFNESS,
                ARM_ANGLE / 2.0f,
                LIMB_ROTATION_LIMIT);
        cpShapeSetCollisionType(right_forearm_body->GetShape(), static_cast<cpCollisionType>(CollisionGroup::TECH17));
        physics_system.AddEntity(right_forearm_entity);
        tech17->AddChild(right_forearm_entity);

        // THIGHS
        sf::Sprite thigh_sprite;
        thigh_sprite.setTexture(*spacesuit_texture);
        auto thigh_sprite_rect = sf::IntRect(10, 206, 55 - 10, 337 - 206);
        thigh_sprite.setTextureRect(thigh_sprite_rect);
        thigh_sprite.setScale(SPRITE_SCALE_FACTOR * LIMB_THICKNESS / static_cast<float>(thigh_sprite_rect.width),
                              SPRITE_SCALE_FACTOR * LIMB_LENGTH / static_cast<float>(thigh_sprite_rect.height));
        //
        // CREATE LEFT THIGH
        //
        auto left_thigh_entity = std::make_shared<Entity>();
        left_thigh_entity->AddComponent<Location>();
        left_thigh_entity->AddComponent<Sprite>(thigh_sprite, TECH17_BASE_SPRITE_LAYER - 2);
        auto left_thigh_body = left_thigh_entity->AddComponent<DynamicBody>(
                physics_system.GetSpace(),
                sf::Vector2f(tech17_x - 1 * ABS_WIDTH / 2.0f,
                             tech17_y + CHEST_HEIGHT + ABS_HEIGHT + LIMB_LENGTH / 2.0f),
                1,
                sf::Vector2f(LIMB_THICKNESS, LIMB_LENGTH));
        left_thigh_entity->AddComponent<Appendage>(
                physics_system.GetSpace(),
                left_thigh_body->GetBody(),
                abs_body->GetBody(),
                sf::Vector2f(0, -1 * LIMB_LENGTH / 2.0f),
                sf::Vector2f(-1 * ABS_WIDTH / 2.0f, ABS_HEIGHT / 2.0f),
                LIMB_STIFFNESS,
                0.0f,
                LIMB_ROTATION_LIMIT);
        cpShapeSetCollisionType(left_thigh_body->GetShape(), static_cast<cpCollisionType>(CollisionGroup::TECH17));
        physics_system.AddEntity(left_thigh_entity);
        tech17->AddChild(left_thigh_entity);

        //
        // CREATE RIGHT THIGH
        //
        auto right_thigh_entity = std::make_shared<Entity>();
        right_thigh_entity->AddComponent<Location>();
        // Flip the sprite horizontally
        thigh_sprite.setScale(-1 * thigh_sprite.getScale().x, thigh_sprite.getScale().y);
        right_thigh_entity->AddComponent<Sprite>(thigh_sprite, TECH17_BASE_SPRITE_LAYER - 2);
        auto right_thigh_body = right_thigh_entity->AddComponent<DynamicBody>(
                physics_system.GetSpace(),
                sf::Vector2f(tech17_x + ABS_WIDTH / 2.0f, tech17_y + CHEST_HEIGHT + ABS_HEIGHT + LIMB_LENGTH / 2.0f),
                1,
                sf::Vector2f(LIMB_THICKNESS, LIMB_LENGTH));
        right_thigh_entity->AddComponent<Appendage>(
                physics_system.GetSpace(),
                right_thigh_body->GetBody(),
                abs_body->GetBody(),
                sf::Vector2f(0, -1 * LIMB_LENGTH / 2.0f),
                sf::Vector2f(ABS_WIDTH / 2.0f, ABS_HEIGHT / 2.0f),
                LIMB_STIFFNESS,
                0.0f,
                LIMB_ROTATION_LIMIT);
        cpShapeSetCollisionType(right_thigh_body->GetShape(), static_cast<cpCollisionType>(CollisionGroup::TECH17));
        physics_system.AddEntity(right_thigh_entity);
        tech17->AddChild(right_thigh_entity);

        // SHINS
        sf::Sprite shin_sprite;
        shin_sprite.setTexture(*spacesuit_texture);
        //TODO: These coordinates are not correct.
        auto shin_sprite_rect = sf::IntRect(10, 206, 55 - 10, 337 - 206);
        shin_sprite.setTextureRect(shin_sprite_rect);
        shin_sprite.setScale(SPRITE_SCALE_FACTOR * LIMB_THICKNESS / static_cast<float>(shin_sprite_rect.width),
                             SPRITE_SCALE_FACTOR * LIMB_LENGTH / static_cast<float>(shin_sprite_rect.height));
        //
        // CREATE LEFT SHIN
        //
        auto left_shin_entity = std::make_shared<Entity>();
        left_shin_entity->AddComponent<Location>();
        left_shin_entity->AddComponent<Sprite>(shin_sprite, TECH17_BASE_SPRITE_LAYER - 3);
        auto left_shin_body = left_shin_entity->AddComponent<DynamicBody>(
                physics_system.GetSpace(),
                sf::Vector2f(tech17_x - 1 * ABS_WIDTH / 2.0f,
                             tech17_y + CHEST_HEIGHT + ABS_HEIGHT + LIMB_LENGTH + LIMB_LENGTH / 2.0f),
                1,
                sf::Vector2f(LIMB_THICKNESS, LIMB_LENGTH));
        left_shin_entity->AddComponent<Appendage>(
                physics_system.GetSpace(),
                left_shin_body->GetBody(),
                left_thigh_body->GetBody(),
                sf::Vector2f(0, -1 * LIMB_LENGTH / 2.0f),
                sf::Vector2f(0, LIMB_LENGTH / 2.0f),
                LIMB_STIFFNESS,
                0.0f,
                LIMB_ROTATION_LIMIT);
        cpShapeSetCollisionType(left_shin_body->GetShape(), static_cast<cpCollisionType>(CollisionGroup::TECH17));
        physics_system.AddEntity(left_shin_entity);
        tech17->AddChild(left_shin_entity);

        //
        // CREATE RIGHT SHIN
        //
        auto right_shin_entity = std::make_shared<Entity>();
        right_shin_entity->AddComponent<Location>();
        // Flip the sprite horizontally
        shin_sprite.setScale(-1 * shin_sprite.getScale().x, shin_sprite.getScale().y);
        right_shin_entity->AddComponent<Sprite>(shin_sprite, TECH17_BASE_SPRITE_LAYER - 3);
        auto right_shin_body = right_shin_entity->AddComponent<DynamicBody>(
                physics_system.GetSpace(),
                sf::Vector2f(tech17_x + ABS_WIDTH / 2.0f,
                             tech17_y + CHEST_HEIGHT + ABS_HEIGHT + LIMB_LENGTH + LIMB_LENGTH / 2.0f),
                1,
                sf::Vector2f(LIMB_THICKNESS, LIMB_LENGTH));
        right_shin_entity->AddComponent<Appendage>(
                physics_system.GetSpace(),
                right_shin_body->GetBody(),
                right_thigh_body->GetBody(),
                sf::Vector2f(0, -1 * LIMB_LENGTH / 2.0f),
                sf::Vector2f(0, LIMB_LENGTH / 2.0f),
                LIMB_STIFFNESS,
                0.0f,
                LIMB_ROTATION_LIMIT);
        cpShapeSetCollisionType(right_shin_body->GetShape(), static_cast<cpCollisionType>(CollisionGroup::TECH17));
        physics_system.AddEntity(right_shin_entity);
        tech17->AddChild(right_shin_entity);

        return tech17;
    }

    std::shared_ptr<Entity> EntityFactory::MakePressureSource(const sf::Vector2f &origin, float radius,
                                                              float strength) {
        // Load texture sheet.
        auto texture_sheet = resource_manager.LoadTexture("spritesheet.png");

        // Build pressure source
        auto pressure_source = std::make_shared<Entity>();

        // Add location component pointing to the origin.
        pressure_source->AddComponent<Location>(origin);

        // Add sprite component (load from texture sheet).
        auto pressure_source_sprite = pressure_source->AddComponent<Sprite>(
                strength < 0
                ? sf::Sprite(*texture_sheet, sf::IntRect(461, 0, 702 - 461, 245))
                : sf::Sprite(*texture_sheet, sf::IntRect(162, 360, 286 - 162, 493 - 360))
        );

        // Create linear force component for physics system
        auto radial_force = pressure_source->AddComponent<RadialForce>(physics_system.GetSpace(), origin, radius,
                                                                       strength);

        // Create sensor shape component (the physics system uses this to check if a DynamicBody is inside the sensor shape).
        pressure_source->AddComponent<SensorShape>(radial_force->GetShape(), [=](cpShape *shape) {
            // Apply a force to each shape overlapping with this pressure source

            // Calculate force to be applied by a linear equation.
            // At the pressure source's origin_point, a force of origin_strength will be applied.
            // At the outside of a pressure sources's radius, a force of 0 will be applied.
            auto shape_position = cpBodyGetPosition(cpShapeGetBody(shape));
            auto force_direction = cpvnormalize(shape_position - cpv(origin.x, origin.y));

            // Calculate the amount of force to apply.
            auto origin_end_dist = radius;
            auto origin_shape_dist = cpvdist(cpv(origin.x, origin.y), shape_position);
            auto force = force_direction * ((((origin_end_dist - origin_shape_dist) / origin_end_dist) *
                                                            strength));
            // Apply the force to the affected shape.
            cpBodyApplyForceAtWorldPoint(cpShapeGetBody(shape), force, cpBodyGetPosition(cpShapeGetBody(shape)));
        });
        physics_system.AddEntity(pressure_source);

        return pressure_source;
    }


    std::shared_ptr<Entity>
    EntityFactory::MakeFan(const sf::Vector2f &origin_point, const sf::Vector2f &end_point, const float width,
                           const float origin_strength, const float end_strength) {
        // Load texture sheet.
        auto texture_sheet = resource_manager.LoadTexture("spritesheet.png");

        // Build fan entity.
        auto fan = std::make_shared<Entity>();

        // Add location component pointing to the origin.
        auto fan_location = fan->AddComponent<Location>(origin_point);
        fan_location->SetRotation(calculateAngle(origin_point, end_point));

        // Add sprite component (load from texture sheet).
        auto fan_sprite = fan->AddComponent<Sprite>(
                std::vector<sf::Sprite> {
                        // Define frames of animation
                        sf::Sprite(*texture_sheet, sf::IntRect(234, 146, 344 - 234, 360 - 146)),
                        sf::Sprite(*texture_sheet, sf::IntRect(344, 146, 448 - 344, 360 - 146)),
                },
                20
        );

        // Set the size and start the animation
        fan_sprite->SetSize(sf::Vector2f(width / 2.0f, width));
        fan_sprite->Play(true);

        // Create linear force component for physics system
        auto linear_force = fan->AddComponent<LinearForce>(physics_system.GetSpace(), origin_point, end_point, width,
                                                           origin_strength, end_strength);

        // Create sensor shape component (the physics system uses this to check if a DynamicBody is inside the sensor shape).
        fan->AddComponent<SensorShape>(linear_force->GetShape(), [=](cpShape *shape) {
            // Apply a force to each shape overlapping with this linear force shape.

            // Convert the sf::Vector2f to a cpVect
            auto force_origin = cpv(origin_point.x, origin_point.y);
            auto force_end = cpv(end_point.x, end_point.y);

            // Calculate force to be applied by a linear equation.
            // At the fan's origin_point, a force of origin_strength will be applied.
            // At the fan's end_point, a force of end_strength will be applied.
            auto force_direction = fan->GetComponent<LinearForce>()->GetForce();
            auto shape_position = cpBodyGetPosition(cpShapeGetBody(shape));

            // Calculate the amount of force to apply.
            auto origin_end_dist = cpvdist(force_origin, force_end);
            auto origin_shape_dist = cpvdist(force_origin, shape_position);
            auto force = force_direction * (end_strength + (((origin_end_dist - origin_shape_dist) / origin_end_dist) *
                                                            (origin_strength - end_strength)));

            // Apply the force to the affected shape.
            cpBodyApplyForceAtWorldPoint(cpShapeGetBody(shape), force, cpBodyGetPosition(cpShapeGetBody(shape)));
        });
        physics_system.AddEntity(fan);

        return fan;
    }

    std::shared_ptr<Entity> EntityFactory::MakeEntrance(const sf::Vector2f &position) {
        // Create entrance entity.
        auto entrance = std::make_shared<Entity>();

        // Add location component
        auto entrance_location = entrance->AddComponent<Location>(position.x, position.y);

        // Load texture.
        auto entrance_texture = resource_manager.LoadTexture("door-1.png");

        // Add Sprite component so walls are visible
        sf::Sprite entrance_sprite;
        entrance_sprite.setTexture(*entrance_texture);
        entrance_sprite.setTextureRect(sf::IntRect(0, 0, 128, 240));
        entrance->AddComponent<Sprite>(entrance_sprite, -25);

        return entrance;
    }

    std::shared_ptr<Entity> EntityFactory::MakeExit(const sf::Vector2f &position) {
        // Create exit entity.
        auto exit = std::make_shared<Entity>();

        // Add location component
        auto exit_location = exit->AddComponent<Location>(position.x, position.y);

        // Load texture.
        auto exit_texture = resource_manager.LoadTexture("door-1.png");

        // Add Sprite component
        sf::Sprite exit_sprite;
        exit_sprite.setTexture(*exit_texture);
        exit_sprite.setTextureRect(sf::IntRect(0, 0, 128, 240));
        exit->AddComponent<Sprite>(exit_sprite, -25);

        // StaticSegment component.
        auto segment = exit->AddComponent<StaticSegment>(physics_system.GetSpace(), position + sf::Vector2f(0, -10),
                                                         position + sf::Vector2f(0, 10), 20);
        cpShapeSetCollisionType(segment->GetShape(), static_cast<cpCollisionType>(CollisionGroup::EXIT));

        return exit;
    }

    std::shared_ptr<Entity> EntityFactory::MakeShockBox(const sf::Vector2f &position) {
        // Create shock box entity.
        auto shock_box = std::make_shared<Entity>();

        // Add location component
        auto shock_box_location = shock_box->AddComponent<Location>(position.x, position.y);

        // Load texture.
        auto shock_box_texture = resource_manager.LoadTexture("shock-box.png");

        // Add Sprite component
        sf::Sprite shock_box_sprite;
        shock_box_sprite.setTexture(*shock_box_texture);
        shock_box_sprite.setTextureRect(
                sf::IntRect(0, 0, shock_box_texture->getSize().x, shock_box_texture->getSize().y));
        shock_box_sprite.setScale(0.3, 0.3);
        shock_box->AddComponent<Sprite>(shock_box_sprite, -25);

        // StaticSegment component.
        sf::FloatRect shock_box_bounds = shock_box_sprite.getLocalBounds();
        auto segment = shock_box->AddComponent<StaticSegment>(physics_system.GetSpace(),
                                                              sf::Vector2f(position.x, position.y + 20),
                                                              sf::Vector2f(position.x, position.y - 20),
                                                              shock_box_bounds.width / 10);
        cpShapeSetCollisionType(segment->GetShape(), static_cast<cpCollisionType>(CollisionGroup::LETHAL));

        return shock_box;
    }

    std::shared_ptr<Entity>
    EntityFactory::MakeResourceTracker(float max_value, std::string &texture_path, const sf::Color &color) {
        // Create resource bar entity.
        auto resource_tracker = std::make_shared<Entity>();

        // Add Location component.
        auto location = resource_tracker->AddComponent<Location>(0, 0);

        // Add FiniteResource component.
        auto finite_resource = resource_tracker->AddComponent<FiniteResource>(max_value);

        // Load texture.
        auto texture = resource_manager.LoadTexture(texture_path);
        auto texture_size = texture->getSize();
        texture->setRepeated(true);

        // Add Sprite component.
        sf::Sprite sprite;
        sprite.setTexture(*texture);
        sprite.setTextureRect(sf::IntRect(0, 0, texture_size.x, texture_size.y));
        sprite.setColor(color);
        resource_tracker->AddComponent<Sprite>(sprite);

        return resource_tracker;
    }

    float EntityFactory::calculateAngle(sf::Vector2f p1, sf::Vector2f p2) {
        // Calculate the angle between p1 and p2
        double deltaY = p1.y - p2.y;
        double deltaX = p2.x - p1.x;
        double angle = atan2(deltaY, deltaX) * 180 / M_PI;
        return -static_cast<float>(angle);
    }

    float EntityFactory::calculateDistance(sf::Vector2f p1, sf::Vector2f p2) {
        // Calculate distance between p1 and p2
        return static_cast<float>(sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)));
    }
}
