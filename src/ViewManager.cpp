#include "ViewManager.h"

namespace tjg {
    ViewManager::ViewManager(ResourceManager &resource_manager, LogicCenter &logic_center):
        resource_manager(resource_manager),
        logic_center(logic_center),
        state(State::MAIN_MENU),
        window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Game", sf::Style::Titlebar | sf::Style::Close),
        main_menu_view(resource_manager, window),
        level_menu_view(resource_manager, window),
        player_view(resource_manager, window, logic_center),
        pause_menu_view(resource_manager, window) {
        window.setVerticalSyncEnabled(true);
    }

    void ViewManager::Initialize() {

    }

    bool ViewManager::Running(){
        return running;
    }


    void ViewManager::SwitchView(ViewSwitch view_switch) {
        switch (view_switch) {
            case ViewSwitch::MAIN_MENU:
                SwitchToMainMenuView();
                break;
            case ViewSwitch ::LEVEL_MENU:
                SwitchToLevelMenuView();
                break;
            case ViewSwitch::PLAYING:
                logic_center.Reset();
                SwitchToPlayerView();
                break;
            case ViewSwitch::RESUME:
                ResumePlayerView();
                break;
            case ViewSwitch::PAUSED:
                SwitchToPauseMenuView(State::PAUSED);
                break;
            case ViewSwitch::WON:
                SwitchToPauseMenuView(State::WON);
                break;
            case ViewSwitch::FAILED:
                SwitchToPauseMenuView(State::FAILED);
                break;
            case ViewSwitch::EXIT:
                window.close();
                running = false;
                break;
            default:
                break;
        }
    }


    void ViewManager::SwitchToMainMenuView() {
        main_menu_view.Initialize();
        state = State::MAIN_MENU;
    }


    void ViewManager::SwitchToLevelMenuView() {
        level_menu_view.Initialize();
        state = State::LEVEL_MENU;
    }


    void ViewManager::SwitchToPauseMenuView(State state) {
        pause_menu_view.Initialize(state);
        this->state = state;
    }


    void ViewManager::SwitchToPlayerView() {
        logic_center.Initialize();
        player_view.Initialize();
        state = State::PLAYING;
    }

    void ViewManager::ResumePlayerView() {
        state = State::PLAYING;
    }

    void ViewManager::Update(sf::Time elapsed){
        switch (state) {
            case State::MAIN_MENU:
                HandleWindowEvents(main_menu_view);
                main_menu_view.Update();
                break;
            case State::LEVEL_MENU:
                HandleWindowEvents(level_menu_view);
                level_menu_view.Update();
                break;
            case State::WON:
            case State::FAILED:
            case State::PAUSED:
                HandleWindowEvents(pause_menu_view);
                pause_menu_view.Update();
                break;
            case State::PLAYING:
                HandleWindowEvents(player_view);
                logic_center.Update(elapsed);
                player_view.Update();
                break;
        }

        //Switch to menu if won/lost
        switch (logic_center.GetGameState()) {
            case State::WON:
                logic_center.Reset();
                SwitchToPauseMenuView(State::WON);
                break;
            case State::FAILED:
                logic_center.Reset();
                SwitchToPauseMenuView(State::FAILED);
                break;
            default:
                break;
        }
    }

    void ViewManager::Render(){
        switch (state) {
            case State::MAIN_MENU:
                main_menu_view.Render();
                break;
            case State::LEVEL_MENU:
                level_menu_view.Render();
                break;
            case State::PAUSED:
            case State::WON:
            case State::FAILED:
                pause_menu_view.Render();
                break;
            case State::PLAYING:
                player_view.Render();
                break;
        }
    }

    void ViewManager::HandleWindowEvents(View &current_view) {
        sf::Event event;
        ViewSwitch view_switch;
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
//                        case sf::Keyboard::Escape: {
//                            window.close();
//                            running = false;
//                            break;
//                        }

                        default:
                            view_switch = current_view.HandleWindowEvents(event);
                            SwitchView(view_switch);
                            break;
                    }
                    break;
                }
                default:
                    view_switch = current_view.HandleWindowEvents(event);
                    SwitchView(view_switch);
                    break;
            }
        }
    }
}
