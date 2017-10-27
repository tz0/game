#include "Views/PauseMenuView.h"

namespace tjg{
    PauseMenuView::PauseMenuView(ResourceManager &resource_manager, sf::RenderWindow &window) :
            View(window,resource_manager) {}


    void PauseMenuView::Initialize(){

    }

    void PauseMenuView::Initialize(State state) {
        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");
        // temp Set font for win message
        message.setFont(*avenir_bold);
        // Create a win message.
        message.setStyle(sf::Text::Bold);
        message.setCharacterSize(24);
        switch (state) {
            case State::WON:
                message.setString("You Reached the Exit!\nM/ Main Menu\nESC/ Exit Game");
                break;
            case State::FAILED:
                message.setString("You failed!\nM/ Main Menu\nESC/ Exit Game");
                break;
            case State::PAUSED:
                message.setString("Game is paused!\nR/ Resume\nESC/ Exit Game");
                break;
            default:
                break;
        }

        // Center the win message on the screen.
        sf::FloatRect textRect = message.getLocalBounds();
        message.setOrigin(textRect.left + (textRect.width / 2), textRect.top + (textRect.height / 2));
        message.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);
    }

    //Handle keyboard control of the menu
    void PauseMenuView::Update() {
    }


    void PauseMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(message);
        window.display();
    }

    ViewSwitch PauseMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::R:
                        return ViewSwitch::RESUME;
                    case sf::Keyboard::M:
                        return ViewSwitch::MAIN_MENU;
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
        return ViewSwitch::CONTINUE;
    }

}