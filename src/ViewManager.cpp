#include "ViewManager.h"

namespace tjg {
    ViewManager::ViewManager(ResourceManager &resource_manager, LogicCenter &logic_center, EventManager &event_manager):
        logic_center(logic_center),
        event_manager(event_manager),
        state(State::MAIN_MENU),
        window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Game", sf::Style::Titlebar | sf::Style::Close),
        main_menu_view(resource_manager, window, logic_center),
        level_menu_view(resource_manager, window),
        player_view(resource_manager, window, logic_center),
        pause_menu_view(resource_manager, window) {
        window.setVerticalSyncEnabled(true);
    }

  
    //TODO: Implement or remove
    void ViewManager::Initialize() {

    }

    bool ViewManager::Running(){
        return running;
    }


    void ViewManager::SwitchView(ViewSwitch view_switch) {
        event_manager.Fire<ViewChanged>(view_switch);
        switch (view_switch.state) {
            case State::MAIN_MENU:
                SwitchToMainMenuView();
                break;
            case State::LEVEL_MENU:
                SwitchToLevelMenuView();
                break;
            case State::PLAYING:
                logic_center.Reset();
                if (view_switch.level_number > 0) {
                    current_level = view_switch.level_number;
                    SwitchToPlayerView(view_switch.level_number);
                } else {
                    SwitchToPlayerView(current_level);
                }
                break;
            case State::RESUME:
                ResumePlayerView();
                break;
            case State::PAUSED:
                SwitchToPauseMenuView(ViewSwitch{State::PAUSED, 0});
                break;
            case State::WON:
                SwitchToPauseMenuView(ViewSwitch{State::WON, 0});                
                break;
            case State::FAILED:
                SwitchToPauseMenuView(ViewSwitch{State::FAILED, 0});
                break;
            case State::EXIT:
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


    void ViewManager::SwitchToPauseMenuView(ViewSwitch view_switch) {        
        pause_menu_view.Initialize(ViewSwitch {view_switch.state, current_level});
        this->state = view_switch.state;
    }


    void ViewManager::SwitchToPlayerView(const unsigned int level_number) {
        logic_center.Initialize(level_number);
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
                player_view.Update(elapsed);
                break;
            default:
                break;
        }

        //Switch to menu if won/lost
        switch (logic_center.GetGameState()) {
            case State::WON:
                logic_center.Reset();
                SwitchToPauseMenuView(ViewSwitch{State::WON, 0});
                break;
            case State::FAILED:
                logic_center.Reset();
                SwitchToPauseMenuView(ViewSwitch{State::FAILED, 0});
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
            default:
                break;
        }
    }

    void ViewManager::HandleWindowEvents(View &current_view) {
        sf::Event event;
        // Look for window events.
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    running = false;
                    break;
                default:
                    auto view_switch = current_view.HandleWindowEvents(event);
                    if (view_switch.state != State::CONTINUE) {
                        SwitchView(view_switch);
                    }
                    break;
            }
        }
    }
}
