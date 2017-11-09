#include "Views/LevelMenuView.h"

namespace tjg {
    LevelMenuView::LevelMenuView(ResourceManager &resource_manager, sf::RenderWindow &window) :
            View(window,resource_manager) {}


    void LevelMenuView::Initialize() {
        selection = 1;
        auto avenir_bold = resource_manager.LoadFont("Avenir-Bold.ttf");
        // temp Set font for win message
        message.setFont(*avenir_bold);
        // Create a win message.
        message.setStyle(sf::Text::Bold);
        message.setCharacterSize(24);
        message.setString("SELECT A LEVEL\n\n1/ Level 1\n2/ Level 2\nESC/ Back to menu");
        // Center the win message on the screen.
        sf::FloatRect textRect = message.getLocalBounds();
        message.setOrigin(textRect.left + (textRect.width / 2), textRect.top + (textRect.height / 2));
        message.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);
    }


    //TODO: Implement or remove
    void LevelMenuView::Update() {
        message.setString("Selected: " + std::to_string(selection) + "\nSELECT A LEVEL\n\n1/ Level 1\n2/ Level 2\nESC/ Back to menu");
    }


    void LevelMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(message);
        window.display();
    }

    ViewSwitch LevelMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selection > 1) selection -= 1;
                        break;
                    case sf::Keyboard::Down:
                        if (selection < unlocked) selection += 1;
                        break;
                    case sf::Keyboard::Return:
                        if (selection == 3) {
                            return ViewSwitch {State::MAIN_MENU, 0};
                        } else {
                            return ViewSwitch {State::PLAYING, selection};
                        }
//                    case sf::Keyboard::Num1:
//                        return ViewSwitch {State::PLAYING, 1};
//                    case sf::Keyboard::Num2:
//                        return ViewSwitch {State::PLAYING, 2};
                    case sf::Keyboard::Escape:
                        return ViewSwitch {State::MAIN_MENU, 0};
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