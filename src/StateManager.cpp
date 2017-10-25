#include <bitset>
#include "StateManager.h"

namespace tjg {
    StateManager::StateManager(sf::RenderWindow &window):
        window(window),
        state(State::PLAYING){}

    void StateManager::SetState(State state){
        this -> state = state;
    }

    void StateManager::Initialize(sf::Font &font) {
        // temp Set font for win message
        win_message.setFont(font);
        // Create a win message.
        win_message.setStyle(sf::Text::Bold);
        win_message.setCharacterSize(24);
        win_message.setString("You Reached the Exit!");
        // Center the win message on the screen.
        sf::FloatRect textRect = win_message.getLocalBounds();
        win_message.setOrigin(textRect.left + (textRect.width / 2), textRect.top + (textRect.height / 2));
        win_message.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);
    }

    void StateManager::Draw(){
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
                DrawPlaying();
                break;
        }
    }

    void StateManager::DrawMainMenu() {

    }

    void StateManager::DrawLevelMenu() {

    }

    void StateManager::DrawPauseMenu(){
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(win_message);
        window.display();
    }

    void StateManager::DrawPlaying(){

    }
}
