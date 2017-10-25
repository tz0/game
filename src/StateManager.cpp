#include <bitset>
#include "StateManager.h"

namespace tjg {
    StateManager::StateManager(ResourceManager &resource_manager, LogicCenter &logic_center):
        resource_manager(resource_manager),
        logic_center(logic_center),
        view(resource_manager, logic_center),
        state(State::PLAYING){}

    void StateManager::SetState(State state){
        this -> state = state;
    }

    void StateManager::Initialize() {

    }

    bool StateManager::Running(){
        return view.Running();
    }

    void StateManager::Update(){
        switch (state) {
            case State::MAIN_MENU:
                DrawMainMenu();
                break;
            case State::LEVEL_MENU:
                DrawLevelMenu();
            case State::PAUSE_MENU:
                DrawPauseMenu();
                break;
            case State::PLAYING:
                auto elapsed = update_clock.getElapsedTime();
                if (elapsed.asSeconds() > 1.f/60.f) {
                    logic_center.Update(elapsed);
                    view.Update();
                    update_clock.restart();
                }
                break;
        }
    }

    void StateManager::SwitchToPlayerView() {
        logic_center.Initialize();
        view.Initialize();
        state = State::PLAYING;
    }

    void StateManager::Render(){
        switch (state) {
            case State::MAIN_MENU:
                DrawMainMenu();
                break;
            case State::LEVEL_MENU:
                DrawLevelMenu();
            case State::PAUSE_MENU:
                DrawPauseMenu();
                break;
            case State::PLAYING:
                view.Render();
                break;
        }
    }

    void StateManager::DrawMainMenu() {

    }

    void StateManager::DrawLevelMenu() {

    }

    void StateManager::DrawPauseMenu(){

    }

    void StateManager::DrawPlaying(){

    }
}
