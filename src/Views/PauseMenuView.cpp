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
                message.setString("Level " + std::to_string(current_level) + "\n\nYou Reached the Exit!\n\nENTER/ Go to Next Level\nR/ Replay This Level\nESC/ Exit to Main Menu\n");
                break;
            case State::FAILED:
                options = {ViewSwitch {State::PLAYING, 0}, ViewSwitch {State::MAIN_MENU, 0}};
                message.setString("Level " + std::to_string(current_level) + "\n\nYou failed!\n\nR/ Replay This Level\nESC/ Exit to Main Menu\n\n");
                break;
            case State::PAUSED:
                options = {ViewSwitch {State::LEVEL_MENU, 0}, ViewSwitch {State::RESUME, 0}, ViewSwitch {State::PLAYING, 0}, ViewSwitch {State::MAIN_MENU, 0}};
                message.setString("Level " + std::to_string(current_level) + "\nGame is paused.\nAre you sure you want to leave this level?\n\nY/ Leave Game\nN/ Resume Game\nR/ Restart Level\nESC/ Exit to Main Menu");
                break;
            default:
                break;
        }

        // Center the win message on the screen.
        sf::FloatRect textRect = message.getLocalBounds();
        message.setOrigin(textRect.left + (textRect.width / 2), textRect.top + (textRect.height / 2));
        message.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);

        selection_box_position = sf::Vector2f(350, 361);
        selection_box.setSize(sf::Vector2f(550,29));
        selection_box.setPosition(selection_box_position);
        selection_box.setFillColor(sf::Color::Transparent);
        selection_box.setOutlineColor(sf::Color(255, 255, 255, 255));
        selection_box.setOutlineThickness(2.0f);
    }


    //TODO: Implement or remove
    void PauseMenuView::Update() {
        selection_box.setPosition(selection_box_position);
    }


    void PauseMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(message);
        window.draw(selection_box);
        window.display();
    }

    ViewSwitch PauseMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selection > 0) {
                            selection -= 1;
                            selection_box_position.y -= 29;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (selection < options.size() - 1) {
                            selection += 1;
                            selection_box_position.y += 29;
                        }
                        break;
                    case sf::Keyboard::Return:
                        return options[selection];
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