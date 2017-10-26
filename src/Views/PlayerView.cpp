#include <bitset>

#include "Views/PlayerView.h"

namespace tjg {

    PlayerView::PlayerView(ResourceManager &resource_manager, LogicCenter &logic_center) :
            View(logic_center),
            resource_manager(resource_manager),
            window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Jetpack Game - Alpha", sf::Style::Titlebar | sf::Style::Close) {
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

        // Add tech17 + child components to the sprite render system
        gameview_render_system.AddEntity(logic_center.GetTech17());
        logic_center.GetTech17()->ForEachChild([&](std::shared_ptr<Entity> child){
            gameview_render_system.AddEntity(child);
        });

        // Add the wall entities to the sprite render system
        for (const auto &wall : logic_center.GetWalls()) {
            gameview_render_system.AddEntity(wall);
        }

        //Add the entrance and exit to the sprite render system
        gameview_render_system.AddEntity(logic_center.GetEntrance());
        gameview_render_system.AddEntity(logic_center.GetExit());

        // Make game view background
        gameview_render_system.AddEntity(logic_center.GetEntityFactory().MakeTiledBackground("white-tile.jpg"));

        // Add fans to sprite render system.
        for (const auto &fan : logic_center.GetFans()) {
            gameview_render_system.AddEntity(fan);
        }

        // TODO: Delete this section once menu system is implemented.
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

        // Initialize status bar.
        initializeStatusBar();

        // Initialize dialog system
        std::vector<std::string> dialog_snippets;
        dialog_snippets.emplace_back("This is some test dialog.");
        dialog_snippets.emplace_back("This is some more test dialog.");
        initializeDialogSystem(dialog_snippets, 5, lcd_regular);

        // Set up camera
        // TODO: This needs to change depending on the level.
        // We are accounting for status bar height here since the walls were built before the status bar.
        // Typically, the level design should account for the status bar.
        camera.setCenter(-500, 0 - STATUSBAR_HEIGHT);
        camera.setSize(2080, 1280 + (STATUSBAR_HEIGHT * 2));
    }

    bool PlayerView::Running() {
        return running;
    }

    void PlayerView::Render() {
        window.clear(sf::Color(50, 50, 50, 255));
        window.setView(camera);

        // Render game view
        gameview_render_system.render(window);

        // Drawing that should take place separate from the "camera" should go below here.
        window.setView(window.getDefaultView());

        // Draw the status bar
        renderStatusBarBackground();
        updateStatusBarTrackers();
        statusbar_render_system.render(window);

        // Draw the dialog box on top of the status bar.
        window.draw(dialog_box);

        // Draw FPS counter.
        if (show_info) {
            info.setString(std::to_string(fps) + " FPS");
            window.draw(info);
        }

        // Show the newly drawn frame.
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
    void PlayerView::Update(const sf::Time &elapsed) {
        CheckKeys(elapsed);
        HandleWindowEvents();
        dialog_system.Update(elapsed);
        printf("Dialog box: %s\n", dialog_box.getString().toAnsiString().c_str());
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

    void PlayerView::CheckKeys(const sf::Time &elapsed) {

        auto control_center = logic_center.GetControlCenter();
        auto fuel_resource = logic_center.GetFuelTracker()->GetComponent<FiniteResource>();
        // Control the player character.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            control_center.RotateCounterClockwise(elapsed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            control_center.RotateClockwise(elapsed);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !fuel_resource->IsDepleted()) {
            control_center.FireJetpack(elapsed);
            // Set body to red to visually show the jetpack is firing. Allow this only if the user is not out of fuel.
            control_center.GetPlayerEntity()->GetComponent<Sprite>()->GetSprite().setColor(sf::Color(255, 0, 0));
        }
        else if (control_center.GetPlayerEntity()->GetComponent<Sprite>()->GetSprite().getColor() ==
                   sf::Color(255, 0, 0)) {
            // Set body back to its normal color.
            control_center.GetPlayerEntity()->GetComponent<Sprite>()->GetSprite().setColor(
                    sf::Color(255, 255, 255));
        }
    }

    // TODO: This is a temporary solution.
    void PlayerView::RenderWinMessage() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(win_message);
        window.display();
    }

    void PlayerView::initializeStatusBar() {
        // Store reusable values.
        statusbar_element_height = STATUSBAR_HEIGHT * (3.f / 4.f);
        statusbar_x_padding =  WINDOW_WIDTH / 40.f;
        statusbar_y_padding = STATUSBAR_HEIGHT / 8.f;
        trackers_initial_size = sf::Vector2f((WINDOW_WIDTH / 5.f), statusbar_element_height);
        dialog_initial_size = sf::Vector2f((WINDOW_WIDTH / 2.f), statusbar_element_height);

        // Create a dark background.
        statusbar_background = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, STATUSBAR_HEIGHT));
        statusbar_background.setFillColor(sf::Color(60, 60, 60));
        statusbar_background.setPosition(0, 0);

        // Create fuel tank background.
        fuel_tank_background = sf::RectangleShape(trackers_initial_size);
        fuel_tank_background.setFillColor(sf::Color(0, 0, 0));
        fuel_tank_background.setPosition(statusbar_x_padding, statusbar_y_padding);

        // Create oxygen tank background.
        oxygen_tank_background = sf::RectangleShape(trackers_initial_size);
        oxygen_tank_background.setFillColor(sf::Color(0, 0, 0));
        auto oxygen_tank_x_position = fuel_tank_background.getPosition().x + fuel_tank_background.getLocalBounds().width + statusbar_x_padding;
        oxygen_tank_background.setPosition(oxygen_tank_x_position, statusbar_y_padding);

        // Create dialog box background
        dialog_background = sf::RectangleShape(dialog_initial_size);
        dialog_background.setFillColor(sf::Color(0, 0, 0));
        auto dialog_x_position = oxygen_tank_x_position + oxygen_tank_background.getLocalBounds().width + statusbar_x_padding;
        dialog_background.setPosition(dialog_x_position, statusbar_y_padding);

        // Set up fuel meter.
        auto fuel_tracker_entity = logic_center.GetFuelTracker();
        auto fuel_meter_location = fuel_tracker_entity->GetComponent<Location>();
        auto fuel_meter_sprite = fuel_tracker_entity->GetComponent<Sprite>();
        fuel_meter_sprite->GetSprite().setOrigin(0, 0);
        fuel_meter_sprite->SetSize(trackers_initial_size);
        fuel_meter_location->SetPosition(sf::Vector2f((WINDOW_WIDTH / 40.f), STATUSBAR_HEIGHT * (1.f / 8.f)));

        // Set up oxygen meter.
        auto oxygen_tracker_entity = logic_center.GetOxygenTracker();
        auto oxygen_meter_location = oxygen_tracker_entity->GetComponent<Location>();
        auto oxygen_meter_sprite = oxygen_tracker_entity->GetComponent<Sprite>();
        oxygen_meter_sprite->GetSprite().setOrigin(0, 0);
        oxygen_meter_sprite->SetSize(trackers_initial_size);
        oxygen_meter_location->SetPosition(sf::Vector2f((WINDOW_WIDTH / 4.f), STATUSBAR_HEIGHT * (1.f / 8.f)));

        // Add meters to status bar render system.
        statusbar_render_system.AddEntity(logic_center.GetFuelTracker());
        statusbar_render_system.AddEntity(logic_center.GetOxygenTracker());
    }

    void PlayerView::renderStatusBarBackground() {
        // Draw background elements.
        window.draw(statusbar_background);
        window.draw(fuel_tank_background);
        window.draw(oxygen_tank_background);
        window.draw(dialog_background);
    }

    void PlayerView::updateStatusBarTrackers() {
        // Update fuel tracker size.
        auto fuel_tracker = logic_center.GetFuelTracker();
        auto fuel_tracker_resource = fuel_tracker->GetComponent<FiniteResource>();
        auto fuel_tracker_sprite = fuel_tracker->GetComponent<Sprite>();
        float new_fuel_width = trackers_initial_size.x * (fuel_tracker_resource->GetCurrentLevel() / fuel_tracker_resource->GetMaxLevel());
        auto new_fuel_size = sf::Vector2f(new_fuel_width, trackers_initial_size.y);
        fuel_tracker_sprite->SetSize(new_fuel_size);

        // Update oxygen tracker size.
        auto oxygen_tracker = logic_center.GetOxygenTracker();
        auto oxygen_tracker_resource = oxygen_tracker->GetComponent<FiniteResource>();
        auto oxygen_tracker_sprite = oxygen_tracker->GetComponent<Sprite>();
        float new_oxygen_width = trackers_initial_size.x * (oxygen_tracker_resource->GetCurrentLevel() / oxygen_tracker_resource->GetMaxLevel());
        auto new_oxygen_size = sf::Vector2f(new_oxygen_width, trackers_initial_size.y);
        oxygen_tracker_sprite->SetSize(new_oxygen_size);
    }

    void PlayerView::initializeDialogSystem(std::vector<std::string> &dialog_snippets, float seconds_to_show_dialog, std::shared_ptr<sf::Font> font) {
        // Create dialog box Text object.
        dialog_box.setFont(*font);
        dialog_box.setFillColor(sf::Color(255, 255, 255));
        dialog_box.setCharacterSize(16);
        float dialog_box_x = trackers_initial_size.x*2 + statusbar_x_padding*3;
        dialog_box.setPosition(dialog_box_x, statusbar_y_padding);
        // Build the dialog system.
        dialog_system.Initialize(dialog_box, dialog_snippets, seconds_to_show_dialog);
    }
}
