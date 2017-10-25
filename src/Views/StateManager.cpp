#include "Views/StateManager.h"

namespace tjg {
    StateManager::StateManager(sf::RenderWindow &window):
        window(&window),
        state(State::PLAYING);

    void StateManager::SetState(State state){
        this -> state = state;
    }
    void StateManager::Draw(State state){
        switch (state) {
            case PAUSE_MENU:
                DrawPauseMenu();
                break;
            case PLAYING:
                DrawPlaying();
                break;
            default:
                break;
        }
    }

    void StateManager::DrawPauseMenu(){
        window->setView(window->getDefaultView());

        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(win_message);
        window.display();
    }

    void StateManager::DrawPlaying(){

    }
}
