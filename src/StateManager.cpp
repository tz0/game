#include "StateManager.h"

namespace tjg {
    StateManager::StateManager(ResourceManager &resource_manager, LogicCenter &logic_center):
        resource_manager(resource_manager),
        logic_center(logic_center),
        state(State::MAIN_MENU),
        window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Game", sf::Style::Titlebar | sf::Style::Close),
        main_menu_view(resource_manager, window),
        level_menu_view(resource_manager, window),
        player_view(resource_manager, logic_center, window),
        pause_menu_view(resource_manager, window){
        window.setVerticalSyncEnabled(true);
    }

    void StateManager::Initialize() {
        // Load fonts and the texture sheet
        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");
        auto lcd_regular = resource_manager.LoadFont("LCD-Regular.ttf");
    }

    bool StateManager::Running(){
        return running;
    }

    void StateManager::SwitchToPlayerView() {
        logic_center.Initialize();
        player_view.Initialize();
        state = State::PLAYING;
    }

    void StateManager::SwitchToPauseMenuView() {
        pause_menu_view.Initialize();
        state = State::PAUSE_MENU;
    }

    void StateManager::SwitchToMainMenuView() {
        main_menu_view.Initialize();
        state = State::MAIN_MENU;
    }

    void StateManager::SwitchToLevelMenuView() {
        level_menu_view.Initialize();
        state = State::LEVEL_MENU;
    }

    void StateManager::Update(sf::Time elapsed){
        HandleWindowEvents();
        switch (state) {
            case State::MAIN_MENU:
                main_menu_view.Update();
                break;
            case State::LEVEL_MENU:
                level_menu_view.Update();
                break;
            case State::PAUSE_MENU:
                pause_menu_view.Update();
                break;
            case State::PLAYING:
                logic_center.Update(elapsed);
                player_view.Update();
                break;
        }
    }

    void StateManager::Render(){
        switch (state) {
            case State::MAIN_MENU:
                main_menu_view.Render();
                break;
            case State::LEVEL_MENU:
                level_menu_view.Render();
                break;
            case State::PAUSE_MENU:
                pause_menu_view.Render();
                break;
            case State::PLAYING:
                player_view.Render();
                break;
        }
    }

    void StateManager::HandleWindowEvents() {
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
}
