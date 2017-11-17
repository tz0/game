#include "Views/LevelView.h"

namespace tjg {

    LevelView::LevelView(sf::RenderWindow &window, ResourceManager &resource_manager, std::shared_ptr<SoundManager> &sound_manager, LogicCenter &logic_center) :
            View(window, resource_manager, sound_manager),
            logic_center(logic_center),
            dust_particle_system(main_render_system, logic_center.GetPhysicsSystem(), 200,
                                 sf::Sprite(*resource_manager.LoadTexture("particle.png"), sf::IntRect(0, 0, 256, 256)),
                                 -10, sf::BlendAdd, sf::milliseconds(1), sf::seconds(8), sf::Vector2f(60, 60), sf::Vector2f(0, 0), 2.0f,
                                 [](float x){
                                     auto alpha = static_cast<sf::Uint8>(std::max(0.0f, static_cast<float>(128 * cos(x * 2.5)+128)));
                                     return sf::Color(120, 120, 120, alpha/sf::Uint8(4));
                                 },
                                 [](float x){
                                     auto size = static_cast<float>(sin(x * 4.0) / 5.f);
                                     return sf::Vector2f(size, size);
                                 }),
            shockbox_particle_system(main_render_system, logic_center.GetPhysicsSystem(), 10,
                                 sf::Sprite(*resource_manager.LoadTexture("particle.png"), sf::IntRect(0, 0, 256, 256)),
                                 -10, sf::BlendAdd, sf::milliseconds(200), sf::seconds(0.25f), sf::Vector2f(50, 50), sf::Vector2f(50, 50),  2.0f,
                                 [](float x){
                                     auto alpha = static_cast<sf::Uint8>(std::max(0.0f, static_cast<float>(128 * cos(x * 2.5)+128)));
                                     return sf::Color(0, 128, 255, alpha * 4);
                                 },
                                 [](float x){
                                     auto size = static_cast<float>(sin(x * 4.0));
                                     return sf::Vector2f(size, size);
                                 }),
            jetpack_flame_system(main_render_system, 500,
                                 sf::Sprite(*resource_manager.LoadTexture("particle.png"), sf::IntRect(0, 0, 256, 256)),
                                 40, sf::BlendAdd, sf::milliseconds(1), sf::seconds(2), sf::Vector2f(0, 0), sf::Vector2f(5, 5), 0,
                                 [](float x){
                                     auto decreasing = static_cast<sf::Uint8>(std::max(0.0f, static_cast<float>(255 * sin(1.0 / 25.0 * (x * 100)))));
                                     auto increasing = sf::Uint8(255) - decreasing;
                                     return sf::Color(increasing, increasing, decreasing, decreasing);
                                 },
                                 [](float x){
                                     auto size = std::max(0.0f, 0.5f * static_cast<float>(cos(x * 2.0)));
                                     return sf::Vector2f(size, size);
                                 })
    {
            window.setVerticalSyncEnabled(true);
    }


    void LevelView::Initialize() {
        main_render_system.Reset();
        statusbar_render_system.Reset();

        // Load fonts and the texture sheet
        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");
        auto lcd_regular = resource_manager.LoadFont("LCD-Regular.ttf");

        // Set font for FPS clock
        info.setFont(*avenir_bold);
        info.setStyle(sf::Text::Bold);
        info.setCharacterSize(24);

        // Add tech17 + child components to the sprite render system
        main_render_system.AddEntity(logic_center.GetTech17());
        logic_center.GetTech17()->ForEachChild([&](std::shared_ptr<Entity> child){
            main_render_system.AddEntity(child);
        });
        jetpack_flame_system.Initialize();
        jetpack_flame_system.AddEntity(logic_center.GetTech17());

        // Add the wall entities to the sprite render system
        for (const auto &wall : logic_center.GetWalls()) {
            main_render_system.AddEntity(wall);

            // Lethal walls have children (endcaps) that must be added to render system as well.
            wall->ForEachChild([&](std::shared_ptr<Entity> child){
               main_render_system.AddEntity(child);
            });
        }

        //Add the entrance and exit to the sprite render system
        main_render_system.AddEntity(logic_center.GetEntrance());
        main_render_system.AddEntity(logic_center.GetExit());

        // Make game view background
        auto tiled_background = logic_center.GetEntityFactory().MakeTiledBackground("white-tile.jpg");
        tiled_background->GetComponent<Sprite>()->GetSprite().setColor(sf::Color(200, 200, 200));
        main_render_system.AddEntity(tiled_background);

        for (const auto &pressure_source : logic_center.GetPressureSources()) {
            main_render_system.AddEntity(pressure_source);
        }

        // Add fans to sprite render system and set up their particles.
        dust_particle_system.Initialize();
        for (const auto &fan : logic_center.GetFans()) {
            main_render_system.AddEntity(fan);
            dust_particle_system.AddEntity(fan);
        }

        // Add the shock boxes to the sprite render system and set up their particles.
        shockbox_particle_system.Initialize();
        for (const auto &shock_box : logic_center.GetShockBoxes()) {
            main_render_system.AddEntity(shock_box);
            shockbox_particle_system.AddEntity(shock_box);
        }

        // Iterate static decorations record from level's decorations vector, create static decorations, and add them
        // to the render system.
        for (auto &decoration : logic_center.GetLevel().GetStaticDecorations()) {
            std::cout << decoration.texture << std::endl;
            sf::Sprite sprite(*resource_manager.LoadTexture(decoration.texture), decoration.texture_rect);
            sprite.setScale(decoration.scale);
            main_render_system.AddEntity(logic_center.GetEntityFactory().MakeStaticDecoration(sprite, decoration.position, decoration.rotation));
        }

        // Initialize status bar.
        InitializeStatusBar(lcd_regular);

        // Initialize dialog system
        std::vector<Dialogue> dialogues = logic_center.GetLevel().GetDialogues();
        InitializeDialogueSystem(dialogues, lcd_regular);

        // Set up camera, accounting for level and status bar since the walls were built before the status bar.
        camera.setCenter(
            logic_center.GetLevel().GetCameraCenter().x, 
            logic_center.GetLevel().GetCameraCenter().y);
        camera.setSize(
            logic_center.GetLevel().GetCameraSize().x, 
            logic_center.GetLevel().GetCameraSize().y);

        // Update listener position so the player hears spatial sounds properly.
        auto player_location = logic_center.GetTech17()->GetComponent<Location>();
        sound_manager->UpdateListenerPosition(player_location);

        // Set up spatial sounds.
        sound_manager->InitializeSpatialSounds(logic_center.GetFans(),
                                               logic_center.GetShockBoxes(),
                                               logic_center.GetPressureSources(),
                                               logic_center.GetWalls());

        // Start music.
        sound_manager->StartLevelMusic();
    }


    void LevelView::Render() {
        window.clear(sf::Color(50, 50, 50, 255));
        camera.setViewport(sf::FloatRect(0, 0.1, 1, 0.9));
        window.setView(camera);

        // Render game view
        main_render_system.render(window);

        // Drawing that should take place separate from the "camera" should go below here.
        window.setView(window.getDefaultView());

        // Draw the status bar
        RenderStatusBar();

        // Draw the dialog box on top of the status bar.
        window.draw(dialogue_system.GetDialogueBox());

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
    void LevelView::Update(const sf::Time &elapsed) {
        CheckKeys(elapsed);
        dust_particle_system.Update(elapsed);
        shockbox_particle_system.Update(elapsed);
        jetpack_flame_system.Update(elapsed);
        dialogue_system.Update(elapsed);
        // Update listener position so the player hears spatial sounds properly.
        auto player_location = logic_center.GetTech17()->GetComponent<Location>();
        sound_manager->UpdateListenerPosition(player_location);
    }

    ViewSwitch LevelView::HandleWindowEvents(const sf::Event event) {
        switch (event.type) {
            case sf::Event::LostFocus:
                return ViewSwitch {State::PAUSED, 0};
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    // Toggle FPS counter on F1.
                    case sf::Keyboard::F1: {
                        show_info = !show_info;
                        break;
                    }
                    case sf::Keyboard::Escape: {
                        // Stop music.
                        sound_manager->PauseLevelMusic();
                        // Switch to pause screen.
                        return ViewSwitch {State::PAUSED, 0};
                    }
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
        return ViewSwitch {State::CONTINUE, 0};
    }

    void LevelView::CheckKeys(const sf::Time &elapsed) {
        auto control_center = logic_center.GetControlCenter();
        auto fuel_resource = logic_center.GetFuelTracker()->GetComponent<FiniteResource>();
        // Control the player character.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            control_center.RotateCounterClockwise(elapsed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            control_center.RotateClockwise(elapsed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !fuel_resource->IsDepleted()) {
            control_center.FireJetpack(elapsed);
            // Enable jetpack particle system to show it is active.
            jetpack_flame_system.Enable();
            // Start jetpack sound effect.
            sound_manager->StartJetPack();
        } else {
            // Disable jetpack particle system when key is no longer pressed.
            jetpack_flame_system.Disable();
            // Stop jetpack sound effect.
            sound_manager->StopJetPack();
        }
    }

    void LevelView::InitializeStatusBar(std::shared_ptr<sf::Font> hud_font) {
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

        // Create dialogue box background
        dialogue_background = sf::RectangleShape(dialog_initial_size);
        dialogue_background.setFillColor(sf::Color(0, 0, 0));
        auto dialog_x_position = oxygen_tank_x_position + oxygen_tank_background.getLocalBounds().width + statusbar_x_padding;
        dialogue_background.setPosition(dialog_x_position, statusbar_y_padding);

        // Set up fuel meter.
        auto fuel_tracker_entity = logic_center.GetFuelTracker();
        auto fuel_meter_location = fuel_tracker_entity->GetComponent<Location>();
        auto fuel_meter_sprite = fuel_tracker_entity->GetComponent<Sprite>();
        fuel_meter_sprite->GetSprite().setOrigin(0, 0);
        fuel_meter_sprite->SetSize(trackers_initial_size);
        fuel_meter_location->SetPosition(fuel_tank_background.getPosition());

        // Fuel meter numeric display.
        auto fuel_meter_color = fuel_meter_sprite->GetSprite().getColor();
        auto fuel_outline_color = sf::Color(static_cast<sf::Uint8>(fuel_meter_color.r / 2), static_cast<sf::Uint8>(fuel_meter_color.g / 2), static_cast<sf::Uint8>(fuel_meter_color.b / 2));
        fuel_numeric_text = sf::Text();
        fuel_numeric_text.setFont(*hud_font);
        fuel_numeric_text.setFillColor(sf::Color(255, 255, 255));
        fuel_numeric_text.setOutlineColor(fuel_outline_color);
        fuel_numeric_text.setOutlineThickness(2);
        fuel_numeric_text.setCharacterSize(20);
        fuel_numeric_text.setPosition(fuel_tank_background.getPosition());

        // Set up oxygen meter.
        auto oxygen_tracker_entity = logic_center.GetOxygenTracker();
        auto oxygen_meter_location = oxygen_tracker_entity->GetComponent<Location>();
        auto oxygen_meter_sprite = oxygen_tracker_entity->GetComponent<Sprite>();
        oxygen_meter_sprite->GetSprite().setOrigin(0, 0);
        oxygen_meter_sprite->SetSize(trackers_initial_size);
        oxygen_meter_location->SetPosition(oxygen_tank_background.getPosition());

        // Oxygen meter numeric display.
        auto oxygen_meter_color = oxygen_meter_sprite->GetSprite().getColor();
        auto oxygen_outline_color = sf::Color(static_cast<sf::Uint8>(oxygen_meter_color.r / 2), static_cast<sf::Uint8>(oxygen_meter_color.g / 2), static_cast<sf::Uint8>(oxygen_meter_color.b / 2));
        oxygen_numeric_text = sf::Text();
        oxygen_numeric_text.setFont(*hud_font);
        oxygen_numeric_text.setFillColor(sf::Color(255, 255, 255));
        oxygen_numeric_text.setOutlineColor(oxygen_outline_color);
        oxygen_numeric_text.setOutlineThickness(2);
        oxygen_numeric_text.setCharacterSize(20);
        oxygen_numeric_text.setPosition(oxygen_tank_background.getPosition());

        // Add meters to status bar render system.
        statusbar_render_system.AddEntity(logic_center.GetFuelTracker());
        statusbar_render_system.AddEntity(logic_center.GetOxygenTracker());
    }

    void LevelView::RenderStatusBar() {
        // Draw background elements.
        window.draw(statusbar_background);
        window.draw(fuel_tank_background);
        window.draw(oxygen_tank_background);
        window.draw(dialogue_background);

        // Update resource trackers.
        UpdateStatusBarTrackers();

        // Render the sprites in the status bar (just the resource tracker images for now).
        statusbar_render_system.render(window);

        // Render status bar text (resource tracker levels).
        window.draw(fuel_numeric_text);
        window.draw(oxygen_numeric_text);
    }

    void LevelView::UpdateStatusBarTrackers() {
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

        // Update fuel tracker text.
        std::stringstream fuel_stream;
        fuel_stream << std::fixed << std::setprecision(1) << fuel_tracker_resource->GetCurrentLevel();
        fuel_numeric_text.setString("FUEL: " + fuel_stream.str());

        // Update oxygen tracker text.
        std::stringstream oxygen_stream;
        oxygen_stream << std::fixed << std::setprecision(1) << oxygen_tracker_resource->GetCurrentLevel();
        oxygen_numeric_text.setString("OXYGEN: " + oxygen_stream.str());
    }

    void LevelView::InitializeDialogueSystem(std::vector<Dialogue> &dialogues, std::shared_ptr<sf::Font> font) {
        // Create dialog box Text object.
        sf::Text dialogue_box;
        dialogue_box.setFont(*font);
        dialogue_box.setFillColor(sf::Color(255, 255, 255));
        dialogue_box.setCharacterSize(20);
        float dialogue_box_x = trackers_initial_size.x*2 + statusbar_x_padding*3;
        dialogue_box.setPosition(dialogue_box_x, statusbar_y_padding);
        // Build the dialog system.
        dialogue_system.Initialize(dialogue_box, dialogues, (unsigned int)(dialogue_background.getLocalBounds().width));
    }
}
