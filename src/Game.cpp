#include "Game.h"

namespace tjg {

    // Constructor.
    Game::Game() :
            space(cpSpaceNew()),
            resource_manager("media"),
            entity_factory(resource_manager, sprite_render_system, space),
            window(sf::VideoMode(1280, 720, 32), "Game", sf::Style::Titlebar | sf::Style::Close) {

        // Enable vsync.
        window.setVerticalSyncEnabled(true);

        // Set up Chipmunk physics space.
        cpSpaceSetGravity(space, cpv(0, 0));
    }

    // Teardown.
    Game::~Game() {
        // Free all memory used by Chipmunk.
        cpSpaceFree(space);
    }

    // Begin the game loop.
    void Game::Run() {
        // Load fonts and the texture sheet
        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");
        auto lcd_regular = resource_manager.LoadFont("LCD-Regular.ttf");
        auto texture_sheet = resource_manager.LoadTexture("texturesheet.png");

        // Create boundary walls using the entity factory.
        auto top_wall = entity_factory.MakeWall(sf::Vector2f(-500, -500), sf::Vector2f(500, -500), 40);
        auto bottom_wall = entity_factory.MakeWall(sf::Vector2f(500, 500), sf::Vector2f(-500, 500), 40);
        auto left_wall = entity_factory.MakeWall(sf::Vector2f(-500, 500), sf::Vector2f(-500, -500), 40);
        auto right_wall = entity_factory.MakeWall(sf::Vector2f(500, -500), sf::Vector2f(500, 500), 40);

        // Add the walls to the entities vector.
        entities.push_back(top_wall);
        entities.push_back(bottom_wall);
        entities.push_back(left_wall);
        entities.push_back(right_wall);

        // Add the walls to the sprite render system.
        sprite_render_system.AddEntity(top_wall, 0);
        sprite_render_system.AddEntity(bottom_wall, 0);
        sprite_render_system.AddEntity(left_wall, 0);
        sprite_render_system.AddEntity(right_wall, 0);

        // Make background
        sprite_render_system.AddEntity(entity_factory.MakeTiledBackground("background.png"), -100);

        // Create player character
        tech17 = entity_factory.MakeTech17();
        // Add tech17 to the player control system
        player_control_system.AddEntity(tech17);

        // Load asteroid texture.
        sf::Sprite asteroid_sprite;
        asteroid_sprite.setTexture(*texture_sheet);
        asteroid_sprite.setTextureRect(sf::IntRect(1, 1, 160, 150));

        // Create many asteroids
        for (auto i = 0; i < 10; ++i) {
            auto asteroid_entity = std::make_shared<Entity>();
            asteroid_entity->AddComponent<Location>();
            asteroid_entity->AddComponent<Sprite>(asteroid_sprite);
            asteroid_entity->AddComponent<DynamicBody>(
                    space,
                    sf::Vector2f(floor(i / 4) * 100 + 50, 100 * (i % 4)),
                    3,
                    sf::Vector2f(asteroid_sprite.getGlobalBounds().width, asteroid_sprite.getGlobalBounds().height));
            entities.push_back(asteroid_entity);
            sprite_render_system.AddEntity(asteroid_entity);
        }

        // Set font for FPS clock
        info.setFont(*avenir_bold);
        info.setStyle(sf::Text::Bold);
        info.setCharacterSize(24);

        // Set up camera
        camera.setCenter(0, 0);
        camera.setSize(1600, 1200);

        // Game loop.
        while (window.isOpen()) {
            Draw();
            Update();
            HandleEvents();
        }

    }

    void Game::HandleEvents() {
        sf::Event event;
        // Look for window events.
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed: {
                    switch (event.key.code) {
                        // Close window on ESC
                        case sf::Keyboard::Escape: {
                            window.close();
                            break;
                        }
                        // Toggle FPS counter on F1.
                        case sf::Keyboard::F1: {
                            show_info = !show_info;
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }

    void Game::Update() {
        sf::Time elapsed = clock.restart();

        // Temporary/Example control system.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player_control_system.RotateCounterClockwise();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player_control_system.RotateClockwise();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            player_control_system.FireJetpack();
            // Set body to red for testing.
            player_control_system.GetPlayerEntity()->GetComponent<Sprite>()->GetSprite().setColor(sf::Color(255,0,0));
        }
        else if(player_control_system.GetPlayerEntity()->GetComponent<Sprite>()->GetSprite().getColor() == sf::Color(255,0,0)){
            // Set body back to its normal color.
            player_control_system.GetPlayerEntity()->GetComponent<Sprite>()->GetSprite().setColor(sf::Color(255,255,255));
        }

        //
        // Update all of the entities' components
        //
        for (auto entity : entities) {
            auto rigidbody = entity->GetComponent<DynamicBody>();
            if (rigidbody) rigidbody->Update();
        }

        tech17->GetComponent<DynamicBody>()->Update();
        tech17->ForEachChild([](std::shared_ptr<Entity> child) {
            auto r = child->GetComponent<DynamicBody>();
            if (r) r->Update();
        });

        //
        // Example of moving the camera location
        //
        camera.setCenter(camera.getCenter() * 0.99f + tech17->GetComponent<Location>()->getPosition() * 0.01f);

        // Perform the physical simulation based on SFML timer elapsed time.
        cpSpaceStep(space, elapsed.asSeconds() * 2);
    }

    void Game::Draw() {
        window.clear(sf::Color(50, 50, 50, 255));
        window.setView(camera);

        // Render sprites
        sprite_render_system.render(window);

        // Drawing that should take place separate from the "camera" should go below here.
        window.setView(window.getDefaultView());

        if (show_info) {
            info.setString(std::to_string(fps) + " FPS");
            window.draw(info);
        }

        window.display();

        // Count FPS
        frames_drawn++;
        if (fps_clock.getElapsedTime().asSeconds() > 1.0f) {
            fps_clock.restart();
            fps = frames_drawn;
            frames_drawn = 0;
        }
    }
}