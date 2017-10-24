#include <bitset>

#include "Views/PlayerView.h"

namespace tjg {

    PlayerView::PlayerView(ResourceManager &resource_manager, LogicCenter &logic_center) :
            View(logic_center),
            resource_manager(resource_manager),
            window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Game", sf::Style::Titlebar | sf::Style::Close) {
            window.setVerticalSyncEnabled(true);
    }

    void PlayerView::Initialize() {

        // Load fonts and the texture sheet
        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");
        auto lcd_regular = resource_manager.LoadFont("LCD-Regular.ttf");

        // Set font for FPS clock
        info.setFont(*avenir_bold);
        info.setStyle(sf::Text::Bold);
        info.setCharacterSize(24);

        // set font for user countdown clock
        countdown.setFont(*lcd_regular);
        countdown.setStyle(sf::Text::Bold);
        countdown.setCharacterSize(32);
        //countdown.setPosition(WINDOW_WIDTH / 2 - 165, WINDOW_HEIGHT * .054f); // position - outside the wall
        countdown.setPosition(WINDOW_WIDTH / 2 - 165, WINDOW_HEIGHT * .001f); // position - inside the wall

        // Add tech17 + child components to the sprite render system
        sprite_render_system.AddEntity(logic_center.GetTech17());
        logic_center.GetTech17()->ForEachChild([&](std::shared_ptr<Entity> child){
            sprite_render_system.AddEntity(child);
        });

        // Add the wall entities to the sprite render system
        for (const auto &wall : logic_center.GetWalls()) {
            sprite_render_system.AddEntity(wall);
        }

        //Add the entrance and exit to the sprite render system
        sprite_render_system.AddEntity(logic_center.GetEntrance());
        sprite_render_system.AddEntity(logic_center.GetExit());

        // Make background
        sprite_render_system.AddEntity(logic_center.GetEntityFactory().MakeTiledBackground("white-tile.jpg"));

        // temp Set font for win message
        win_message.setFont(*avenir_bold);
        // Create a win message.
        win_message.setStyle(sf::Text::Bold);
        win_message.setCharacterSize(24);
        win_message.setString("You Reached the Exit!");
        // Center the win message on the screen.
        sf::FloatRect textRect = win_message.getLocalBounds();
        win_message.setOrigin(textRect.left + (textRect.width / 2), textRect.top + (textRect.height / 2));
        win_message.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);


        // Add fans to sprite render system.
        for (const auto &fan : logic_center.GetFans()) {
            sprite_render_system.AddEntity(fan);
        }

        // Set up camera
        // TODO: This needs to change depending on the level.
        camera.setCenter(-500, 0);
        camera.setSize(2080, 1280);
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
        
        // Drawing countdown timer  
        if (show_countdown) {
            if (countdown_mode_binary)
                countdown.setString(
                        "Time Left " +
                        std::bitset<8>(logic_center.GetRemainingSeconds()).to_string());
            else
                countdown.setString(
                        std::to_string(logic_center.GetRemainingSeconds()) + " Seconds");
            window.draw(countdown);
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
    void PlayerView::Update() {
        CheckKeys();
        HandleWindowEvents();
    }

    void PlayerView::HandleWindowEvents() {
        sf::Event event;
        // Look for window events.
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    running = false;
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

    void PlayerView::CheckKeys() {

        auto control_center = logic_center.GetControlCenter();

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

    void PlayerView::RenderWinMessage() {
        window.setView(window.getDefaultView());

        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(win_message);
        window.display();
    }

}
