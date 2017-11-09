#include "Views/PauseMenuView.h"

namespace tjg{
    PauseMenuView::PauseMenuView(ResourceManager &resource_manager, sf::RenderWindow &window) :
            View(window,resource_manager) {}


    void PauseMenuView::Initialize(ViewSwitch view_switch) {
        current_level = view_switch.level_number;
        selection = 0;
        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");
        // temp Set font for win message
        message.setFont(*avenir_bold);
        // Create a win message.
        message.setStyle(sf::Text::Bold);
        message.setCharacterSize(24);
        switch (view_switch.state) {
            case State::WON:
                options = {ViewSwitch {State::PLAYING, current_level + 1}, ViewSwitch {State::PLAYING, 0}, ViewSwitch {State::MAIN_MENU, 0}};
                message.setString("Level " + std::to_string(current_level) + "\nYou Reached the Exit!\n\nENTER/ Go to Next Level\nR/ Replay This Level\nESC/ Exit to Main Menu");
                break;
            case State::FAILED:
                options = {ViewSwitch {State::PLAYING, 0}, ViewSwitch {State::MAIN_MENU, 0}};
                message.setString("Level " + std::to_string(current_level) + "\nYou failed!\n\nR/ Replay This Level\nESC/ Exit to Main Menu");
                break;
            case State::PAUSED:
                options = {ViewSwitch {State::LEVEL_MENU, 0}, ViewSwitch {State::RESUME, 0}, ViewSwitch {State::PLAYING, 0}, ViewSwitch {State::MAIN_MENU, 0}};
                message.setString("Level " + std::to_string(current_level) + "\nGame is paused.\nAre you sure you want to leave this level?\n\nY/ Leave Game\nN/ Resume Game\nR/ Restart Level\nESC/ Exit to Main Menu");
                break;
            default:
                break;
        }

        arrow.setFont(*avenir_bold);
        // Create a win message.
        arrow.setStyle(sf::Text::Bold);
        arrow.setCharacterSize(24);

        // Center the win message on the screen.
        sf::FloatRect textRect = message.getLocalBounds();
        message.setOrigin(textRect.left + (textRect.width / 2), textRect.top + (textRect.height / 2));
        message.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);
    }


    //TODO: Implement or remove
    void PauseMenuView::Update() {
        arrow.setString("Selected: " + std::to_string(selection));
    }


    void PauseMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(message);
        window.draw(arrow);
        window.display();
    }

    ViewSwitch PauseMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selection > 0) selection -= 1;
                        break;
                    case sf::Keyboard::Down:
                        if (selection < options.size() - 1) selection += 1;
                        break;
                    case sf::Keyboard::Return:
                        return options[selection];
//                    case sf::Keyboard::Escape:
//                        return ViewSwitch {State::MAIN_MENU, 0};
//                    case sf::Keyboard::R:
//                        return ViewSwitch {State::PLAYING, 0};
//                    case sf::Keyboard::Y:
//                        return ViewSwitch {State::LEVEL_MENU, 0};
//                    case sf::Keyboard::N:
//                        return ViewSwitch {State::RESUME, 0};
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

}