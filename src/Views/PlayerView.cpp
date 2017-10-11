
#include "Views/PlayerView.h"

namespace tjg {

    PlayerView::PlayerView(ResourceManager &resource_manager) :
            View(resource_manager),
            window(sf::VideoMode(1280, 720, 32), "Game", sf::Style::Titlebar | sf::Style::Close) {

        window.setVerticalSyncEnabled(true);

    }

    void PlayerView::initialize() {

        // Load fonts and the texture sheet
        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");
        auto lcd_regular = resource_manager.LoadFont("LCD-Regular.ttf");

        // Set font for FPS clock
        info.setFont(*avenir_bold);
        info.setStyle(sf::Text::Bold);
        info.setCharacterSize(24);

        // Add tech17 + child components to the sprite render system
        sprite_render_system.AddEntity(tech17);
        tech17->ForEachChild([&](std::shared_ptr<Entity> child){
            sprite_render_system.AddEntity(child);
        });

        // Add the wall entities to the sprite render system
        for (auto wall : walls) {
            sprite_render_system.AddEntity(wall);
        }

        // Make background
        sprite_render_system.AddEntity(entity_factory.MakeTiledBackground("background.png"));


        // Load asteroid texture.
        auto texture_sheet = resource_manager.LoadTexture("texturesheet.png");
        sf::Sprite asteroid_sprite;
        asteroid_sprite.setTexture(*texture_sheet);
        asteroid_sprite.setTextureRect(sf::IntRect(1, 1, 160, 150));
        auto asteroid_bounds = asteroid_sprite.getGlobalBounds();
        // Add all asteroids to the sprite render system.
        for (auto asteroid : asteroids) {
            asteroid->AddComponent<Sprite>(asteroid_sprite);
            asteroid->GetComponent<Sprite>()->GetSprite().setScale(100.0f / asteroid_bounds.width, 100.0f / asteroid_bounds.height);
            sprite_render_system.AddEntity(asteroid);
        }

        // Set up camera
        camera.setCenter(0, 0);
        camera.setSize(1600, 1200);

    }

    bool PlayerView::Running() {
        return running;
    }

    void PlayerView::Render() {
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

    // Update logic that is specific to the player view.
    void PlayerView::update(const sf::Time elapsed) {
        CheckKeys(elapsed);
        HandleWindowEvents();

        // Example of moving the camera location
        camera.setCenter(camera.getCenter() * 0.99f + tech17->GetComponent<Location>()->getPosition() * 0.01f);
    }

    void PlayerView::HandleWindowEvents() {
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
                            running = false;
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

    void PlayerView::CheckKeys(const sf::Time) {
        // Temporary/Example control system.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            control_center.RotateCounterClockwise();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            control_center.RotateClockwise();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            control_center.FireJetpack();
            // Set body to red for testing.
            control_center.GetPlayerEntity()->GetComponent<Sprite>()->GetSprite().setColor(sf::Color(255, 0, 0));
        } else if (control_center.GetPlayerEntity()->GetComponent<Sprite>()->GetSprite().getColor() ==
                   sf::Color(255, 0, 0)) {
            // Set body back to its normal color.
            control_center.GetPlayerEntity()->GetComponent<Sprite>()->GetSprite().setColor(sf::Color(255, 255, 255));
        }
    }

}
