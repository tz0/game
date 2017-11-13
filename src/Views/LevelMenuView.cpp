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
        message.setString("SELECT A LEVEL\n\nLevel 1\nLevel 2\nBack to menu");
        // Center the win message on the screen.
        sf::FloatRect textRect = message.getLocalBounds();
        message.setOrigin(textRect.left + (textRect.width / 2), textRect.top + (textRect.height / 2));
        message.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);

        selection_box_position = sf::Vector2f(LEVEL_MENU_BOX_X_LEFT, LEVEL_MENU_BOX_Y_UP);
        selection_box.setSize(sf::Vector2f(200,29));
        selection_box.setPosition(selection_box_position);
        selection_box.setFillColor(sf::Color::Transparent);
        selection_box.setOutlineColor(sf::Color(255, 255, 255, 255));
        selection_box.setOutlineThickness(2.0f);
    }


    //TODO: Implement or remove
    void LevelMenuView::Update() {
        selection_box.setPosition(selection_box_position);
    }


    void LevelMenuView::Render() {
        window.setView(window.getDefaultView());
        window.clear(sf::Color(50, 50, 50, 255));
        window.draw(message);
        window.draw(selection_box);
        window.display();
    }

    ViewSwitch LevelMenuView::HandleWindowEvents(sf::Event event) {
        switch (event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (selection > 1) {
                            selection -= 1;
                            selection_box_position.y -= LEVEL_MENU_BOX_SHIFT;
                        } else {
                            selection = LEVEL_MENU_OPTIONS;
                            selection_box_position.y = LEVEL_MENU_BOX_Y_LOW;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (selection <= unlocked) {
                            selection += 1;
                            selection_box_position.y += LEVEL_MENU_BOX_SHIFT;
                        } else {
                            selection = 1;
                            selection_box_position.y = LEVEL_MENU_BOX_Y_UP;
                        }
                        break;
                    case sf::Keyboard::Return:
                        if (selection > unlocked) {
                            return ViewSwitch {State::MAIN_MENU, 0};
                        } else {
                            return ViewSwitch {State::PLAYING, selection};
                        }
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