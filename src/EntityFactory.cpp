// Need these two lines for M_PI to work on Windows.
#define _USE_MATH_DEFINES
#include <cmath>

#include "EntityFactory.h"

std::shared_ptr <tjg::Entity> tjg::EntityFactory::MakeWall(const sf::Vector2f &a, const sf::Vector2f &b, const float width) {
    // Create wall entity.
    auto wall = std::make_shared<Entity>();

    // Add location component
    auto wall_location = wall->AddComponent<Location>((a.x + b.x) / 2.0f, (a.y + b.y) / 2.0f);
    wall_location->setRotation(calculateAngle(a, b));

    // Add static segment component
    wall->AddComponent<StaticSegment>(space, a.x, a.y, b.x, b.y, width);

    // Add line component
    wall->AddComponent<Line>(a.x, a.y, b.x, b.y);

    // Load wall texture.
    auto wall_texture = resource_manager.LoadTexture("wall-texture.png"); // TODO get a real wall texture
    wall_texture->setRepeated(true);

    // Get wall length.
    auto length = (int)calculateDistance(a, b);

    // Add Sprite component so walls are visible
    sf::Sprite wall_sprite;
    wall_sprite.setTexture(*wall_texture);
    wall_sprite.setTextureRect(sf::IntRect(0, 0, length, (int)width));
    wall_sprite.setRotation(calculateAngle(a, b));
    wall->AddComponent<Sprite>(wall_sprite);

    return wall;
}

// Build a static Sprite Entity
std::shared_ptr<tjg::Entity> tjg::EntityFactory::MakeStaticSprite(sf::Sprite sprite, const sf::Vector2f &position) {
    auto rect = std::make_shared<Entity>();
    rect->AddComponent<Location>(position.x, position.y);
    rect->AddComponent<Sprite>(sprite);
    return rect;
}

// Build a Tiled Background Entity.
std::shared_ptr<tjg::Entity> tjg::EntityFactory::MakeTiledBackground(const std::string &path) {
    // Load texture
    auto background_texture = resource_manager.LoadTexture(path);
    background_texture->setRepeated(true);

    // Create entity
    auto background = std::make_shared<Entity>();
    background->AddComponent<Location>();
    sf::Sprite background_sprite;
    background_sprite.setTexture(*background_texture);
    background_sprite.setTextureRect(sf::IntRect(INT16_MIN, INT16_MIN, INT16_MAX, INT16_MAX));
    background->AddComponent<Sprite>(background_sprite);
    return background;
}

/**
 * MakeTech17 Creates an Entity representating the player character.
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
 * @return Tech17 Entity
 */
std::shared_ptr<tjg::Entity> tjg::EntityFactory::MakeTech17() {
    auto spacesuit_texture = resource_manager.LoadTexture("spacesuit.png");
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
    tech17->AddComponent<Sprite>(chest_sprite);
    auto torso_body = tech17->AddComponent<DynamicBody>(
            space,
            sf::Vector2f(0, 0),
            1,
            sf::Vector2f(CHEST_WIDTH, CHEST_HEIGHT),
            // Set moment to INFINITY to prevents the torso from rotating
            true);
    sprite_render_system.AddEntity(tech17, TECH17_BASE_SPRITE_LAYER);

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
    abs_entity->AddComponent<Sprite>(abs_sprite);
    auto abs_body = abs_entity->AddComponent<DynamicBody>(
            space,
            sf::Vector2f(0, ABS_HEIGHT),
            1,
            sf::Vector2f(CHEST_WIDTH, ABS_HEIGHT));
    abs_entity->AddComponent<Appendage>(
            space,
            abs_body->GetBody(),
            torso_body->GetBody(),
            sf::Vector2f(0, -1 * ABS_HEIGHT / 2.0f),
            sf::Vector2f(0, CHEST_HEIGHT / 2.0f),
            LIMB_STIFFNESS * 10.0f);
    sprite_render_system.AddEntity(abs_entity, TECH17_BASE_SPRITE_LAYER - 1);
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
    head_entity->AddComponent<Sprite>(head_sprite);
    auto head_body = head_entity->AddComponent<DynamicBody>(
            space,
            sf::Vector2f(0, -1 * (CHEST_HEIGHT / 2.0f + HEAD_RADIUS)),
            1,
            HEAD_RADIUS);
    head_entity->AddComponent<Appendage>(
            space,
            head_body->GetBody(),
            torso_body->GetBody(),
            sf::Vector2f(0, HEAD_RADIUS),
            sf::Vector2f(0, -1 * CHEST_HEIGHT / 2.0f),
            LIMB_STIFFNESS);
    sprite_render_system.AddEntity(head_entity, TECH17_BASE_SPRITE_LAYER + 1);
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
    left_bicep_entity->AddComponent<Sprite>(bicep_sprite);
    auto left_bicep_body = left_bicep_entity->AddComponent<DynamicBody>(
            space,
            sf::Vector2f(-1 * (CHEST_WIDTH / 2.0f + LIMB_LENGTH / 2.0f), -1 * (CHEST_HEIGHT / 2.0f)),
            1,
            sf::Vector2f(LIMB_LENGTH, LIMB_THICKNESS));
    left_bicep_entity->AddComponent<Appendage>(
            space,
            left_bicep_body->GetBody(),
            torso_body->GetBody(),
            sf::Vector2f(LIMB_LENGTH / 2.0f, 0),
            sf::Vector2f(-1 * CHEST_WIDTH / 2.0f, -1 * CHEST_HEIGHT / 2.0f),
            LIMB_STIFFNESS,
            // Set the angle to keep the arm at his side.
            -1 * ARM_ANGLE);
    sprite_render_system.AddEntity(left_bicep_entity, TECH17_BASE_SPRITE_LAYER - 1);
    tech17->AddChild(left_bicep_entity);

    //
    // CREATE RIGHT BICEP
    //
    auto right_bicep_entity = std::make_shared<Entity>();
    right_bicep_entity->AddComponent<Location>();
    // Flip the sprite horizontally
    bicep_sprite.setScale(-1 * bicep_sprite.getScale().x, bicep_sprite.getScale().y);
    right_bicep_entity->AddComponent<Sprite>(bicep_sprite);
    auto right_bicep_body = right_bicep_entity->AddComponent<DynamicBody>(
            space,
            sf::Vector2f((CHEST_WIDTH / 2.0f + LIMB_LENGTH / 2.0f), -1 * (CHEST_HEIGHT / 2.0f)),
            1,
            sf::Vector2f(LIMB_LENGTH, LIMB_THICKNESS));
    right_bicep_entity->AddComponent<Appendage>(
            space,
            right_bicep_body->GetBody(),
            torso_body->GetBody(),
            sf::Vector2f(-1 * LIMB_LENGTH / 2.0f, 0),
            sf::Vector2f(CHEST_WIDTH / 2.0f, -1 * CHEST_HEIGHT / 2.0f),
            LIMB_STIFFNESS,
            ARM_ANGLE);
    sprite_render_system.AddEntity(right_bicep_entity, TECH17_BASE_SPRITE_LAYER - 1);
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
    left_forearm_entity->AddComponent<Sprite>(forearm_sprite);
    auto left_forearm_body = left_forearm_entity->AddComponent<DynamicBody>(
            space,
            sf::Vector2f(-1 * (CHEST_WIDTH / 2.0f + LIMB_LENGTH + LIMB_LENGTH / 2.0f), -1 * (CHEST_HEIGHT / 2.0f)),
            1,
            sf::Vector2f(LIMB_LENGTH, LIMB_THICKNESS));
    left_forearm_entity->AddComponent<Appendage>(
            space,
            left_forearm_body->GetBody(),
            left_bicep_body->GetBody(),
            sf::Vector2f(LIMB_LENGTH / 2.0f, 0),
            sf::Vector2f(-1 * (LIMB_LENGTH / 2.0f), 0),
            LIMB_STIFFNESS,
            -1 * ARM_ANGLE / 2.0f);
    sprite_render_system.AddEntity(left_forearm_entity, TECH17_BASE_SPRITE_LAYER - 2);
    tech17->AddChild(left_forearm_entity);

    //
    // CREATE RIGHT FOREARM
    //
    auto right_forearm_entity = std::make_shared<Entity>();
    right_forearm_entity->AddComponent<Location>();
    // Flip the sprite horizontally
    forearm_sprite.setScale(-1 * forearm_sprite.getScale().x, forearm_sprite.getScale().y);
    right_forearm_entity->AddComponent<Sprite>(forearm_sprite);
    auto right_forearm_body = right_forearm_entity->AddComponent<DynamicBody>(
            space,
            sf::Vector2f((CHEST_WIDTH / 2.0f + LIMB_LENGTH + LIMB_LENGTH / 2.0f), -1 * (CHEST_HEIGHT / 2.0f)),
            1,
            sf::Vector2f(LIMB_LENGTH, LIMB_THICKNESS));
    right_forearm_entity->AddComponent<Appendage>(
            space,
            right_forearm_body->GetBody(),
            right_bicep_body->GetBody(),
            sf::Vector2f(-1 * (LIMB_LENGTH / 2.0f), 0),
            sf::Vector2f(LIMB_LENGTH / 2.0f, 0),
            LIMB_STIFFNESS,
            ARM_ANGLE / 2.0f);
    sprite_render_system.AddEntity(right_forearm_entity, TECH17_BASE_SPRITE_LAYER - 2);
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
    left_thigh_entity->AddComponent<Sprite>(thigh_sprite);
    auto left_thigh_body = left_thigh_entity->AddComponent<DynamicBody>(
            space,
            sf::Vector2f(-1 * ABS_WIDTH / 2.0f, CHEST_HEIGHT + ABS_HEIGHT + LIMB_LENGTH / 2.0f),
            1,
            sf::Vector2f(LIMB_THICKNESS, LIMB_LENGTH));
    left_thigh_entity->AddComponent<Appendage>(
            space,
            left_thigh_body->GetBody(),
            abs_body->GetBody(),
            sf::Vector2f(0, -1 * LIMB_LENGTH / 2.0f),
            sf::Vector2f(-1 * ABS_WIDTH / 2.0f, ABS_HEIGHT / 2.0f),
            LIMB_STIFFNESS);
    sprite_render_system.AddEntity(left_thigh_entity);
    tech17->AddChild(left_thigh_entity);

    //
    // CREATE RIGHT THIGH
    //
    auto right_thigh_entity = std::make_shared<Entity>();
    right_thigh_entity->AddComponent<Location>();
    // Flip the sprite horizontally
    thigh_sprite.setScale(-1 * thigh_sprite.getScale().x, thigh_sprite.getScale().y);
    right_thigh_entity->AddComponent<Sprite>(thigh_sprite);
    auto right_thigh_body = right_thigh_entity->AddComponent<DynamicBody>(
            space,
            sf::Vector2f(ABS_WIDTH / 2.0f, CHEST_HEIGHT + ABS_HEIGHT + LIMB_LENGTH / 2.0f),
            1,
            sf::Vector2f(LIMB_THICKNESS, LIMB_LENGTH));
    right_thigh_entity->AddComponent<Appendage>(
            space,
            right_thigh_body->GetBody(),
            abs_body->GetBody(),
            sf::Vector2f(0, -1 * LIMB_LENGTH / 2.0f),
            sf::Vector2f(ABS_WIDTH / 2.0f, ABS_HEIGHT / 2.0f),
            LIMB_STIFFNESS);
    sprite_render_system.AddEntity(right_thigh_entity);
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
    left_shin_entity->AddComponent<Sprite>(shin_sprite);
    auto left_shin_body = left_shin_entity->AddComponent<DynamicBody>(
            space,
            sf::Vector2f(-1 * ABS_WIDTH / 2.0f, CHEST_HEIGHT + ABS_HEIGHT + LIMB_LENGTH + LIMB_LENGTH / 2.0f),
            1,
            sf::Vector2f(LIMB_THICKNESS, LIMB_LENGTH));
    left_shin_entity->AddComponent<Appendage>(
            space,
            left_shin_body->GetBody(),
            left_thigh_body->GetBody(),
            sf::Vector2f(0, -1 * LIMB_LENGTH / 2.0f),
            sf::Vector2f(0, LIMB_LENGTH / 2.0f),
            LIMB_STIFFNESS);
    sprite_render_system.AddEntity(left_shin_entity);
    tech17->AddChild(left_shin_entity);

    //
    // CREATE RIGHT SHIN
    //
    auto right_shin_entity = std::make_shared<Entity>();
    right_shin_entity->AddComponent<Location>();
    // Flip the sprite horizontally
    shin_sprite.setScale(-1 * shin_sprite.getScale().x, shin_sprite.getScale().y);
    right_shin_entity->AddComponent<Sprite>(shin_sprite);
    auto right_shin_body = right_shin_entity->AddComponent<DynamicBody>(
            space,
            sf::Vector2f(ABS_WIDTH / 2.0f, CHEST_HEIGHT + ABS_HEIGHT + LIMB_LENGTH + LIMB_LENGTH / 2.0f),
            1,
            sf::Vector2f(LIMB_THICKNESS, LIMB_LENGTH));
    right_shin_entity->AddComponent<Appendage>(
            space,
            right_shin_body->GetBody(),
            right_thigh_body->GetBody(),
            sf::Vector2f(0, -1 * LIMB_LENGTH / 2.0f),
            sf::Vector2f(0, LIMB_LENGTH / 2.0f),
            LIMB_STIFFNESS);
    sprite_render_system.AddEntity(right_shin_entity);
    tech17->AddChild(right_shin_entity);

    return tech17;
}

float tjg::EntityFactory::calculateAngle(sf::Vector2f p1, sf::Vector2f p2) {
    // Calculate the angle between p1 and p2
    double deltaY = p1.y - p2.y;
    double deltaX = p2.x - p1.x;
    double angle = atan2(deltaY, deltaX) * 180 / M_PI;
    return (angle < 0) ? (float)(angle + 360.d) : (float)angle;
}

float tjg::EntityFactory::calculateDistance(sf::Vector2f p1, sf::Vector2f p2) {
    // Calculate distance between p1 and p2
    return (float) sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}
